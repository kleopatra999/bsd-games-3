// Copyright (c) 2003 The NetBSD Foundation, Inc.
// This file is free software, distributed under the BSD license.

// ttyscrn.cc: Curses screen implementation for dots

#include "player.h"
#include "ttyscrn.h"
#include <curses.h>
#include <sys/ioctl.h>

void TTYSCRN::clean (void)
{
    clear();
}

void TTYSCRN::moveto (size_t y, size_t x)
{
    move(y + TTYSCRN::offsy, x + TTYSCRN::offsx);
}

void TTYSCRN::addsym (const int sym)
{
    addch(sym);
}

void TTYSCRN::addedge (const int sym)
{
    int nsym;
#ifdef A_ALTCHARSET
    if (_acs) {
	switch (sym) {
	    case GS_HLINE:	nsym = ACS_HLINE; break;
	    case GS_VLINE:	nsym = ACS_VLINE; break;
	    case GS_ULCORNER:	nsym = ACS_ULCORNER; break;
	    case GS_URCORNER:	nsym = ACS_URCORNER; break;
	    case GS_LLCORNER:	nsym = ACS_LLCORNER; break;
	    case GS_LRCORNER:	nsym = ACS_LRCORNER; break;
	    case GS_LTEE:	nsym = ACS_LTEE; break;
	    case GS_RTEE:	nsym = ACS_RTEE; break;
	    case GS_TTEE:	nsym = ACS_TTEE; break;
	    case GS_BTEE:	nsym = ACS_BTEE; break;
	    case GS_PLUS:	nsym = ACS_PLUS; break;
	    case ' ':		addsym(' '); return;
	    default:		::abort();
	}
	attron(A_ALTCHARSET);
	addch(nsym);
	attroff(A_ALTCHARSET);
	return;
    }
#endif
    switch (sym) {
	case GS_HLINE:		nsym = '-'; break;
	case GS_VLINE:		nsym = '|'; break;
	case GS_ULCORNER:	nsym = '.'; break;
	case GS_URCORNER:	nsym = '.'; break;
	case GS_LLCORNER:	nsym = '.'; break;
	case GS_LRCORNER:	nsym = '.'; break;
	case GS_LTEE:		nsym = '.'; break;
	case GS_RTEE:		nsym = '.'; break;
	case GS_TTEE:		nsym = '.'; break;
	case GS_BTEE:		nsym = '.'; break;
	case GS_PLUS:		nsym = '+'; break;
	case ' ':		addsym(' '); return;
	default:		::abort();
    }
    addsym(nsym);
}

void TTYSCRN::redraw (void)
{
    refresh();
    doupdate();
}

void TTYSCRN::bell (void)
{
    putc('\007', stdout);
}

int TTYSCRN::getinput (void)
{
    return getch();
}

void TTYSCRN::score (size_t s, const PLAYER& p)
{
    mvwprintw (stdscr, _sy + s + TTYSCRN::offsscore, _sx, "S %c:%5zd", p.getWho(), p.getScore());
}

void TTYSCRN::total (size_t s, const PLAYER& p)
{
    mvwprintw (stdscr, _sy + s + TTYSCRN::offstotal, _sx, "T %c:%5zd", p.getWho(), p.getTotal());
}

void TTYSCRN::games (size_t s, const PLAYER& p)
{
    mvwprintw (stdscr, _sy + s + TTYSCRN::offsgames, _sx, "G %c:%5zd", p.getWho(), p.getGames());
}

void TTYSCRN::ties (const PLAYER& p)
{
    mvwprintw (stdscr, _sy + TTYSCRN::offsties, _sx, "G =:%5zd", p.getTies());
}

TTYSCRN* TTYSCRN::create(int acs, size_t y, size_t x)
{
    initscr();
    int tx = getmaxx(stdscr);
    int ty = getmaxy(stdscr);
    if (tx == ERR || ty == ERR || (size_t)tx < x * 2 + TTYSCRN::offsx + 12
	|| (size_t)ty < y * 2 + TTYSCRN::offsy) {
	endwin();
	return nullptr;
    }
    cbreak();
    noecho();

    static TTYSCRN that;
    that._tx = tx;
    that._ty = ty;
    that._sx = tx - 12;
    that._sy = TTYSCRN::offsy;
    that._acs = acs;
    return &that;
}

TTYSCRN::~TTYSCRN (void)
{
    nocbreak();
    echo();
    endwin();
}
