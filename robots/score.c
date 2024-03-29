// Copyright (c) 1980 The Regents of the University of California.
// Copyright (c) 1999 The NetBSD Foundation, Inc.
// This file is free software, distributed under the BSD license.

#include "robots.h"
#include <arpa/inet.h>	       // for ntohl and htonl

const char *Scorefile = _PATH_SCORE;

int Max_per_uid = MAX_PER_UID;

static SCORE Top[MAXSCORES];

static u_int32_t numscores, max_uid;

static void read_score(int);
static void write_score(int);

// Read the score file in MI format
static void read_score (int inf)
{
    SCORE *scp;
    if (read(inf, &max_uid, sizeof max_uid) == sizeof max_uid) {
	max_uid = ntohl(max_uid);
	read(inf, Top, sizeof Top);
	for (scp = Top; scp < &Top[MAXSCORES]; scp++) {
	    scp->s_uid = ntohl(scp->s_uid);
	    scp->s_score = ntohl(scp->s_score);
	    scp->s_auto = ntohl(scp->s_auto);
	    scp->s_level = ntohl(scp->s_level);
	}
    } else {
	for (scp = Top; scp < &Top[MAXSCORES]; scp++)
	    scp->s_score = 0;
	max_uid = Max_per_uid;
    }
}

// Write the score file in MI format
static void write_score (int inf)
{
    lseek(inf, 0L, SEEK_SET);

    max_uid = htonl(max_uid);
    write(inf, &max_uid, sizeof max_uid);

    for (SCORE* scp = Top; scp < &Top[MAXSCORES]; scp++) {
	scp->s_uid = htonl(scp->s_uid);
	scp->s_score = htonl(scp->s_score);
	scp->s_auto = htonl(scp->s_auto);
	scp->s_level = htonl(scp->s_level);
    }

    write(inf, Top, sizeof Top);
}

// Post the player's score, if reasonable, and then print out the top list.
void score (int score_wfd)
{
    int inf = score_wfd;
    SCORE *scp;
    u_int32_t uid;
    bool done_show = false;

    Newscore = false;
    if (inf < 0)
	return;

    read_score(inf);

    uid = getuid();
    if (Top[MAXSCORES - 1].s_score <= Score) {
	numscores = 0;
	for (scp = Top; scp < &Top[MAXSCORES]; scp++)
	    if ((scp->s_uid == uid && ++numscores == max_uid)) {
		if (scp->s_score > Score)
		    break;
		scp->s_score = Score;
		scp->s_uid = uid;
		scp->s_auto = Auto_bot;
		scp->s_level = Level;
		set_name(scp);
		Newscore = true;
		break;
	    }
	if (scp == &Top[MAXSCORES]) {
	    Top[MAXSCORES - 1].s_score = Score;
	    Top[MAXSCORES - 1].s_uid = uid;
	    Top[MAXSCORES - 1].s_auto = Auto_bot;
	    Top[MAXSCORES - 1].s_level = Level;
	    set_name(&Top[MAXSCORES - 1]);
	    Newscore = true;
	}
	if (Newscore)
	    qsort(Top, MAXSCORES, sizeof Top[0], cmp_sc);
    }

    if (!Newscore) {
	Full_clear = false;
	lseek(inf, 0, SEEK_SET);
	return;
    } else
	Full_clear = true;

    move(1, 15);
    printw("%5.5s %5.5s %-9.9s %-8.8s %5.5s", "Rank", "Score", "User", " ", "Level");

    for (scp = Top; scp < &Top[MAXSCORES]; scp++) {
	if (scp->s_score == 0)
	    break;
	move((scp - Top) + 2, 15);
	if (!done_show && scp->s_uid == uid && scp->s_score == Score)
	    standout();
	printw("%5ld %5d %-8.8s %-9.9s %5d", (long) (scp - Top) + 1, scp->s_score, scp->s_name, scp->s_auto ? "(autobot)" : "", scp->s_level);
	if (!done_show && scp->s_uid == uid && scp->s_score == Score) {
	    standend();
	    done_show = true;
	}
    }
    Num_scores = scp - Top;
    refresh();

    if (Newscore) {
	write_score(inf);
    }
    lseek(inf, 0, SEEK_SET);
}

void set_name (SCORE* scp)
{
    PASSWD* pp = getpwuid(scp->s_uid);
    strncpy(scp->s_name, pp ? pp->pw_name : "???", MAXNAME);
}

// Compare two scores.
int cmp_sc (const void* s1, const void* s2)
{
    return ((const SCORE*)s2)->s_score - ((const SCORE*)s1)->s_score;
}

// Show the score list for the '-s' option.
void show_score (void)
{
    int inf = open(Scorefile, O_RDONLY);
    if (inf < 0) {
	warn("opening `%s'", Scorefile);
	return;
    }
    read_score(inf);
    close(inf);
    inf = 1;
    printf("%5.5s %5.5s %-9.9s %-8.8s %5.5s\n", "Rank", "Score", "User", " ", "Level");
    for (SCORE* scp = Top; scp < &Top[MAXSCORES]; ++scp)
	if (scp->s_score > 0)
	    printf("%5d %5d %-8.8s %-9.9s %5d\n", inf++, scp->s_score, scp->s_name, scp->s_auto ? "(autobot)" : "", scp->s_level);
}
