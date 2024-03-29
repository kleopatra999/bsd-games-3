// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include "driver.h"

static int stillmoving(int);
static int is_isolated(struct ship *);
static int push(struct ship *, struct ship *);
static void step(struct ship *, int, char *);

// move all comp ships
void moveall(void)
{
    struct ship *sp, *sq;
    int n;
    int k, l;
    int row[NSHIP], col[NSHIP], dir[NSHIP], drift[NSHIP];
    char moved[NSHIP];

    // first try to create moves for OUR ships
    foreachship(sp) {
	struct ship *closest;
	int ma, ta;
	char af;

	if (sp->file->captain[0] || sp->file->dir == 0)
	    continue;
	if (!sp->file->struck && windspeed && !snagged(sp)
	    && sp->specs->crew3) {
	    ta = maxturns(sp, &af);
	    ma = maxmove(sp, sp->file->dir, 0);
	    closest = closestenemy(sp, 0, 0);
	    if (closest == 0)
		*sp->file->movebuf = '\0';
	    else
		closeon(sp, closest, sp->file->movebuf, ta, ma, af);
	} else
	    *sp->file->movebuf = '\0';
    }
    // Then execute the moves for ALL ships (dead ones too),
    // checking for collisions and snags at each step.
    // The old positions are saved in row[], col[], dir[].
    // At the end, we compare and write out the changes.
    n = 0;
    foreachship(sp) {
	if (snagged(sp))
	    strcpy(sp->file->movebuf, "d");
	else if (*sp->file->movebuf != 'd')
	    strcat(sp->file->movebuf, "d");
	row[n] = sp->file->row;
	col[n] = sp->file->col;
	dir[n] = sp->file->dir;
	drift[n] = sp->file->drift;
	moved[n] = 0;
	n++;
    }
    // Now resolve collisions.
    // This is the tough part.
    for (k = 0; stillmoving(k); k++) {
	// Step once.
	// And propagate the nulls at the end of sp->file->movebuf.
	n = 0;
	foreachship(sp) {
	    if (!sp->file->movebuf[k])
		sp->file->movebuf[k + 1] = '\0';
	    else if (sp->file->dir)
		step(sp, sp->file->movebuf[k], &moved[n]);
	    n++;
	}
	// The real stuff.
	n = 0;
	foreachship(sp) {
	    if (sp->file->dir == 0 || is_isolated(sp))
		goto cont1;
	    l = 0;
	    foreachship(sq) {
		char snap = 0;

		if (sp == sq)
		    goto cont2;
		if (sq->file->dir == 0)
		    goto cont2;
		if (!push(sp, sq))
		    goto cont2;
		if (snagged2(sp, sq) && range(sp, sq) > 1)
		    snap++;
		if (!range(sp, sq) && !fouled2(sp, sq)) {
		    makesignal(sp, "collision with $$", sq);
		    if (dieroll() < 4) {
			makesignal(sp, "fouled with $$", sq);
			Write(W_FOUL, sp, l, 0, 0, 0);
			Write(W_FOUL, sq, n, 0, 0, 0);
		    }
		    snap++;
		}
		if (snap) {
		    sp->file->movebuf[k + 1] = 0;
		    sq->file->movebuf[k + 1] = 0;
		    sq->file->row = sp->file->row - 1;
		    if (sp->file->dir == 1 || sp->file->dir == 5)
			sq->file->col = sp->file->col - 1;
		    else
			sq->file->col = sp->file->col;
		    sq->file->dir = sp->file->dir;
		}
	      cont2:
		l++;
	    }
	  cont1:
	    n++;
	}
    }
    // Clear old moves.  And write out new pos.
    n = 0;
    foreachship(sp) {
	if (sp->file->dir != 0) {
	    *sp->file->movebuf = 0;
	    if (row[n] != sp->file->row)
		Write(W_ROW, sp, sp->file->row, 0, 0, 0);
	    if (col[n] != sp->file->col)
		Write(W_COL, sp, sp->file->col, 0, 0, 0);
	    if (dir[n] != sp->file->dir)
		Write(W_DIR, sp, sp->file->dir, 0, 0, 0);
	    if (drift[n] != sp->file->drift)
		Write(W_DRIFT, sp, sp->file->drift, 0, 0, 0);
	}
	n++;
    }
}

