// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "extern.h"
#include "player.h"
#include "restart.h"
#include <setjmp.h>
#include <signal.h>

static void initialize(void);

int pl_main(void)
{
    initialize();
    Msg("Aye aye, Sir");
    play();
    return 0;		       // for lint,  play() never returns
}

static void initialize(void)
{
    struct File *fp;
    struct ship *sp;
    char captain[80];
    char message[60];
    int load;
    int n;
    char *nameptr;
    int nat[NNATION];

    if (game < 0) {
	puts("Choose a scenario:\n");
	puts("\n\tNUMBER\tSHIPS\tIN PLAY\tTITLE");
	for (n = 0; n < NSCENE; n++) {
	    // (
	    printf("\t%d):\t%d\t%s\t%s\n", n, scene[n].vessels, sync_exists(n) ? "YES" : "no", scene[n].name);
	}
      reprint:
	printf("\nScenario number? ");
	fflush(stdout);
	scanf("%d", &game);
	while (getchar() != '\n');
    }
    if (game < 0 || game >= NSCENE) {
	puts("Very funny.");
	exit(1);
    }
    cc = &scene[game];
    ls = SHIP(cc->vessels);

    for (n = 0; n < NNATION; n++)
	nat[n] = 0;
    foreachship(sp) {
	if (sp->file == NULL && (sp->file = (struct File *) calloc(1, sizeof(struct File))) == NULL) {
	    puts("OUT OF MEMORY");
	    exit(1);
	}
	sp->file->index = sp - SHIP(0);
	sp->file->stern = nat[sp->nationality]++;
	sp->file->dir = sp->shipdir;
	sp->file->row = sp->shiprow;
	sp->file->col = sp->shipcol;
    }
    windspeed = cc->windspeed;
    winddir = cc->winddir;

    signal(SIGHUP, choke);
    signal(SIGINT, choke);

    hasdriver = sync_exists(game);
    if (sync_open() < 0) {
	perror("sail: syncfile");
	exit(1);
    }

    if (hasdriver) {
	puts("Synchronizing with the other players...");
	fflush(stdout);
	if (Sync() < 0)
	    leave(LEAVE_SYNC);
    }
    for (;;) {
	foreachship(sp)
	    if (sp->file->captain[0] == 0 && !sp->file->struck && sp->file->captured == 0)
	    break;
	if (sp >= ls) {
	    puts("All ships taken in that scenario.");
	    foreachship(sp)
		free((char *) sp->file);
	    sync_close(0);
	    people = 0;
	    goto reprint;
	}
	if (randomize) {
	    player = sp - SHIP(0);
	} else {
	    printf("%s\n\n", cc->name);
	    foreachship(sp)
		printf("  %2d:  %-10s %-15s  (%-2d pts)   %s\n", sp->file->index, countryname[sp->nationality], sp->shipname, sp->specs->pts, saywhat(sp, 1));
	    printf("\nWhich ship (0-%d)? ", cc->vessels - 1);
	    fflush(stdout);
	    if (scanf("%d", &player) != 1 || player < 0 || player >= cc->vessels) {
		while (getchar() != '\n');
		puts("Say what?");
		player = -1;
	    } else
		while (getchar() != '\n');
	}
	if (player < 0)
	    continue;
	if (Sync() < 0)
	    leave(LEAVE_SYNC);
	fp = SHIP(player)->file;
	if (fp->captain[0] || fp->struck || fp->captured != 0)
	    puts("That ship is taken.");
	else
	    break;
    }

    ms = SHIP(player);
    mf = ms->file;
    mc = ms->specs;

    Write(W_BEGIN, ms, 0, 0, 0, 0);
    if (Sync() < 0)
	leave(LEAVE_SYNC);

    signal(SIGCHLD, child);
    if (!hasdriver)
	switch (fork()) {
	    case 0:
		longjmp(restart, MODE_DRIVER);
	     /*NOTREACHED*/ case -1:
		perror("fork");
		leave(LEAVE_FORK);
		break;
	    default:
		hasdriver++;
	}

    printf("Your ship is the %s, a %d gun %s (%s crew).\n", ms->shipname, mc->guns, classname[mc->class], qualname[mc->qual]);
    if ((nameptr = (char *) getenv("SAILNAME")) && *nameptr)
	strncpy(captain, nameptr, sizeof captain);
    else {
	printf("Your name, Captain? ");
	fflush(stdout);
	fgets(captain, sizeof captain, stdin);
	if (!*captain)
	    strcpy(captain, "no name");
	else
	    captain[strlen(captain) - 1] = '\0';
    }
    captain[sizeof captain - 1] = '\0';
    Writestr(W_CAPTAIN, ms, captain);
    for (n = 0; n < 2; n++) {
	char buf[10];

	printf("\nInitial broadside %s (grape, chain, round, double): ", n ? "right" : "left");
	fflush(stdout);
	scanf("%s", buf);
	switch (*buf) {
	    case 'g':
		load = L_GRAPE;
		break;
	    case 'c':
		load = L_CHAIN;
		break;
	    case 'r':
		load = L_ROUND;
		break;
	    case 'd':
		load = L_DOUBLE;
		break;
	    default:
		load = L_ROUND;
	}
	if (n) {
	    mf->loadR = load;
	    mf->readyR = R_LOADED | R_INITIAL;
	} else {
	    mf->loadL = load;
	    mf->readyL = R_LOADED | R_INITIAL;
	}
    }

    initscreen();
    draw_board();
    snprintf(message, sizeof message, "Captain %s assuming command", captain);
    Writestr(W_SIGNAL, ms, message);
    newturn(0);
}
