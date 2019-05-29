#ifndef EVENTS_H_INCLUDED
#include "Header.h"
#define EVENTS_H_INCLUDED

//!Events.c
//!Egy adott teglalapon belul kattint
bool negyzetenbelul(SDL_Event event, int x, int y, int w, int h);

//!Szoveg kezelo event fuggveny
bool text(SDL_Event e, char *szoveg);

//!A jatekallas betoltese
void Betoltes(Field *mezo, Ido *noves, char *jatekosnev, int *nevhossz, int *fieldx, int *fieldy);

//!Jatek kozben ultetes
void ultetesadat(Field *mezo, Ido *noves, int fieldx, int fieldy, SDL_Event menuevent, int noveny);

void megnotte(Field *mezo, Ido *noves, int fieldx, int fieldy);

void arat(Field *mezo, Ido *noves, int fieldx, int fieldy, SDL_Event menuevent, char *jatekosnev, int nevhossz);


#endif // EVENTS_H_INCLUDED
