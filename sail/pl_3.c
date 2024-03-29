// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include "player.h"

void acceptcombat(void)
{
    int men = 0;
    int target, temp;
    int n, r;
    int index, rakehim, sternrake;
    int hhits = 0, ghits = 0, rhits = 0, chits = 0;
    int crew[3];
    int load;
    int guns, car, ready, shootat, hit;
    int roll;
    struct ship *closest;

    crew[0] = mc->crew1;
    crew[1] = mc->crew2;
    crew[2] = mc->crew3;
    for (n = 0; n < 3; n++) {
	if (mf->OBP[n].turnsent)
	    men += mf->OBP[n].mensent;
    }
    for (n = 0; n < 3; n++) {
	if (mf->DBP[n].turnsent)
	    men += mf->DBP[n].mensent;
    }
    if (men) {
	crew[0] = men / 100 ? 0 : crew[0] != 0;
	crew[1] = (men % 100) / 10 ? 0 : crew[1] != 0;
	crew[2] = men % 10 ? 0 : crew[2] != 0;
    }
    for (r = 0; r < 2; r++) {
	if (r) {
	    ready = mf->readyR;
	    load = mf->loadR;
	    guns = mc->gunR;
	    car = mc->carR;
	} else {
	    ready = mf->readyL;
	    load = mf->loadL;
	    guns = mc->gunL;
	    car = mc->carL;
	}
	if ((!guns && !car) || load == L_EMPTY || (ready & R_LOADED) == 0)
	    goto cant;
	if (mf->struck || !crew[2])
	    goto cant;
	closest = closestenemy(ms, (r ? 'r' : 'l'), 1);
	if (closest == 0)
	    goto cant;
	if (closest->file->struck)
	    goto cant;
	target = range(ms, closest);
	if (target > rangeofshot[load] || (!guns && target >= 3))
	    goto cant;
	Signal("$$ within range of %s broadside.", closest, r ? "right" : "left");
	if (load > L_CHAIN && target < 6) {
	    switch (sgetch("Aim for hull or rigging? ", (struct ship *) 0, 1)) {
		case 'r':
		    shootat = RIGGING;
		    break;
		case 'h':
		    shootat = HULL;
		    break;
		default:
		    shootat = -1;
		    Msg("'Avast there! Hold your fire.'");
	    }
	} else {
	    if (sgetch("Fire? ", (struct ship *) 0, 1) == 'n') {
		shootat = -1;
		Msg("Belay that! Hold your fire.");
	    } else
		shootat = RIGGING;
	}
	if (shootat == -1)
	    continue;
	fired = 1;
	rakehim = gunsbear(ms, closest) && !gunsbear(closest, ms);
	temp = portside(closest, ms, 1) - closest->file->dir + 1;
	if (temp < 1)
	    temp += 8;
	else if (temp > 8)
	    temp -= 8;
	sternrake = temp > 4 && temp < 6;
	if (rakehim) {
	    if (!sternrake)
		Msg("Raking the %s!", closest->shipname);
	    else
		Msg("Stern Rake! %s splintering!", closest->shipname);
	}
	index = guns;
	if (target < 3)
	    index += car;
	index = (index - 1) / 3;
	index = index > 8 ? 8 : index;
	if (!rakehim)
	    hit = HDT[index][target - 1];
	else
	    hit = HDTrake[index][target - 1];
	if (rakehim && sternrake)
	    hit++;
	hit += QUAL[index][mc->qual - 1];
	for (n = 0; n < 3 && mf->captured == 0; n++)
	    if (!crew[n]) {
		if (index <= 5)
		    hit--;
		else
		    hit -= 2;
	    }
	if (ready & R_INITIAL) {
	    if (index <= 3)
		hit++;
	    else
		hit += 2;
	}
	if (mf->captured != 0) {
	    if (index <= 1)
		hit--;
	    else
		hit -= 2;
	}
	hit += AMMO[index][load - 1];
	if (((temp = mc->class) >= 5 || temp == 1) && windspeed == 5)
	    hit--;
	if (windspeed == 6 && temp == 4)
	    hit -= 2;
	if (windspeed == 6 && temp <= 3)
	    hit--;
	if (hit >= 0) {
	    roll = dieroll();
	    if (load == L_GRAPE)
		chits = hit;
	    else {
		const struct Tables *t;
		if (hit > 10)
		    hit = 10;
		t = &(shootat == RIGGING ? RigTable : HullTable)
		    [hit][roll - 1];
		chits = t->C;
		rhits = t->R;
		hhits = t->H;
		ghits = t->G;
		if (closest->file->FS)
		    rhits *= 2;
		if (load == L_CHAIN) {
		    ghits = 0;
		    hhits = 0;
		}
	    }
	    table(ms, closest, shootat, load, hit, roll);
	}
	Msg("Damage inflicted on the %s:", closest->shipname);
	Msg("\t%d HULL, %d GUNS, %d CREW, %d RIGGING", hhits, ghits, chits, rhits);
	if (!r) {
	    mf->loadL = L_EMPTY;
	    mf->readyL = R_EMPTY;
	} else {
	    mf->loadR = L_EMPTY;
	    mf->readyR = R_EMPTY;
	}
	continue;
      cant:
	Msg("Unable to fire %s broadside", r ? "right" : "left");
    }
    blockalarm();
    draw_stat();
    unblockalarm();
}

void grapungrap(void)
{
    struct ship *sp;
    int i;

    foreachship(sp) {
	if (sp == ms || sp->file->dir == 0)
	    continue;
	if (range(ms, sp) > 1 && !grappled2(ms, sp))
	    continue;
	switch (sgetch("Attempt to grapple or ungrapple $$: ", sp, 1)) {
	    case 'g':
		if (dieroll() < 3 || ms->nationality == capship(sp)->nationality) {
		    Write(W_GRAP, ms, sp->file->index, 0, 0, 0);
		    Write(W_GRAP, sp, player, 0, 0, 0);
		    Msg("Attempt succeeds!");
		    makesignal(ms, "grappled with $$", sp);
		} else
		    Msg("Attempt fails.");
		break;
	    case 'u':
		for (i = grappled2(ms, sp); --i >= 0;) {
		    if (ms->nationality == capship(sp)->nationality || dieroll() < 3) {
			cleangrapple(ms, sp, 0);
			Msg("Attempt succeeds!");
			makesignal(ms, "ungrappling with $$", sp);
		    } else
			Msg("Attempt fails.");
		}
		break;
	}
    }
}

void unfoulplayer(void)
{
    struct ship *to;
    int i;

    foreachship(to) {
	if (fouled2(ms, to) == 0)
	    continue;
	if (sgetch("Attempt to unfoul with the $$? ", to, 1) != 'y')
	    continue;
	for (i = fouled2(ms, to); --i >= 0;) {
	    if (dieroll() <= 2) {
		cleanfoul(ms, to, 0);
		Msg("Attempt succeeds!");
		makesignal(ms, "Unfouling $$", to);
	    } else
		Msg("Attempt fails.");
	}
    }
}
