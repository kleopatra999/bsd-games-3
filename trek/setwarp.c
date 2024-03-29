// Copyright (c) 1980 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "trek.h"
#include "getpar.h"

// SET WARP FACTOR
//
// The warp factor is set for future move commands.  It is
// checked for consistancy.
void setwarp (int v UNUSED)
{
    double warpfac = getfltpar("Warp factor");
    if (warpfac < 0.0)
	return;
    if (warpfac < 1.0) {
	printf("Minimum warp speed is 1.0\n");
	return;
    }
    if (warpfac > 10.0) {
	printf("Maximum speed is warp 10.0\n");
	return;
    }
    if (warpfac > 6.0)
	printf("Damage to warp engines may occur above warp 6.0\n");
    Ship.warp = warpfac;
    Ship.warp2 = Ship.warp * warpfac;
    Ship.warp3 = Ship.warp2 * warpfac;
}
