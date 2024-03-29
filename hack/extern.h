// Copyright (c) 1985, Stichting Centrum voor Wiskunde en Informatica,
// Copyright (c) 1982 Jay Fenlason <hack@gnu.org>
// This file is free software, distributed under the BSD license.

#pragma once
#include "../config.h"

// alloc.c
long *alloc(unsigned);
long *enlarge(char *, unsigned);

// apply.c
int doapply(void);
int holetime(void);
void dighole(void);

// bones.c
void savebones(void);
int getbones(void);

// hack.c
void unsee(void);
void seeoff(int);
void domove(void);
void movobj(struct obj *, int, int);
int dopickup(void);
void pickup(int);
void lookaround(void);
int monster_nearby(void);
int rroom(int, int);
int cansee(int, int);
int sgn(int);
void setsee(void);
void nomul(int);
int abon(void);
int dbon(void);
void losestr(int);
void losehp(int, const char *);
void losehp_m(int, struct monst *);
void losexp(void);
int inv_weight(void);
int inv_cnt(void);
long newuexp(void);

// cmd.c
void rhack(const char *);
int doextcmd(void);
char lowc(int);
char unctrl(int);
int movecmd(int);
int getdir(bool);
void confdir(void);
int finddir(void);
int isroom(int, int);
int isok(int, int);

// do.c
int dodrop(void);
void dropx(struct obj *);
void dropy(struct obj *);
int doddrop(void);
int dodown(void);
int doup(void);
void goto_level(int, bool);
int donull(void);
int dopray(void);
int dothrow(void);
struct obj *splitobj(struct obj *, int);
void more_experienced(int, int);
void set_wounded_legs(long, int);
void heal_legs(void);

// do_name.c
coord getpos(int, const char *);
int do_mname(void);
void do_oname(struct obj *);
int ddocall(void);
void docall(struct obj *);
char *xmonnam(struct monst *, int);
char *lmonnam(struct monst *);
char *monnam(struct monst *);
char *Monnam(struct monst *);
char *amonnam(struct monst *, const char *);
char *Amonnam(struct monst *, const char *);
char *Xmonnam(struct monst *);
char *visctrl(int);

// do_wear.c
void off_msg(struct obj *);
int doremarm(void);
int doremring(void);
int dorr(struct obj *);
int cursed(struct obj *);
int armoroff(struct obj *);
int doweararm(void);
int dowearring(void);
void ringoff(struct obj *);
void find_ac(void);
void glibr(void);
struct obj *some_armor(void);
void corrode_armor(void);

// dog.c
void makedog(void);
void initedog(struct monst *);
void losedogs(void);
void keepdogs(void);
void fall_down(struct monst *);
int dogfood(struct obj *);
int dog_move(struct monst *, int);
int inroom(int, int);
int tamedog(struct monst *, struct obj *);

// eat.c
void init_uhunger(void);
int opentin(void);
int Meatdone(void);
int doeat(void);
void gethungry(void);
void morehungry(int);
void lesshungry(int);
int unfaint(void);
void newuhs(bool);
int poisonous(struct obj *);
int eatcorpse(struct obj *);

// end.c
int dodone(void);
void done1(int);
void done_intr(int);
void done_hangup(int);
void done_in_by(struct monst *);
void done(const char *);
void topten(void);
void outheader(void);
struct toptenentry;
int outentry(int, struct toptenentry *, int);
char *itoa(int);
const char *ordin(int);
void clearlocks(void);
void hangup(int) NORETURN;
char *eos(char *);
void charcat(char *, int);
void prscore(int, char **);

// engrave.c
struct engr *engr_at(int x, int y);
int sengr_at(const char *s, int x, int y);
void u_wipe_engr(int cnt);
void wipe_engr_at(int x, int y, int cnt);
void read_engr_at(int x, int y);
void make_engr_at(int x, int y, const char *s);
int doengrave(void);
void save_engravings(int fd);
void rest_engravings(int fd);
void del_engr(struct engr *ep);

