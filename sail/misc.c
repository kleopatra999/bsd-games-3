// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include "pathnames.h"
#include <sys/file.h>

#define distance(x,y) (abs(x) >= abs(y) ? abs(x) + abs(y)/2 : abs(y) + abs(x)/2)

static int angle(int, int);

// XXX
int range(struct ship *from, struct ship *to)
{
    int bow1r, bow1c, bow2r, bow2c;
    int stern1r, stern1c, stern2c, stern2r;
    int bb, bs, sb, ss, result;

    if (!to->file->dir)
	return -1;
    stern1r = bow1r = from->file->row;
    stern1c = bow1c = from->file->col;
    stern2r = bow2r = to->file->row;
    stern2c = bow2c = to->file->col;
    result = bb = distance(bow2r - bow1r, bow2c - bow1c);
    if (bb < 5) {
	stern2r += dr[to->file->dir];
	stern2c += dc[to->file->dir];
	stern1r += dr[from->file->dir];
	stern1c += dc[from->file->dir];
	bs = distance((bow2r - stern1r), (bow2c - stern1c));
	sb = distance((bow1r - stern2r), (bow1c - stern2c));
	ss = distance((stern2r - stern1r), (stern2c - stern1c));
	result = min(bb, min(bs, min(sb, ss)));
    }
    return result;
}

struct ship *closestenemy(struct ship *from, int side, int anyship)
{
    struct ship *sp;
    char a;
    int olddist = 30000, dist;
    struct ship *closest = 0;

    a = capship(from)->nationality;
    foreachship(sp) {
	if (sp == from)
	    continue;
	if (sp->file->dir == 0)
	    continue;
	if (a == capship(sp)->nationality && !anyship)
	    continue;
	if (side && gunsbear(from, sp) != side)
	    continue;
	dist = range(from, sp);
	if (dist < olddist) {
	    closest = sp;
	    olddist = dist;
	}
    }
    return closest;
}

static int angle(int dr, int dc)
{
    int i;

    if (dc >= 0 && dr > 0)
	i = 0;
    else if (dr <= 0 && dc > 0)
	i = 2;
    else if (dc <= 0 && dr < 0)
	i = 4;
    else
	i = 6;
    dr = abs(dr);
    dc = abs(dc);
    if ((i == 0 || i == 4) && dc * 2.4 > dr) {
	i++;
	if (dc > dr * 2.4)
	    i++;
    } else if ((i == 2 || i == 6) && dr * 2.4 > dc) {
	i++;
	if (dr > dc * 2.4)
	    i++;
    }
    return i % 8 + 1;
}

// checks for target bow or stern
int gunsbear(struct ship *from, struct ship *to)
{
    int Dr, Dc, i;
    int ang;

    Dr = from->file->row - to->file->row;
    Dc = to->file->col - from->file->col;
    for (i = 2; i; i--) {
	if ((ang = angle(Dr, Dc) - from->file->dir + 1) < 1)
	    ang += 8;
	if (ang >= 2 && ang <= 4)
	    return 'r';
	if (ang >= 6 && ang <= 7)
	    return 'l';
	Dr += dr[to->file->dir];
	Dc += dc[to->file->dir];
    }
    return 0;
}

// returns true if fromship is shooting at onship's starboard side
int portside(struct ship *from, struct ship *on, int quick)
{
    int ang;
    int Dr, Dc;

    Dr = from->file->row - on->file->row;
    Dc = on->file->col - from->file->col;
    if (quick == -1) {
	Dr += dr[on->file->dir];
	Dc += dc[on->file->dir];
    }
    ang = angle(Dr, Dc);
    if (quick != 0)
	return ang;
    ang = (ang + 4 - on->file->dir - 1) % 8 + 1;
    return ang < 5;
}

int colours(struct ship *sp)
{
    char flag = '\0';

    if (sp->file->struck)
	flag = '!';
    if (sp->file->explode)
	flag = '#';
    if (sp->file->sink)
	flag = '~';
    if (sp->file->struck)
	return flag;
    flag = *countryname[capship(sp)->nationality];
    return sp->file->FS ? flag : tolower((unsigned char) flag);
}

void logger(struct ship *s)
{
    FILE *fp;
    int persons;
    int n;
    struct logs log[NLOG];
    float net;
    struct logs *lp;

    setegid(egid);
    if ((fp = fopen(_PATH_LOGFILE, "r+")) == NULL) {
	setegid(gid);
	return;
    }
    setegid(gid);
#ifdef LOCK_EX
    if (flock(fileno(fp), LOCK_EX) < 0)
	return;
#endif
    net = (float) s->file->points / s->specs->pts;
    persons = getw(fp);
    n = fread((char *) log, sizeof(struct logs), NLOG, fp);
    for (lp = &log[n]; lp < &log[NLOG]; lp++)
	lp->l_name[0] = lp->l_uid = lp->l_shipnum = lp->l_gamenum = lp->l_netpoints = 0;
    rewind(fp);
    if (persons < 0)
	putw(1, fp);
    else
	putw(persons + 1, fp);
    for (lp = log; lp < &log[NLOG]; lp++)
	if (net > (float) lp->l_netpoints / scene[lp->l_gamenum].ship[lp->l_shipnum].specs->pts) {
	    fwrite((char *) log, sizeof(struct logs), lp - log, fp);
	    strcpy(log[NLOG - 1].l_name, s->file->captain);
	    log[NLOG - 1].l_uid = getuid();
	    log[NLOG - 1].l_shipnum = s->file->index;
	    log[NLOG - 1].l_gamenum = game;
	    log[NLOG - 1].l_netpoints = s->file->points;
	    fwrite((char *) &log[NLOG - 1], sizeof(struct logs), 1, fp);
	    fwrite((char *) lp, sizeof(struct logs), &log[NLOG - 1] - lp, fp);
	    break;
	}
#ifdef LOCK_EX
    flock(fileno(fp), LOCK_UN);
#endif
    fclose(fp);
}
