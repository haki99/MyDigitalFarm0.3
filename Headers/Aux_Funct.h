#ifndef AUX_FUNCT_H_INCLUDED
#include "Header.h"
#define AUX_FUNCT_H_INCLUDED

//!Aux_Funct.c
//!nevbe iras
void nev(char *jatekosnev, char *valami, int *nevhossz);

//!Bezaro fuggveny
void closeall(SDL_Surface* kep, SDL_Window* Window);

//!Struktura kezelo fuggvenyek
void nullaz(Field *m);
void foglal(Field *m, int szeles, int magas);
void nullazido(Ido *t);
void foglalido(Ido *t, int szeles, int magas);

#endif // AUX_FUNCT_H_INCLUDED
