// Copyright (c) 1985, Stichting Centrum voor Wiskunde en Informatica,
// Copyright (c) 1982 Jay Fenlason <hack@gnu.org>
// This file is free software, distributed under the BSD license.
//
// This cannot be part of tty.c (as it was earlier) since on some
// systems (e.g. MUNIX) the include files <termio.h> and <sgtty.h> define the
// same constants, and the C preprocessor complains.
//
#include "hack.h"
#include "extern.h"
#include <termios.h>
struct termios termios;

void getioctls(void)
{
    tcgetattr (fileno(stdin), &termios);
}

void setioctls(void)
{
    tcsetattr (fileno(stdin), TCSADRAIN, &termios);
}

#ifdef SUSPEND		       // implies BSD
#include <signal.h>
int dosuspend()
{
#ifdef SIGTSTP
    if (signal(SIGTSTP, SIG_IGN) == SIG_DFL) {
	settty((char *) 0);
	(void) signal(SIGTSTP, SIG_DFL);
	(void) kill(0, SIGTSTP);
	gettty();
	setftty();
	docrt();
    } else {
	pline("I don't think your shell has job control.");
    }
#else				// SIGTSTP
    pline("Sorry, it seems we have no SIGTSTP here. Try ! or S.");
#endif				// SIGTSTP
    return 0;
}
#endif				// SUSPEND
