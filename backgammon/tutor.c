// Copyright (c) 1980 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "back.h"
#include "tutor.h"

static const char better[] = "That is a legal move, but there is a better one.\n";

void tutor(void)
{
    int i, j;

    i = 0;
    begscr = 18;
    cturn = -1;
    home = 0;
    bar = 25;
    inptr = &in[0];
    inopp = &in[1];
    offptr = &off[0];
    offopp = &off[1];
    Colorptr = &color[0];
    colorptr = &color[2];
    colen = 5;
    wrboard();

    while (1) {
	if (!brdeq(test[i].brd, board)) {
	    if (tflag && curr == 23)
		curmove(18, 0);
	    writel(better);
	    nexturn();
	    movback(mvlim);
	    if (tflag) {
		refresh();
		clrest();
	    }
	    if ((!tflag) || curr == 19) {
		proll();
		writec('\t');
	    } else
		curmove(curr > 19 ? curr - 2 : curr + 4, 25);
	    getmove();
	    if (cturn == 0)
		leave();
	    continue;
	}
	if (tflag)
	    curmove(18, 0);
	text (test[i].com);
	if (!tflag)
	    writec('\n');
	if (i == maxmoves)
	    break;
	D0 = test[i].roll1;
	D1 = test[i].roll2;
	d0 = 0;
	mvlim = 0;
	for (j = 0; j < 4; j++) {
	    if (test[i].mp[j] == test[i].mg[j])
		break;
	    p[j] = test[i].mp[j];
	    g[j] = test[i].mg[j];
	    mvlim++;
	}
	if (mvlim)
	    for (j = 0; j < mvlim; j++)
		if (makmove(j))
		    writel("AARGH!!!\n");
	if (tflag)
	    refresh();
	nexturn();
	D0 = test[i].new1;
	D1 = test[i].new2;
	d0 = 0;
	i++;
	mvlim = movallow();
	if (mvlim) {
	    if (tflag)
		clrest();
	    proll();
	    writec('\t');
	    getmove();
	    if (tflag)
		refresh();
	    if (cturn == 0)
		leave();
	}
    }
    leave();
}

void clrest(void)
{
    int r, c, j;

    r = curr;
    c = curc;
    for (j = r + 1; j < 24; j++) {
	curmove(j, 0);
	cline();
    }
    curmove(r, c);
}

int brdeq(const int *b1, const int *b2)
{
    const int *e;

    e = b1 + 26;
    while (b1 < e)
	if (*b1++ != *b2++)
	    return 0;
    return 1;
}
