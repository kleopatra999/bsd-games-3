/*	$NetBSD: battlestar.c,v 1.6 1997/10/11 02:06:55 lukem Exp $	*/

/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT("@(#) Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
#endif				/* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)battlestar.c	8.2 (Berkeley) 4/28/95";
#else
__RCSID("$NetBSD: battlestar.c,v 1.6 1997/10/11 02:06:55 lukem Exp $");
#endif
#endif				/* not lint */

/*
 * Battlestar - a stellar-tropical adventure game
 *
 * Originally written by His Lordship, Admiral David W. Horatio Riggle,
 * on the Cory PDP-11/70, University of California, Berkeley.
 */

#include "extern.h"

int main __P((int, char *[]));

int
main(argc, argv)
	int     argc;
	char  **argv;
{
	char    mainbuf[LINELENGTH];
	char   *next;

	initialize(argc < 2 || strcmp(argv[1], "-r"));
start:
	news();
	beenthere[position]++;
	if (notes[LAUNCHED])
		crash();	/* decrements fuel & crash */
	if (matchlight) {
		puts("Your match splutters out.");
		matchlight = 0;
	}
	if (!notes[CANTSEE] || testbit(inven, LAMPON) ||
	    testbit(location[position].objects, LAMPON)) {
		writedes();
		printobjs();
	} else
		puts("It's too dark to see anything in here!");
	whichway(location[position]);
run:
	next = getcom(mainbuf, sizeof mainbuf, ">-: ",
	    "Please type in something.");
	for (wordcount = 0; next && wordcount < 20; wordcount++)
		next = getword(next, words[wordcount], -1);
	parse();
	switch (cypher()) {
	case -1:
		goto run;
	case 0:
		goto start;
	default:
		exit(1); /* Shouldn't happen */
	}
}
