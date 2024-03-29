// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include <sys/types.h>

int maxturns(struct ship *ship, char *af)
{
    int turns;

    turns = ship->specs->ta;
    *af = (ship->file->drift > 1 && turns);
    if (*af != '\0') {
	turns--;
	if (ship->file->FS == 1)
	    turns = 0;
    }
    return turns;
}

int maxmove(struct ship *ship, int dir, int fs)
{
    int riggone = 0, Move, flank = 0;

    Move = ship->specs->bs;
    if (!ship->specs->rig1)
	riggone++;
    if (!ship->specs->rig2)
	riggone++;
    if (!ship->specs->rig3)
	riggone++;
    if (!ship->specs->rig4)
	riggone++;
    if ((ship->file->FS || fs) && fs != -1) {
	flank = 1;
	Move = ship->specs->fs;
    }
    if (dir == winddir)
	Move -= 1 + WET[windspeed][ship->specs->class - 1].B;
    else if (dir == winddir + 2 || dir == winddir - 2 || dir == winddir - 6 || dir == winddir + 6)
	Move -= 1 + WET[windspeed][ship->specs->class - 1].C;
    else if (dir == winddir + 3 || dir == winddir - 3 || dir == winddir - 5 || dir == winddir + 5)
	Move = (flank ? 2 : 1) - WET[windspeed][ship->specs->class - 1].D;
    else if (dir == winddir + 4 || dir == winddir - 4)
	Move = 0;
    else
	Move -= WET[windspeed][ship->specs->class - 1].A;
    Move -= riggone;
    Move = Move < 0 ? 0 : Move;
    return (Move);
}
