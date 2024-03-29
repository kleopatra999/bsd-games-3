// Copyright (c) 1980 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "trek.h"
#include "getpar.h"
#include <setjmp.h>

// Signal game won
//
// This routine prints out the win message, arranges to print out
// your score, tells you if you have a promotion coming to you,
// cleans up the current input line, and arranges to have you
// asked whether or not you want another game (via the longjmp()
// call).
//
// Pretty straightforward, although the promotion algorithm is
// pretty off the wall.

extern jmp_buf env;

void win (void)
{
    long s;
    const struct cvntab *p = NULL;

    sleep(1);
    printf("\nCongratulations, you have saved the Federation\n");
    Move.endgame = 1;

    // print and return the score
    s = score();

    // decide if she gets a promotion
    if (Game.helps == 0 && Game.killb == 0 && Game.killinhab == 0 && 5 * Game.kills + Game.deaths < 100 && s >= 1000 && Ship.ship == ENTERPRISE) {
	printf("In fact, you are promoted one step in rank,\n");
	if (Game.skill >= 6)
	    printf("to the exalted rank of Commodore Emeritus\n");
	else {
	    p = &Skitab[Game.skill - 1];
	    printf("from %s%s ", p->abrev, p->full);
	    p++;
	    printf("to %s%s\n", p->abrev, p->full);
	}
    }

    // clean out input, and request new game
    skiptonl(0);
    longjmp(env, 1);
}