// fight.c
int hitmm(struct monst *, struct monst *);
void mondied(struct monst *);
void monstone(struct monst *);
int fightm(struct monst *);
int thitu(int, int, const char *);
bool hmon(struct monst *, struct obj *, int);
int attack(struct monst *);

// invent.c
struct obj *addinv(struct obj *);
void useup(struct obj *);
void freeinv(struct obj *);
void delobj(struct obj *);
void freeobj(struct obj *);
void freegold(struct gold *);
void deltrap(struct trap *);
struct monst *m_at(int, int);
struct obj *o_at(int, int);
struct obj *sobj_at(int, int, int);
int carried(struct obj *);
int carrying(int);
struct obj *o_on(unsigned int, struct obj *);
struct trap *t_at(int, int);
struct gold *g_at(int, int);
struct obj *mkgoldobj(long);
struct obj *getobj(const char *, const char *);
int ckunpaid(struct obj *);
int ggetobj(const char *, int (*fn) (struct obj *), int);
int askchain(struct obj *, char *, int, int (*)(struct obj *), int (*)(struct obj *), int);
char obj_to_let(struct obj *);
void prinv(struct obj *);
int ddoinv(void);
void doinv(char *);
int dotypeinv(void);
int dolook(void);
void stackobj(struct obj *);
int merged(struct obj *, struct obj *, int);
int countgold(void);
int doprgold(void);
int doprwep(void);
int doprarm(void);
int doprring(void);
int digit(int);

// ioctl.c
void getioctls(void);
void setioctls(void);
int dosuspend(void);

// lev.c
void savelev(int, int);
void bwrite(int, const void *, unsigned);
void saveobjchn(int, struct obj *);
void savemonchn(int, struct monst *);
void savegoldchn(int, struct gold *);
void savetrapchn(int, struct trap *);
void getlev(int, int, int);
void mread(int, char *, unsigned);
void mklev(void);

// main.c
void glo(int);
void askname(void);
void impossible(const char *, ...) PRINTFLIKE(1,2);
void stop_occupation(void);

// makemon.c
struct monst *makemon(const struct permonst *, int, int);
coord enexto(int, int);
int goodpos(int, int);
void rloc(struct monst *);
struct monst *mkmon_at(int, int, int);

// mhitu.c
int mhitu(struct monst *);
int hitu(struct monst *, int);

// mklev.c
void makelevel(void);
int makerooms(void);
void addrs(int, int, int, int);
void addrsx(int, int, int, int, bool);
struct mkroom;
int comp(const void *, const void *);
coord finddpos(int, int, int, int);
int okdoor(int, int);
void dodoor(int, int, struct mkroom *);
void dosdoor(int, int, struct mkroom *, int);
int maker(int, int, int, int);
void makecorridors(void);
void join(int, int);
void make_niches(void);
void makevtele(void);
void makeniche(bool);
void mktrap(int, int, struct mkroom *);

// mkmaze.c
void makemaz(void);
void walkfrom(int, int);
void move(int *, int *, int);
int okay(int, int, int);
coord mazexy(void);

// mkobj.c
struct obj *mkobj_at(int, int, int);
void mksobj_at(int, int, int);
struct obj *mkobj(int);
struct obj *mksobj(int);
int letter(int);
int weight(struct obj *);
void mkgold(long, int, int);

// mkshop.c
void mkshop(void);
void mkzoo(int);
const struct permonst *morguemon(void);
void mkswamp(void);
int nexttodoor(int, int);
int has_dnstairs(struct mkroom *);
int has_upstairs(struct mkroom *);
int isbig(struct mkroom *);
int dist2(int, int, int, int);
int sq(int);