static int stillmoving(int k)
{
    struct ship *sp;

    foreachship(sp)
	if (sp->file->movebuf[k])
	return 1;
    return 0;
}

static int is_isolated(struct ship *ship)
{
    struct ship *sp;

    foreachship(sp) {
	if (ship != sp && range(ship, sp) <= 10)
	    return 0;
    }
    return 1;
}

static int push(struct ship *from, struct ship *to)
{
    int bs, sb;

    sb = to->specs->guns;
    bs = from->specs->guns;
    if (sb > bs)
	return 1;
    if (sb < bs)
	return 0;
    return from < to;
}

static void step(struct ship *sp, int com, char *moved)
{
    int dist;

    switch (com) {
	case 'r':
	    if (++sp->file->dir == 9)
		sp->file->dir = 1;
	    break;
	case 'l':
	    if (--sp->file->dir == 0)
		sp->file->dir = 8;
	    break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	    if (sp->file->dir % 2 == 0)
		dist = dtab[com - '0'];
	    else
		dist = com - '0';
	    sp->file->row -= dr[sp->file->dir] * dist;
	    sp->file->col -= dc[sp->file->dir] * dist;
	    *moved = 1;
	    break;
	case 'b':
	    break;
	case 'd':
	    if (!*moved) {
		if (windspeed != 0 && ++sp->file->drift > 2 && ((sp->specs->class >= 3 && !snagged(sp))
								|| (turn & 1) == 0)) {
		    sp->file->row -= dr[winddir];
		    sp->file->col -= dc[winddir];
		}
	    } else
		sp->file->drift = 0;
	    break;
    }
}

void sendbp(struct ship *from, struct ship *to, int sections, int isdefense)
{
    int n;
    struct BP *bp;

    bp = isdefense ? from->file->DBP : from->file->OBP;
    for (n = 0; n < NBP && bp[n].turnsent; n++);
    if (n < NBP && sections) {
	Write(isdefense ? W_DBP : W_OBP, from, n, turn, to->file->index, sections);
	if (isdefense)
	    makemsg(from, "repelling boarders");
	else
	    makesignal(from, "boarding the $$", to);
    }
}

int is_toughmelee(struct ship *ship, struct ship *to, int isdefense, int count)
{
    struct BP *bp;
    int obp = 0;
    int n, OBP = 0, DBP = 0, dbp = 0;
    int qual;

    qual = ship->specs->qual;
    bp = isdefense ? ship->file->DBP : ship->file->OBP;
    for (n = 0; n < NBP; n++, bp++) {
	if (bp->turnsent && (to == bp->toship || isdefense)) {
	    obp += bp->mensent / 100 ? ship->specs->crew1 * qual : 0;
	    obp += (bp->mensent % 100) / 10 ? ship->specs->crew2 * qual : 0;
	    obp += bp->mensent % 10 ? ship->specs->crew3 * qual : 0;
	}
    }
    if (count || isdefense)
	return obp;
    OBP = is_toughmelee(to, ship, 0, count + 1);
    dbp = is_toughmelee(ship, to, 1, count + 1);
    DBP = is_toughmelee(to, ship, 1, count + 1);
    if (OBP > obp + 10 || OBP + DBP >= obp + dbp + 10)
	return 1;
    else
	return 0;
}

void reload(void)
{
    struct ship *sp;

    foreachship(sp) {
	sp->file->loadwith = 0;
    }
}

void checksails(void)
{
    struct ship *sp;
    int rig, full;
    struct ship *close;

    foreachship(sp) {
	if (sp->file->captain[0] != 0)
	    continue;
	rig = sp->specs->rig1;
	if (windspeed == 6 || (windspeed == 5 && sp->specs->class > 4))
	    rig = 0;
	if (rig && sp->specs->crew3) {
	    close = closestenemy(sp, 0, 0);
	    if (close != 0) {
		if (range(sp, close) > 9)
		    full = 1;
		else
		    full = 0;
	    } else
		full = 0;
	} else
	    full = 0;
	if ((sp->file->FS != 0) != full)
	    Write(W_FS, sp, full, 0, 0, 0);
    }
}
