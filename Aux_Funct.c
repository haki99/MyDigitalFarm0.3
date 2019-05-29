#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "Headers\Aux_Funct.h"
#include "Headers\Header.h"


void closeall(SDL_Surface* kep, SDL_Window* Window)
{
	SDL_FreeSurface( kep );
	kep = NULL;

	SDL_DestroyWindow( Window );
	Window = NULL;

	SDL_Quit();
	SDL_StopTextInput();
}

void nev(char *jatekosnev, char *valami, int *nevhossz)
{
    (*nevhossz)++;
    jatekosnev = realloc(jatekosnev, *nevhossz * sizeof(char));
    strcat(jatekosnev, valami);
}

//!Matrix kezelo fuggvenyek
void nullaz(Field *m)
{
    for (int y = 0; y < m->magas; ++y)
    {
        for (int x = 0; x < m->szeles; ++x)
        {
            m->adat[y][x] = 0;
        }
    }
}

void nullazido(Ido *t)
{
    int x, y;
    for (y = 0; y < t->magas; ++y)
    {
        for (x = 0; x < t->szeles; ++x)
        {
            t->adat[y][x] = 0;
        }
    }
}

void foglalido(Ido *t, int szeles, int magas)
{
    t->szeles = szeles;
    t->magas = magas;
    t->adat = (int**) malloc(sizeof(int*) * magas);
    int y;
    for (y = 0; y < magas; ++y)
    {
        //!Azert 10 mert annyiba biztosan belefer hogy az evben melyik masodpercnel jarunk
        t->adat[y] = (int*) malloc(sizeof(int) * szeles * 10);
    }
}

void foglal(Field *m, int const fieldx, int const fieldy)
{
    m->szeles = fieldx;
    m->magas = fieldy;
    m->adat = (int**) malloc(sizeof(int*) * fieldy);
    for (int y = 0; y < fieldy; ++y)
    {
        m->adat[y] = (int*) malloc(sizeof(int) * fieldx);
    }
}
