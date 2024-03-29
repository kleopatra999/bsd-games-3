// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include <sys/types.h>

void subtract(struct ship *from, struct ship *fromcap, int totalfrom, int *crewfrom, int pcfrom)
{
    int n;

    if (fromcap == from && totalfrom) {	// if not captured
	for (n = 0; n < 3; n++) {
	    if (totalfrom > crewfrom[n]) {
		totalfrom -= crewfrom[n];
		crewfrom[n] = 0;
	    } else {
		crewfrom[n] -= totalfrom;
		totalfrom = 0;
	    }
	}
	Write(W_CREW, from, crewfrom[0], crewfrom[1], crewfrom[2], 0);
    } else if (totalfrom) {
	pcfrom -= totalfrom;
	pcfrom = pcfrom < 0 ? 0 : pcfrom;
	Write(W_PCREW, from, pcfrom, 0, 0, 0);
    }
}

int mensent(struct ship *from, struct ship *to, int *crew, struct ship **captured, int *pc, int isdefense)
{			       // returns # of crew squares sent
    int men = 0;
    int n;
    int c1, c2, c3;
    struct BP *bp;

    *pc = from->file->pcrew;
    *captured = from->file->captured;
    crew[0] = from->specs->crew1;
    crew[1] = from->specs->crew2;
    crew[2] = from->specs->crew3;
    bp = isdefense ? from->file->DBP : from->file->OBP;
    for (n = 0; n < NBP; n++, bp++) {
	if (bp->turnsent && bp->toship == to)
	    men += bp->mensent;
    }
    if (men) {
	c1 = men / 100 ? crew[0] : 0;
	c2 = (men % 100) / 10 ? crew[1] : 0;
	c3 = men / 10 ? crew[2] : 0;
	c3 = *captured == 0 ? crew[2] : *pc;
    } else
	c1 = c2 = c3 = 0;
    return (c1 + c2 + c3);
}
