// Copyright (c) 1980 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "../config.h"
#include <sys/uio.h>
#include <signal.h>
#include <termios.h>
#include <termcap.h>

#define rnum(r)	(rand()%r)
#define D0	dice[0]
#define D1	dice[1]
#define swap	{D0 ^= D1; D1 ^= D0; D0 ^= D1; d0 = 1-d0;}

// Some numerical conventions:
//
//      Arrays have white's value in [0], red in [1].
//      Numeric values which are one color or the other use
//      -1 for white, 1 for red.
//      Hence, white will be negative values, red positive one.
//      This makes a lot of sense since white is going in decending
//      order around the board, and red is ascending.
//
extern int pnum;		// color of player:
				//      -1 = white
				//       1 = red
				//       0 = both
				//       2 = not yet init'ed
extern char args[100];		// args passed to teachgammon and back
extern int acnt;		// length of args
extern int aflag;		// flag to ask for rules or instructions
extern int bflag;		// flag for automatic board printing
extern int cflag;		// case conversion flag
extern int hflag;		// flag for cleaning screen
extern int mflag;		// backgammon flag
extern int raflag;		// 'roll again' flag for recovered game
extern int rflag;		// recovered game flag
extern int tflag;		// cursor addressing flag
extern int rfl;			// saved value of rflag
extern int iroll;		// special flag for inputting rolls
extern int board[26];		// board:  negative values are white,
				//  positive are red
extern int dice[2];		// value of dice
extern int mvlim;		// 'move limit':  max. number of moves
extern int mvl;			// working copy of mvlim
extern int p[5];		// starting position of moves
extern int g[5];		// ending position of moves (goals)
extern int h[4];		// flag for each move if a man was hit
extern int cturn;		// whose turn it currently is:
				//      -1 = white
				//       1 = red
				//       0 = just quitted
				//      -2 = white just lost
				//       2 = red just lost
extern int d0;			// flag if dice have been reversed from
				//   original position
extern int table[6][6];		// odds table for possible rolls
extern int rscore;		// red's score
extern int wscore;		// white's score
extern int gvalue;		// value of game (64 max.)
extern int dlast;		// who doubled last (0 = neither)
extern int bar;			// position of bar for current player
extern int home;		// position of home for current player
extern int off[2];		// number of men off board
extern int *offptr;		// pointer to off for current player
extern int *offopp;		// pointer to off for opponent
extern int in[2];		// number of men in inner table
extern int *inptr;		// pointer to in for current player
extern int *inopp;		// pointer to in for opponent

extern int ncin;		// number of characters in cin
extern char cin[100];		// input line of current move
				//   (used for reconstructing input after
				//   a backspace)

extern const char *const color[];
				// colors as strings
extern const char *const *colorptr;	// color of current player
extern const char *const *Colorptr;	// color of current player, capitalized
extern int colen;		// length of color of current player

extern struct termios old, noech, bg_raw;	// original tty status

extern int curr;		// row position of cursor
extern int curc;		// column position of cursor
extern int begscr;		// 'beginning' of screen
				//   (not including board)

int addbuf(int);
void backone(int);
void bsect(int, int, int, int);
void buflush(void);
int canhit(int, int);
int checkd(int);
int checkmove(int);
void clear(void);
void clend(void);
void cline(void);
int count(void);
void curmove(int, int);
int dotable(char, int);
void errexit(const char *) NORETURN;
void fancyc(int);
void fboard(void);
void fixcol(int, int, int, int, int);
void fixpos(int, int, int, int, int);
void fixtty(struct termios *);
void getarg(char ***);
int getcaps(const char *);
void getmove(void);
void getout(int) NORETURN;
void gwrite(void);
void init(void);
int last(void);
int main(int, char *[]);
int makmove(int);
int movallow(void);
void movback(int);
void moverr(int);
int movokay(int);
void newline(void);
void newpos(void);
void nexturn(void);
void norec(const char *) NORETURN;
void odds(int, int, int);
void proll(void);
int quit(void);
int readc(void);
void recover(const char *);
void refresh(void);
void roll(void);
int rsetbrd(void);
void save(int);
int text(const char *const *);
void wrboard(void);
void wrbsub(void);
void wrhit(int);
void wrint(int);
void writec(char);
void writel(const char *);
void wrscore(void);
int yorn(char);