// mon.c
void movemon(void);
void justswld(struct monst *, const char *);
void youswld(struct monst *, int, int, const char *);
int dochugw(struct monst *);
int dochug(struct monst *);
int m_move(struct monst *, int);
void mpickgold(struct monst *);
void mpickgems(struct monst *);
int mfndpos(struct monst *, coord[9], int[9], int);
int dist(int, int);
void poisoned(const char *, const char *);
void mondead(struct monst *);
void replmon(struct monst *, struct monst *);
void relmon(struct monst *);
void monfree(struct monst *);
void dmonsfree(void);
void unstuck(struct monst *);
void killed(struct monst *);
void kludge(const char *, const char *);
void rescham(void);
int newcham(struct monst *, const struct permonst *);
void mnexto(struct monst *);
int ishuman(struct monst *);
void setmangry(struct monst *);
int canseemon(struct monst *);

// monst.c

// o_init.c
int letindex(int);
void init_objects(void);
int probtype(int);
void setgemprobs(void);
void oinit(void);
void savenames(int);
void restnames(int);
int dodiscovered(void);
int interesting_to_discover(int);

// objnam.c
char *strprepend(char *, char *);
char *sitoa(int);
char *typename(int);
char *xname(struct obj *);
char *doname(struct obj *);
void setan(const char *, char *);
char *aobjnam(struct obj *, const char *);
char *Doname(struct obj *);
struct obj *readobjnam(char *);

// options.c
void initoptions(void);
void parseoptions(char *, bool);
int doset(void);

// pager.c
int dowhatis(void);
void intruph(int);
void page_more(FILE *, int);
void set_whole_screen(void);
int readnews(void);
void set_pager(int);
int page_line(const char *);
void cornline(int, const char *);
int dohelp(void);
int page_file(const char *, bool);
int dosh(void);
int child(int);

// potion.c
int dodrink(void);
void pluslvl(void);
void strange_feeling(struct obj *, const char *);
void potionhit(struct monst *, struct obj *);
void potionbreathe(struct obj *);
int dodip(void);
void ghost_from_bottle(void);

// pri.c
void swallowed(void);
void panic(const char *, ...) PRINTFLIKE(1,2);
void atl(int, int, int);
void on_scr(int, int);
void tmp_at(int, int);
void Tmp_at(int, int);
void setclipped(void) NORETURN;
void at(int, int, int);
void prme(void);
int doredraw(void);
void docrt(void);
void docorner(int, int);
void curs_on_u(void);
void pru(void);
void prl(int, int);
char news0(int, int);
void newsym(int, int);
void mnewsym(int, int);
void nosee(int, int);
void prl1(int, int);
void nose1(int, int);
int vism_at(int, int);
void pobj(struct obj *);
void unpobj(struct obj *);
void seeobjs(void);
void seemons(void);
void pmon(struct monst *);
void unpmon(struct monst *);
void nscr(void);
void cornbot(int);
void bot(void);
void mstatusline(struct monst *);
void cls(void);

// read.c
int doread(void);
int identify(struct obj *);
void litroom(bool);
int monstersym(int);

// rip.c
void outrip(void);
void center(int, char *);

// rumors.c
void init_rumors(FILE *);
int skipline(FILE *);
void outline(FILE *);
void outrumor(void);
int used(int);

// save.c
int dosave(void);
int dosave0(int);
int dorecover(int);
struct obj *restobjchn(int);
struct monst *restmonchn(int);

// search.c
int findit(void);
int dosearch(void);
int doidtrap(void);
void wakeup(struct monst *);
void seemimic(struct monst *);

// shk.c
void obfree(struct obj *, struct obj *);
void paybill(void);
char *shkname(struct monst *);
void shkdead(struct monst *);
void replshk(struct monst *, struct monst *);
int inshop(void);
int dopay(void);
struct bill_x;
struct obj *bp_to_obj(struct bill_x *);
void addtobill(struct obj *);
void splitbill(struct obj *, struct obj *);
void subfrombill(struct obj *);
int doinvbill(int);
int shkcatch(struct obj *);
int shk_move(struct monst *);
void shopdig(int);
int online(int, int);
int follower(struct monst *);

// shknam.c
void findname(char *, int);

// steal.c
long somegold(void);
void stealgold(struct monst *);
int stealarm(void);
int steal(struct monst *);
void mpickobj(struct monst *, struct obj *);
int stealamulet(struct monst *);
void relobj(struct monst *, int);

