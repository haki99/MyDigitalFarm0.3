#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "Headers\Events.h"
#include "Headers\Header.h"
#include "Headers\Aux_Funct.h"
#include "Headers\Media.h"


bool negyzetenbelul(SDL_Event event, int x, int y, int w, int h)
{
    int x2 = event.button.x;
    int y2 = event.button.y;
    if( ( x2 > x ) && ( x2 < w ) && ( y2 > y ) && ( y2 < h ) ) return true;
    else return false;
}

bool text(SDL_Event e, char *szoveg)
{
    if( e.type == SDL_KEYDOWN )
    {
        if( e.key.keysym.sym == SDLK_BACKSPACE && szoveg != 0 )
        {
            int hossz = strlen(szoveg);
            szoveg[hossz-1] = '\0';
            return true;
        }
        else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( szoveg );
        }
        else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            szoveg = SDL_GetClipboardText();
            return true;
        }
    }
    else if( e.type == SDL_TEXTINPUT )
    {
        strcat(szoveg, e.text.text);
        return true;
    }

    return true;
}

void betoltesultetes(Field *mezo, Ido *noves, int fieldx, int fieldy)
{
    int x = 345;
    int y = 235;
    int noveny = 0;

    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int curtime = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;

    for (int y = 0; y < fieldy; ++y)
    {
        for (int x = 0; x < fieldx; ++x)
        {
            if(((curtime - noves->adat[y][x]) > 20)  && noves->adat[y][x] != 0 && noves->adat[y][x] <= 4)
            {
                mezo->adat[y][x] += 4;
            }
        }
    }

    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            if(mezo->adat[i][j] == 1)
            {
                noveny = 1;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 2)
            {
                noveny = 2;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 3)
            {
                noveny = 3;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 4)
            {
                noveny = 4;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 5)
            {
                noveny = 5;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 6)
            {
                noveny = 6;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 7)
            {
                noveny = 7;
                ultetes(noveny, x, y);
            }
            if(mezo->adat[i][j] == 8)
            {
                noveny = 8;
                ultetes(noveny, x, y);
            }
            x = x + 60;
        }
        if(x == 345 + fieldx*60) x = 375;
        else x = 345;
        y += 25;
    }
}

void Betoltes(Field *mezo, Ido *noves, char *jatekosnev, int *nevhossz, int *fieldx, int *fieldy)
{
    FILE *file;
    file = fopen("save.txt","rt");

    fscanf(file, "%d", nevhossz);

    fscanf(file, "%s", jatekosnev);

    fscanf(file, "%d", fieldx);

    fscanf(file, "%d", fieldy);

    foglal(mezo, *fieldx, *fieldy);

    for (int y = 0; y < *fieldy; ++y)
    {
        for (int x = 0; x < *fieldx; ++x)
        {
            fscanf(file, "%1d", &mezo->adat[y][x]);
        }
    }

    foglalido(noves, *fieldx, *fieldy);

    for (int y = 0; y < *fieldy; ++y)
    {
        for (int x = 0; x < *fieldx; ++x)
        {
            fscanf(file, "%d", &noves->adat[y][x]);
        }
    }

    fclose(file);

    LoadGame(*fieldx, *fieldy);
    gui(jatekosnev, *nevhossz);

    betoltesultetes(mezo, noves, *fieldx, *fieldy);
}

void ultetesadat(Field *mezo, Ido *noves, int fieldx, int fieldy, SDL_Event menuevent, int noveny)
{
    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );

    int x = 345;
    int y = 235;
    //i -> oszlop
    //j -> sor
    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            if(negyzetenbelul(menuevent, x,y,x+30,y+30) && mezo->adat[i][j] == 0)
            {
                ultetes(noveny, x, y);
                if(noveny == 1)
                {
                    mezo->adat[i][j] = 1;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 2)
                {
                    mezo->adat[i][j] = 2;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 3)
                {
                    mezo->adat[i][j] = 3;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 4)
                {
                    mezo->adat[i][j] = 4;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 5)
                {
                    mezo->adat[i][j] = 5;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 6)
                {
                    mezo->adat[i][j] = 6;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 7)
                {
                    mezo->adat[i][j] = 7;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
                if(noveny == 8)
                {
                    mezo->adat[i][j] = 8;
                    timeinfo = localtime ( &rawtime );
                    noves->adat[i][j] = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;
                }
            }
            x = x + 60;
        }
        if(x == 345 + fieldx*60) x = 375;
        else x = 345;
        y += 25;
    }
}

void arat(Field *mezo, Ido *noves, int fieldx, int fieldy, SDL_Event menuevent, char *jatekosnev, int nevhossz)
{
    int x = 345;
    int y = 235;

    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            if(negyzetenbelul(menuevent, x,y,x+30,y+30) && mezo->adat[i][j] >= 5 && mezo->adat[i][j] <= 8)
            {
                mezo->adat[i][j] = 0;
                noves->adat[i][j] = 0;
                LoadGame(fieldx, fieldy);
                gui(jatekosnev, nevhossz);
                betoltesultetes(mezo, noves, fieldx, fieldy);
            }
            x = x + 60;
        }
        if(x == 345 + fieldx*60) x = 375;
        else x = 345;
        y += 25;
    }
}

void megnotte(Field *mezo, Ido *noves, int fieldx, int fieldy)
{
    time_t rawtime;
    struct tm *timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int curtime = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600 + timeinfo->tm_yday * 86400;

    int x = 345;
    int y = 235;
    //i -> oszlop
    //j -> sor
    for(int i = 0; i < fieldy; i++)
    {
        for(int j = 0; j < fieldx; j++)
        {
            if( mezo->adat[i][j] >= 1 && mezo->adat[i][j] <= 4)
            {
                if((curtime - noves->adat[i][j] ) > 20)
                {
                    mezo->adat[i][j] += 4;
                    noves->adat[i][j] = 0;
                    ultetes(mezo->adat[i][j], x, y);
                }
            }
            x = x + 60;
        }
        if(x == 345 + fieldx*60) x = 375;
        else x = 345;
        y += 25;
    }
}
