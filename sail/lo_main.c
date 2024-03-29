// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.
//
// Print out the top ten SAILors
//
// -l force a long listing (print out real usernames)

#include "extern.h"
#include "pathnames.h"
#include <pwd.h>

const char *const title[] = {
    "Admiral", "Commodore", "Captain", "Captain",
    "Captain", "Captain", "Captain", "Commander",
    "Commander", "Lieutenant"
};

int lo_main(void)
{
    FILE *fp;
    char sbuf[32];
    int n = 0, people;
    struct passwd *pass;
    struct logs log;
    struct ship *ship;

    if ((fp = fopen(_PATH_LOGFILE, "r")) == 0) {
	perror(_PATH_LOGFILE);
	exit(1);
    }
    switch (fread((char *) &people, sizeof people, 1, fp)) {
	case 0:
	    printf("Nobody has sailed yet.\n");
	    exit(0);
	case 1:
	    break;
	default:
	    perror(_PATH_LOGFILE);
	    exit(1);
    }
    while (fread((char *) &log, sizeof log, 1, fp) == 1 && log.l_name[0] != '\0') {
	if (longfmt && (pass = getpwuid(log.l_uid)) != NULL)
	    sprintf(sbuf, "%10.10s (%s)", log.l_name, pass->pw_name);
	else
	    sprintf(sbuf, "%20.20s", log.l_name);
	ship = &scene[log.l_gamenum].ship[log.l_shipnum];
	printf("%-10s %21s of the %15s %3d points, %5.2f equiv\n", title[n++], sbuf, ship->shipname, log.l_netpoints, (float) log.l_netpoints / ship->specs->pts);
    }
    printf("\n%d people have played.\n", people);
    return 0;
}
