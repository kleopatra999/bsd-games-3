#include "struct.h"
#include "extern.h"

//{{{ Helper macros ----------------------------------------------------

// Direction codes from old grammar
// w	DIR_NORTH
// e	DIR_NE
// d	DIR_EAST
// c	DIR_SE
// x	DIR_SOUTH
// z	DIR_SW
// a	DIR_WEST
// q	DIR_NW

#define ArrayCName(game,aname)	c_##game##Game_##aname##s
#define StaticGameArray(game,aname)\
    .num_##aname##s = ArraySize(ArrayCName(game,aname)),\
    .aname = ArrayCName(game,aname)

#define LineDef(x1,y1,x2,y2)	\
    {{x1,y1,DIR_NORTH}, {x2,y2,DIR_NORTH}}

//}}}-------------------------------------------------------------------
//{{{ Default game

static const EXIT c_DefaultGame_exits[] = {
    { 12,  0, DIR_SOUTH	},
    { 29,  0, DIR_SW	},
    { 29,  7, DIR_WEST	},
    { 29, 17, DIR_WEST	},
    {  9, 20, DIR_NE	},
    {  0, 13, DIR_EAST	},
    {  0,  7, DIR_EAST	},
    {  0,  0, DIR_SE	}
};
static const LINE c_DefaultGame_lines[] = {
    LineDef (1,1,	6,6),
    LineDef (12,1,	12,6),
    LineDef (13,7,	28,7),
    LineDef (28,1,	13,16),
    LineDef (1,13,	11,13),
    LineDef (12,8,	12,16),
    LineDef (11,18,	10,19),
    LineDef (13,17,	28,17),
    LineDef (1,7,	11,7)
};
static const BEACON c_DefaultGame_beacons[] = {
    { 12,  7, DIR_NORTH	},
    { 12, 17, DIR_NORTH	}
};
static const AIRPORT c_DefaultGame_airports[] = {
    { 20, 15, DIR_NORTH	},
    { 20, 18, DIR_EAST	}
};
static const C_SCREEN c_DefaultGame = {
    .name		= "Default",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 10,
    StaticGameArray (Default, exit),
    StaticGameArray (Default, line),
    StaticGameArray (Default, beacon),
    StaticGameArray (Default, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Atlantis

static const EXIT c_AtlantisGame_exits[] = {
    { 10,  0, DIR_SOUTH	},
    { 29,  6, DIR_WEST	},
    { 27, 20, DIR_NW	},
    {  0, 16, DIR_EAST	}
};
static const BEACON c_AtlantisGame_beacons[] = {
    { 10,  6, DIR_NORTH	},
    { 23,  6, DIR_NORTH	},
    { 23, 16, DIR_NORTH	},
    { 15, 16, DIR_NORTH	},
    {  7, 16, DIR_NORTH	},
    {  7,  9, DIR_NORTH	},
    { 15,  6, DIR_NORTH	}
};
static const LINE c_AtlantisGame_lines[] = {
    LineDef (10,1, 10,5),
    LineDef (11,6, 14,6),
    LineDef (16,6, 22,6),
    LineDef (24,6, 28,6),
    LineDef (1,16, 6,16),
    LineDef (8,16, 14,16),
    LineDef (16,16, 22,16),
    LineDef (23,7, 23,7),
    LineDef (23,9, 23,15),
    LineDef (15,7, 15,11),
    LineDef (15,13, 15,15),
    LineDef (7,10, 7,15),
    LineDef (9,7, 8,8),
    LineDef (6,10, 1,15),
    LineDef (24,17, 26,19)
};
static const AIRPORT c_AtlantisGame_airports[] = {
    { 23,  8, DIR_SOUTH	},
    { 15, 12, DIR_NORTH	}
};
static const C_SCREEN c_AtlantisGame = {
    .name		= "Atlantis",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (Atlantis, exit),
    StaticGameArray (Atlantis, line),
    StaticGameArray (Atlantis, beacon),
    StaticGameArray (Atlantis, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Killer

static const EXIT c_KillerGame_exits[] = {
    { 29,  7, DIR_WEST	},
    { 29, 17, DIR_WEST	},
    {  0,  7, DIR_EAST	},
    {  0,  0, DIR_SE	},
};
static const BEACON c_KillerGame_beacons[] = {
    { 12,  7, DIR_NORTH	},
    { 12, 17, DIR_NORTH	},
    { 14, 10, DIR_NORTH	},
    { 20, 15, DIR_NORTH	}
};
static const AIRPORT c_KillerGame_airports[] = {
    { 20, 18, DIR_EAST	},
};
static const LINE c_KillerGame_lines[] = {
    LineDef (1,1, 6,6),
    LineDef (12,1, 12,6),
    LineDef (13,7, 28,7),
    LineDef (28,1, 13,16),
    LineDef (1,13, 11,13),
    LineDef (12,8, 12,16),
    LineDef (11,18, 10,19),
    LineDef (13,17, 28,17),
    LineDef (1,7, 11,7)
};
static const C_SCREEN c_KillerGame = {
    .name		= "Killer",
    .width		= 30,
    .height		= 21,
    .update_secs	= 1,
    .newplane_time	= 4,
    StaticGameArray (Killer, exit),
    StaticGameArray (Killer, line),
    StaticGameArray (Killer, beacon),
    StaticGameArray (Killer, airport)
};

//}}}-------------------------------------------------------------------
//{{{ OHare

static const EXIT c_OHareGame_exits[] = {
    {  6,  0, DIR_SOUTH	},
    { 18,  0, DIR_SOUTH	},
    { 29,  5, DIR_WEST	},
    { 29, 13, DIR_WEST	},
    { 14, 20, DIR_NE	},
    {  6, 20, DIR_NORTH	},
};
static const BEACON c_OHareGame_beacons[] = {
    {  6,  5, DIR_NORTH	},
    { 18,  5, DIR_NORTH	},
    {  6, 13, DIR_NORTH	}
};
static const AIRPORT c_OHareGame_airports[] = {
    {  8,  8, DIR_EAST	},
};
static const LINE c_OHareGame_lines[] = {
    LineDef (6,1, 6,4),
    LineDef (18,1, 18,4),
    LineDef (6,6, 6,12),
    LineDef (6,14, 6,19),
    LineDef (28,6, 15,19),
    LineDef (7,13, 20,13),
    LineDef (22,13, 28,13),
    LineDef (7,5, 17,5),
    LineDef (19,5, 28,5)
};
static const C_SCREEN c_OHareGame = {
    .name		= "OHare",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (OHare, exit),
    StaticGameArray (OHare, line),
    StaticGameArray (OHare, beacon),
    StaticGameArray (OHare, airport)
};

//}}}-------------------------------------------------------------------
//{{{ TicTacToe

static const EXIT c_TicTacToeGame_exits[] = {
    { 10,  0, DIR_SOUTH	},
    { 19,  0, DIR_SOUTH	},
    { 29,  7, DIR_WEST	},
    { 29, 13, DIR_WEST	},
    { 19, 20, DIR_NORTH	},
    { 10, 20, DIR_NORTH	},
    {  0, 13, DIR_EAST	},
    {  0,  7, DIR_EAST	},
};
static const BEACON c_TicTacToeGame_beacons[] = {
    { 10,  7, DIR_NORTH	},
    { 19,  7, DIR_NORTH	},
    { 19, 13, DIR_NORTH	},
    { 10, 13, DIR_NORTH	}
};
static const LINE c_TicTacToeGame_lines[] = {
    LineDef (10,1, 10,6),
    LineDef (19,1, 19,6),
    LineDef (1,7, 9,7),
    LineDef (11,7, 18,7),
    LineDef (20,7, 28,7),
    LineDef (10,8, 10,12),
    LineDef (19,8, 19,12),
    LineDef (1,13, 9,13),
    LineDef (11,13, 18,13),
    LineDef (20,13, 28,13),
    LineDef (10,14, 10,19),
    LineDef (19,14, 19,19)
};
static const C_SCREEN c_TicTacToeGame = {
    .name		= "TicTacToe",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (TicTacToe, exit),
    StaticGameArray (TicTacToe, line),
    StaticGameArray (TicTacToe, beacon),
    NULL
};

//}}}-------------------------------------------------------------------
//{{{ Airports

static const EXIT c_AirportsGame_exits[] = {
    { 13,  0, DIR_SOUTH	},
    {  0, 10, DIR_EAST	},
};
static const BEACON c_AirportsGame_beacons[] = {
    {  6,  3, DIR_NORTH	},
    { 19,  4, DIR_NORTH	},
    { 27,  4, DIR_NORTH	},
    { 27, 10, DIR_NORTH	},
    { 27, 16, DIR_NORTH	},
    { 13, 16, DIR_NORTH	},
    {  6, 16, DIR_NORTH	},
    { 13, 10, DIR_NORTH	},
    { 19, 10, DIR_NORTH	}
};
static const AIRPORT c_AirportsGame_airports[] = {
    {  6,  5, DIR_NORTH	},
    { 23,  4, DIR_WEST	},
    { 19,  7, DIR_NORTH	},
    { 25, 10, DIR_EAST	},
    { 24, 16, DIR_WEST	},
    { 13, 13, DIR_SOUTH	},
    {  6, 13, DIR_NORTH	},
};
static const LINE c_AirportsGame_lines[] = {
    LineDef (13,1, 13,9),
    LineDef (13,11, 13,12),
    LineDef (13,14, 13,15),
    LineDef (7,16, 12,16),
    LineDef (18,5, 14,9),
    LineDef (6,14, 6,15),
    LineDef (6,11, 6,12),
    LineDef (6,6, 6,9),
    LineDef (1,10, 12,10),
    LineDef (27,5, 27,9),
    LineDef (27,11, 27,15)
};
static const C_SCREEN c_AirportsGame = {
    .name		= "Airports",
    .width		= 30,
    .height		= 21,
    .update_secs	= 6,
    .newplane_time	= 6,
    StaticGameArray (Airports, exit),
    StaticGameArray (Airports, line),
    StaticGameArray (Airports, beacon),
    StaticGameArray (Airports, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Box

static const EXIT c_BoxGame_exits[] = {
    {  0,  0, DIR_SE	},
    { 14,  0, DIR_SOUTH	},
    { 28,  0, DIR_SW	},
    { 28, 10, DIR_WEST	},
    { 28, 20, DIR_NW	},
    { 14, 20, DIR_NORTH	},
    {  0, 20, DIR_NE	},
    {  0, 10, DIR_EAST	},
};
static const BEACON c_BoxGame_beacons[] = {
    {  4,  4, DIR_NORTH	},
    { 14,  4, DIR_NORTH	},
    { 24,  4, DIR_NORTH	},
    { 24, 10, DIR_NORTH	},
    { 24, 16, DIR_NORTH	},
    { 14, 16, DIR_NORTH	},
    {  4, 16, DIR_NORTH	},
    {  4, 10, DIR_NORTH	},
    { 14, 13, DIR_NORTH	},
    { 14,  7, DIR_NORTH	}
};
static const AIRPORT c_BoxGame_airports[] = {
    {  9,  7, DIR_WEST	},
    { 19,  7, DIR_EAST	},
    { 19, 13, DIR_EAST	},
    {  9, 13, DIR_WEST	},
};
static const LINE c_BoxGame_lines[] = {
    LineDef (1,1, 3,3),
    LineDef (14,1, 14,3),
    LineDef (27,1, 25,3),
    LineDef (5,4, 13,4),
    LineDef (15,4, 23,4),
    LineDef (4,5, 4,9),
    LineDef (14,5, 14,6),
    LineDef (24,5, 24,9),
    LineDef (10,7, 13,7),
    LineDef (15,7, 18,7),
    LineDef (14,8, 14,9),
    LineDef (1,10, 3,10),
    LineDef (5,10, 23,10),
    LineDef (25,10, 27,10),
    LineDef (4,11, 4,15),
    LineDef (14,11, 14,12),
    LineDef (24,11, 24,15),
    LineDef (10,13, 13,13),
    LineDef (15,13, 18,13),
    LineDef (14,14, 14,15),
    LineDef (5,16, 13,16),
    LineDef (15,16, 23,16),
    LineDef (3,17, 1,19),
    LineDef (14,17, 14,19),
    LineDef (25,17, 27,19)
};
static const C_SCREEN c_BoxGame = {
    .name		= "Box",
    .width		= 29,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 6,
    StaticGameArray (Box, exit),
    StaticGameArray (Box, line),
    StaticGameArray (Box, beacon),
    StaticGameArray (Box, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Crosshatch

static const EXIT c_CrosshatchGame_exits[] = {
    {  0, 10, DIR_EAST	},
    {  6,  0, DIR_SOUTH	},
    { 12,  0, DIR_SOUTH	},
    { 18,  0, DIR_SOUTH	},
    { 24,  0, DIR_SOUTH	},
    { 29, 10, DIR_WEST	},
    { 24, 20, DIR_NORTH	},
    { 18, 20, DIR_NORTH	},
    { 12, 20, DIR_NORTH	},
    {  6, 20, DIR_NORTH	}
};
static const BEACON c_CrosshatchGame_beacons[] = {
    {  6, 10, DIR_NORTH	},
    { 12, 10, DIR_NORTH	},
    { 18, 10, DIR_NORTH	},
    { 24, 10, DIR_NORTH	},
    {  6,  5, DIR_NORTH	},
    { 12,  5, DIR_NORTH	},
    { 18,  5, DIR_NORTH	},
    { 24,  5, DIR_NORTH	},
    { 12, 15, DIR_NORTH	},
    { 18, 15, DIR_NORTH	}
};
static const AIRPORT c_CrosshatchGame_airports[] = {
    {  9, 15, DIR_WEST	},
    { 21, 15, DIR_EAST	},
    { 15,  5, DIR_EAST	}
};
static const LINE c_CrosshatchGame_lines[] = {
    LineDef (6,1, 6,4),
    LineDef (12,1, 12,4),
    LineDef (18,1, 18,4),
    LineDef (24,1, 24,4),
    LineDef (6,6, 6,9),
    LineDef (12,6, 12,9),
    LineDef (18,6, 18,9),
    LineDef (24,6, 24,9),
    LineDef (12,11, 12,14),
    LineDef (18,11, 18,14),
    LineDef (6,11, 6,19),
    LineDef (24,11, 24,19),
    LineDef (12,16, 12,19),
    LineDef (18,16, 18,19),
    LineDef (7,5, 11,5),
    LineDef (19,5, 23,5),
    LineDef (13,15, 17,15),
    LineDef (1,10, 5,10),
    LineDef (7,10, 11,10),
    LineDef (13,10, 17,10),
    LineDef (19,10, 23,10),
    LineDef (25,10, 29,10)
};
static const C_SCREEN c_CrosshatchGame = {
    .name		= "Crosshatch",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (Crosshatch, exit),
    StaticGameArray (Crosshatch, line),
    StaticGameArray (Crosshatch, beacon),
    StaticGameArray (Crosshatch, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Crossover

static const EXIT c_CrossoverGame_exits[] = {
    {  0,  0, DIR_SE	},
    {  8,  0, DIR_SE	},
    { 20,  0, DIR_SW	},
    { 28,  0, DIR_SW	},
    { 28, 20, DIR_NW	},
    { 20, 20, DIR_NW	},
    {  8, 20, DIR_NE	},
    {  0, 20, DIR_NE	}
};
static const BEACON c_CrossoverGame_beacons[] = {
    { 14,  6, DIR_NORTH	},
    { 18, 10, DIR_NORTH	},
    { 14, 14, DIR_NORTH	},
    { 10, 10, DIR_NORTH	}
};

static const LINE c_CrossoverGame_lines[] = {
    LineDef (0,0, 20,20),
    LineDef (8,0, 28,20),
    LineDef (20,0, 0,20),
    LineDef (28,0, 8,20)
};
static const C_SCREEN c_CrossoverGame = {
    .name		= "Crossover",
    .width		= 29,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (Crossover, exit),
    StaticGameArray (Crossover, line),
    StaticGameArray (Crossover, beacon),
    NULL
};

//}}}-------------------------------------------------------------------
//{{{ Easy

static const EXIT c_EasyGame_exits[] = {
    {  7,  0, DIR_SOUTH	},
    { 14,  0, DIR_SW	},
    { 12, 14, DIR_NW	},
    {  0, 14, DIR_NE	}
};
static const BEACON c_EasyGame_beacons[] = {
    { 12,  7, DIR_NORTH	}
};
static const AIRPORT c_EasyGame_airports[] = {
    {  7,  8, DIR_NORTH	}
};
static const LINE c_EasyGame_lines[] = {
    LineDef (1,1, 6,6),
    LineDef (7,9, 12,14),
    LineDef (7,0, 7,14),
    LineDef (1,7, 11,7)
};
static const C_SCREEN c_EasyGame = {
    .name		= "Easy",
    .width		= 15,
    .height		= 15,
    .update_secs	= 7,
    .newplane_time	= 12,
    StaticGameArray (Easy, exit),
    StaticGameArray (Easy, line),
    StaticGameArray (Easy, beacon),
    StaticGameArray (Easy, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Game2

static const EXIT c_Game2Game_exits[] = {
    { 12,  0, DIR_SOUTH	},
    { 29,  0, DIR_SW	},
    { 29,  6, DIR_WEST	},
    { 29, 13, DIR_WEST	},
    {  9, 20, DIR_NE	},
    {  0, 13, DIR_EAST	},
    {  0,  6, DIR_EAST	},
    {  0,  0, DIR_SE	}
};
static const BEACON c_Game2Game_beacons[] = {
    { 12, 17, DIR_NORTH	},
    { 23,  6, DIR_NORTH	},
    { 23, 13, DIR_NORTH	},
    { 25, 17, DIR_NORTH	},
    { 12,  6, DIR_NORTH	},
    { 12, 13, DIR_NORTH	},
    {  6,  6, DIR_NORTH	}
};
static const AIRPORT c_Game2Game_airports[] = {
    { 18, 17, DIR_EAST	}
};
static const LINE c_Game2Game_lines[] = {
    LineDef (1,1, 16,16),
    LineDef (1,6, 28,6),
    LineDef (12,1, 12,17),
    LineDef (10,19, 28,1),
    LineDef (13,17, 17,17),
    LineDef (1,13, 28,13),
    LineDef (19,17, 24,17),
    LineDef (19,17, 22,14),
    LineDef (26,16, 28,14)
};
static const C_SCREEN c_Game2Game = {
    .name		= "Game2",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 8,
    StaticGameArray (Game2, exit),
    StaticGameArray (Game2, line),
    StaticGameArray (Game2, beacon),
    StaticGameArray (Game2, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Game3

static const EXIT c_Game3Game_exits[] = {
    { 12,  0, DIR_SOUTH	},
    {  0,  6, DIR_EAST	},
    { 29, 12, DIR_WEST	},
    { 26, 20, DIR_NW	}
};
static const BEACON c_Game3Game_beacons[] = {
    { 12,  6, DIR_NORTH	}
};
static const AIRPORT c_Game3Game_airports[] = {
    {  8, 11, DIR_SOUTH	}
};
static const LINE c_Game3Game_lines[] = {
    LineDef (12,1, 12,5),
    LineDef (1,6, 11,6),
    LineDef (8,7, 8,10),
    LineDef (28,12, 19,12),
    LineDef (13,7, 25,19)
};
static const C_SCREEN c_Game3Game = {
    .name		= "Game3",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (Game3, exit),
    StaticGameArray (Game3, line),
    StaticGameArray (Game3, beacon),
    StaticGameArray (Game3, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Game4

static const EXIT c_Game4Game_exits[] = {
    {  9,  0, DIR_SE	},
    { 29,  0, DIR_SW	},
    { 29, 20, DIR_NW	},
    {  9, 20, DIR_NE	},
    {  0, 20, DIR_NE	},
    {  0, 10, DIR_EAST	},
    {  0,  0, DIR_SE	}
};
static const BEACON c_Game4Game_beacons[] = {
    {  5,  5, DIR_NORTH	},
    { 14,  5, DIR_NORTH	},
    { 24,  5, DIR_NORTH	},
    { 24,  9, DIR_NORTH	},
    { 24, 11, DIR_NORTH	},
    { 24, 15, DIR_NORTH	},
    { 14, 15, DIR_NORTH	},
    {  5, 15, DIR_NORTH	},
    {  5, 10, DIR_NORTH	},
    { 14, 10, DIR_NORTH	}
};
static const AIRPORT c_Game4Game_airports[] = {
    { 19,  9, DIR_WEST	},
    { 19, 11, DIR_WEST	}
};
static const LINE c_Game4Game_lines[] = {
    LineDef (1,1, 4,4),
    LineDef (10,1, 13,4),
    LineDef (28,1, 25,4),
    LineDef (6,5, 13,5),
    LineDef (15,5, 23,5),
    LineDef (1,10, 13,10),
    LineDef (15,10, 17,10),
    LineDef (18,9, 18,9),
    LineDef (18,11, 18,11),
    LineDef (20,9, 23,9),
    LineDef (20,11, 23,11),
    LineDef (6,15, 13,15),
    LineDef (15,15, 24,15),
    LineDef (1,19, 4,16),
    LineDef (10,19, 13,16),
    LineDef (28,19, 25,16),
    LineDef (5,6, 5,9),
    LineDef (5,11, 5,14),
    LineDef (14,6, 14,9),
    LineDef (14,11, 14,14),
    LineDef (24,6, 24,8),
    LineDef (24,10, 24,10),
    LineDef (24,12, 24,14)
};
static const C_SCREEN c_Game4Game = {
    .name		= "Game4",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (Game4, exit),
    StaticGameArray (Game4, line),
    StaticGameArray (Game4, beacon),
    StaticGameArray (Game4, airport)
};

//}}}-------------------------------------------------------------------
//{{{ Novice

static const EXIT c_NoviceGame_exits[] = {
    {  0,  2, DIR_SE	},
    { 29,  2, DIR_SW	},
    { 29, 18, DIR_NW	},
    {  0, 18, DIR_NE	}
};
static const BEACON c_NoviceGame_beacons[] = {
    {  8, 10, DIR_NORTH	},
    { 21, 10, DIR_NORTH	}
};
static const LINE c_NoviceGame_lines[] = {
    LineDef (1,3, 7,9),
    LineDef (7,11, 1,17),
    LineDef (28,3, 22,9),
    LineDef (22,11, 28,17),
    LineDef (9,10, 20,10)
};
static const C_SCREEN c_NoviceGame = {
    .name		= "Novice",
    .width		= 30,
    .height		= 21,
    .update_secs	= 6,
    .newplane_time	= 6,
    StaticGameArray (Novice, exit),
    StaticGameArray (Novice, line),
    StaticGameArray (Novice, beacon),
    NULL
};

//}}}-------------------------------------------------------------------
//{{{ TwoCorners

static const EXIT c_TwoCornersGame_exits[] = {
    {  0,  0, DIR_SE	},
    { 10,  0, DIR_SOUTH	},
    { 29, 10, DIR_WEST	},
    { 29, 20, DIR_NW	},
    { 19, 20, DIR_NORTH	},
    {  0, 10, DIR_EAST	}
};
static const BEACON c_TwoCornersGame_beacons[] = {
    { 10, 10, DIR_NORTH	},
    { 19, 10, DIR_NORTH	}
};
static const AIRPORT c_TwoCornersGame_airports[] = {
    { 15, 15, DIR_SOUTH	}
};
static const LINE c_TwoCornersGame_lines[] = {
    LineDef (1,1, 9,9),
    LineDef (10,1, 10,9),
    LineDef (1,10, 9,10),
    LineDef (11,10, 18,10),
    LineDef (15,11, 15,14),
    LineDef (20,10, 28,10),
    LineDef (19,11, 19,19),
    LineDef (20,11, 28,19)
};
static const C_SCREEN c_TwoCornersGame = {
    .name		= "TwoCorners",
    .width		= 30,
    .height		= 21,
    .update_secs	= 5,
    .newplane_time	= 5,
    StaticGameArray (TwoCorners, exit),
    StaticGameArray (TwoCorners, line),
    StaticGameArray (TwoCorners, beacon),
    StaticGameArray (TwoCorners, airport)
};

//}}}-------------------------------------------------------------------

static const C_SCREEN* c_Games[] = {
    &c_DefaultGame,
    &c_AtlantisGame,
    &c_KillerGame,
    &c_OHareGame,
    &c_TicTacToeGame,
    &c_AirportsGame,
    &c_BoxGame,
    &c_CrosshatchGame,
    &c_CrossoverGame,
    &c_EasyGame,
    &c_Game2Game,
    &c_Game3Game,
    &c_Game4Game,
    &c_NoviceGame,
    &c_TwoCornersGame
};

static unsigned game_by_name (const char* name)
{
    for (unsigned i = 0; i < ArraySize(c_Games); ++i)
	if (0 == strcmp (name, c_Games[i]->name))
	    return i;
    return UINT_MAX;
}

int load_game (const char *s)
{
    unsigned gamei = game_by_name (s);
    if (gamei >= ArraySize(c_Games))
	return -1;
    sp = c_Games[gamei];
    return 0;
}

const char* default_game (void)
{
    assert (ArraySize(c_Games) && "no games included with project?");
    return c_Games[0]->name;
}

const char* okay_game (const char *s)
{
    return game_by_name(s) < ArraySize(c_Games) ? s : NULL;
}

void list_games (void)
{
    assert (ArraySize(c_Games) && "no games included with project?");
    puts ("Available games:");
    for (unsigned i = 0; i < ArraySize(c_Games); ++i)
	printf ("\t%s\n", c_Games[i]->name);
}
