#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "Headers\File_Management.h"
#include "Headers\Header.h"


//!Log fajl letrehozasa
void logfile()
{
    //!Mindig az aktualis ido beszurasa
    time_t curtime;
    time(&curtime);

    FILE *log;
    log = fopen("log.txt", "w");


    fprintf(log, "%sLog inditasa \n", ctime(&curtime));
}


//!Szimpla logolas a fajlba egy char tombon keresztul
void writelog(char *tomb)
{
    FILE *log;
    log = fopen("log.txt", "a");

    time_t curtime;
    time(&curtime);

    fprintf(log, "%s%s\n", ctime(&curtime), tomb);
}


//!SDL logolas egy char tombon keresztul
void SDLwritelog(char *tomb)
{
    FILE *log;
    log = fopen("log.txt", "a");

    time_t curtime;
    time(&curtime);

    fprintf(log, "%s%s%s\n", ctime(&curtime), tomb, SDL_GetError());
}

//!Log fajl bezarasa
void logfileclose()
{
    FILE *log;
    log = fopen("log.txt", "w");
    fclose(log);
}

void Mentes(Field *mezo, Ido *noves, int nevhossz, char *jatekosnev, int fieldx, int fieldy)
{
    FILE *f;
    f = fopen("save.txt", "wt");
    fprintf(f, "%d\n", nevhossz);
    fprintf(f, "%s\n", jatekosnev);
    fprintf(f, "%d\n", fieldx);
    fprintf(f, "%d\n", fieldy);
    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            fprintf(f, "%1d", mezo->adat[i][j]);
        }
    }
    fprintf(f, "\n");

    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            fprintf(f, "%d\n", noves->adat[i][j]);
        }
    }
    fclose(f);
}
