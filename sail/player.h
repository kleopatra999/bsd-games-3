// Copyright (c) 1983 The Regents of the University of California.
// This file is free software, distributed under the BSD license.
// sizes and coordinates for the screen

#define LINE_T		0
#define LINE_L		0
#define LINE_X		COLS
#define LINE_Y		1
#define LINE_B		(LINE_T+LINE_Y-1)
#define LINE_R		(LINE_L+LINE_X-1)

#define BOX_T		1
#define BOX_L		0
#define BOX_X		65
#define BOX_Y		16
#define BOX_B		(BOX_T+BOX_Y-1)
#define BOX_R		(BOX_L+BOX_X-1)

#define TURN_T		BOX_B
#define TURN_Y		1
#define TURN_L		((BOX_L+BOX_R-TURN_X)/2)
#define TURN_X		9
#define TURN_B		(TURN_T+TURN_Y+1)
#define TURN_R		(TURN_L+TURN_X+1)

#define STAT_T		0
#define STAT_B		BOX_B
#define STAT_L		(BOX_R+2)
#define STAT_X		14
#define STAT_Y		(STAT_B-STAT_T+1)
#define STAT_R		(STAT_L+STAT_X-1)
#define STAT_1		0
#define STAT_2          (STAT_1+4)
#define STAT_3          (STAT_2+7)

#define SCROLL_T	(BOX_B+1)
#define SCROLL_L	0
#define SCROLL_B	(LINES-1)
#define SCROLL_R	(COLS-1)
#define SCROLL_X	(SCROLL_R-SCROLL_L+1)
#define SCROLL_Y	(SCROLL_B-SCROLL_T+1)

#define VIEW_T		(BOX_T+1)
#define VIEW_L		(BOX_L+1)
#define VIEW_X		(BOX_X-5)
#define VIEW_Y		(BOX_Y-2)
#define VIEW_B		(VIEW_T+VIEW_Y-1)
#define VIEW_R		(VIEW_L+VIEW_X-1)

#define SLOT_T		VIEW_T
#define SLOT_L		(VIEW_R+1)
#define SLOT_X		3
#define SLOT_Y		VIEW_Y
#define SLOT_B		VIEW_B
#define SLOT_R		(SLOT_L+SLOT_X-1)

extern int done_curses;
extern int loaded, fired, changed, repaired;
extern int dont_adjust;
extern int viewrow, viewcol;
extern char movebuf[sizeof SHIP(0)->file->movebuf];
extern char version[];
extern int player;
extern struct ship *ms;		// memorial structure, &cc->ship[player]
extern struct File *mf;		// ms->file
extern struct shipspecs *mc;	// ms->specs

// condition codes for leave()
enum {
    LEAVE_QUIT,
    LEAVE_CAPTURED,
    LEAVE_HURRICAN,
    LEAVE_DRIVER,
    LEAVE_FORK,
    LEAVE_SYNC
};
