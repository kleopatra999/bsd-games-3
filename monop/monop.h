// Copyright (c) 1980 The Regents of the University of California.
// This file is free software, distributed under the BSD license.

#include "../config.h"
#include <err.h>

enum {
    N_MON	= 8,	// number of monopolies
    N_PROP	= 22,	// number of normal property squares
    N_RR	= 4,	// number of railroads
    N_UTIL	= 2,	// number of utilities
    N_SQRS	= 40,	// number of squares on board
    MAX_PL	= 9,	// maximum number of players
    MAX_PRP	= (N_PROP+N_RR+N_UTIL)	// max # ownable property
};

// square type numbers
enum {
    PRPTY,	// normal property
    RR,		// railroad
    UTIL,	// water works - electric co
    SAFE,	// safe spot
    CC,		// community chest
    CHANCE,	// chance (surprise!!!)
    INC_TAX,	// Income tax
    GOTO_J,	// Go To Jail!
    LUX_TAX,	// Luxury tax
    IN_JAIL,	// In jail
    JAIL = 40	// JAIL square number
};

#define	lucky(str)	printf("%s%s\n",str,lucky_mes[roll(1,num_luck)-1])
#define	sqnum(sqp)	(sqp - board)

struct sqr_st {			// structure for square
    const char *name;		// place name
    short owner;		// owner number
    short type;			// place type
    struct prp_st *desc;	// description struct
    int cost;			// cost
};

typedef struct sqr_st SQUARE;

struct mon_st {			// monopoly description structure
    const char *name;		// monop. name (color)
    short owner;		// owner of monopoly
    short num_in;		// # in monopoly
    short num_own;		// # owned (-1: not poss. monop)
    short h_cost;		// price of houses
    const char *not_m;		// name if not monopoly
    const char *mon_n;		// name if a monopoly
    unsigned char sqnums[3];	// Square numbers (used to init)
    SQUARE *sq[3];		// list of squares in monop
};

typedef struct mon_st MON;

//
// This struct describes a property.  For railroads and utilities, only
// the "morg" member is used.
struct prp_st {			// property description structure
    bool morg;			// set if mortgaged
    bool monop;			// set if monopoly
    short square;		// square description
    short houses;		// number of houses
    MON *mon_desc;		// name of color
    int rent[6];		// rents
};

struct own_st {			// element in list owned things
    SQUARE *sqr;		// pointer to square
    struct own_st *next;	// next in list
};

typedef struct own_st OWN;

struct plr_st {			// player description structure
    char *name;			// owner name
    short num_gojf;		// # of get-out-of-jail-free's
    short num_rr;		// # of railroads owned
    short num_util;		// # of water works/elec. co.
    short loc;			// location on board
    short in_jail;		// count of turns in jail
    int money;			// amount of money
    OWN *own_list;		// start of propery list
};

typedef struct plr_st PLAY;
typedef struct prp_st PROP;
typedef struct prp_st RR_S;
typedef struct prp_st UTIL_S;

// cards.c
void init_decks(void);
void get_card(unsigned);

// execute.c
void execute(int);
void do_move(void);
void move(int);
void save(void);
void restore(void);
int rest_f(const char *);

// getinp.c
int getinp(const char *, const char *const[]);

// houses.c
void buy_houses(void);
void sell_houses(void);

// jail.c
void card(void);
void ret_card(PLAY *);
void pay(void);
int move_jail(int, int);
void printturn(void);

// misc.c
int getyn(const char *);
void notify(void);
void next_play(void);
int get_int(const char *);
void set_ownlist(int);
void is_monop(MON *, int);
void is_not_monop(MON *);
void list(void);
void list_all(void);
void quit(void);

// morg.c
void mortgage(void);
void unmortgage(void);
void force_morg(void);

// print.c
void printboard(void);
void where(void);
void printsq(int, bool);
void printhold(int);

// prop.c
void buy(int, SQUARE *);
void add_list(int, OWN **, int);
void del_list(int, OWN **, int);
void bid(void);
int prop_worth(PLAY *);

// rent.c
void rent(SQUARE *);

// roll.c
int roll(int, int);

// spec.c
void inc_tax(void);
void goto_jail(void);
void lux_tax(void);
void cc(void);
void chance(void);

// trade.c
void trade(void);
void resign(void);