// termcap.c
void startup(void);
void start_screen(void);
void end_screen(void);
void curs(int, int);
void nocmov(int, int);
void cmov(int, int);
int xputc(int);
void xputs(char *);
void cl_end(void);
void clear_screen(void);
void home(void);
void standoutbeg(void);
void standoutend(void);
void backsp(void);
void bell(void);
void delay_output(void);
void cl_eos(void);

// timeout.c
void timeout(void);
void stoned_dialogue(void);

// topl.c
int doredotopl(void);
void redotoplin(void);
void remember_topl(void);
void addtopl(const char *);
void xmore(const char *);
void more(void);
void cmore(const char *);
void clrlin(void);
void pline(const char *, ...) PRINTFLIKE(1,2);
void vpline(const char *, va_list) PRINTFLIKE(1,0);
void putsym(int);
void putstr(const char *);

// track.c
void initrack(void);
void settrack(void);
coord *gettrack(int, int);

// trap.c
struct trap *maketrap(int, int, int);
void dotrap(struct trap *);
int mintrap(struct monst *);
void selftouch(const char *);
void float_up(void);
void float_down(void);
void vtele(void);
void tele(void);
void teleds(int, int);
int teleok(int, int);
int dotele(void);
void placebc(int);
void unplacebc(void);
void level_tele(void);
void drown(void);

// tty.c
void gettty(void);
void settty(const char *);
void setctty(void);
void setftty(void);
void error(const char *, ...) PRINTFLIKE(1,2) NORETURN;
void getlin(char *);
void getret(void);
void cgetret(const char *);
void xwaitforspace(const char *);
char *parse(void);
char readchar(void);
void end_of_input(void) NORETURN;

// u_init.c
void u_init(void);
struct trobj;
void ini_inv(struct trobj *);
void wiz_inv(void);
void plnamesuffix(void);
int role_index(int);

// unix.c
void setrandom(void);
struct tm *getlt(void);
int getyear(void);
const char* getdatestr (void);
int phase_of_the_moon(void);
int night(void);
int midnight(void);
void gethdate(char *);
int uptodate(int);
int veryold(int);
void getlock(void);
void getmailstatus(void);
void ckmailstatus(void);
void newmail(void);
void mdrush(struct monst *, bool);
void readmail(void);
void regularize(char *);

// vault.c
void setgd(void);
int gd_move(void);
void gddead(void);
void replgd(struct monst *, struct monst *);
void invault(void);

// version.c
int doversion(void);

// wield.c
void setuwep(struct obj *);
int dowield(void);
void corrode_weapon(void);
int chwepon(struct obj *, int);

// wizard.c
void amulet(void);
int wiz_hit(struct monst *);
void inrange(struct monst *);
void aggravate(void);
void clonewiz(struct monst *);

// worm.c
#ifndef NOWORM
int getwn(struct monst *);
void initworm(struct monst *);
void worm_move(struct monst *);
void worm_nomove(struct monst *);
void wormdead(struct monst *);
void wormhit(struct monst *);
void wormsee(unsigned);
struct wseg;
void pwseg(struct wseg *);
void cutworm(struct monst *, int, int, int);
void remseg(struct wseg *);
#endif

// worn.c
void setworn(struct obj *, long);
void setnotworn(struct obj *);

// zap.c
void bhitm(struct monst *, struct obj *);
int bhito(struct obj *, struct obj *);
int dozap(void);
const char *exclam(int);
void hit(const char *, struct monst *, const char *);
void miss(const char *, struct monst *);
struct monst *bhit(int, int, int, int, void (*)(struct monst *, struct obj *), int (*)(struct obj *, struct obj *), struct obj *);
struct monst *boomhit(int, int);
char dirlet(int, int);
void buzz(int, int, int, int, int);
int zhit(struct monst *, int);
int revive(struct obj *);
void rloco(struct obj *);
void fracture_rock(struct obj *);
void burn_scrolls(void);

// rnd.c
int rn1(int, int);
int rn2(int);
int rnd(int);
int d(int, int);
