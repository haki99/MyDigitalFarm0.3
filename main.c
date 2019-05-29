#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include "Headers\Header.h"
#include "Headers/Aux_Funct.h"
#include "Headers/Init.h"
#include "Headers/Events.h"
#include "Headers/File_Management.h"
#include "Headers/Media.h"

//!Az ablak amibe renderelunk
SDL_Window* window = NULL;

//!A felulet az ablakban
SDL_Surface* surface = NULL;

//!A render letrehozasa
SDL_Renderer* renderer = NULL;

int main( int argc, char* args[] )
{
	//!SDL inditasa es az ablak letrehozasa
	init();
    TTF_Init();

    //!A flag-ek a fo loophoz
    bool quit = false;
    bool openmenu = true;
    bool opengame = false;

    bool insidemenu = false;
    bool gameplay = false;
    bool insidemainmenu = true;
    bool insideplay = false;
    bool insideoptions = false;
    bool insidenewgamemenu = false;
    bool ingamemenu = false;

    //!Ultetes kivalaszto
    int noveny = 0;

    //!Begepeleshez az allapotok
    bool nevbe = false;

    //!Event kezelo
    SDL_Event menuevent;

    int nevhossz = 1;
    char *jatekosnev;
    jatekosnev = (char*) malloc(nevhossz*sizeof(char));

    int fieldy = 1;
    int fieldx = 1;

    char szamx[2] = {0};
    char szamy[2] = {0};

    Field *mezo;
    mezo=(Field*) malloc(sizeof(Field));
    nullaz(mezo);

    Ido *noves;
    noves = (Ido*) malloc(sizeof(Ido));
    nullazido(noves);

    //!Fo loop
    //!Addig fut ameddig nem mondjuk neki hogy 'quit'
    while( !quit )
    {
        //!Eventek feldolgozasa
        while( SDL_PollEvent( &menuevent ) != 0 )
        {
            //!fELHASZNALO KILEPNI SZERETNE
            if( menuevent.type == SDL_QUIT )
            {
                quit = true;
            }

            //!Event fajtak kezelese
            switch (menuevent.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if(menuevent.button.button == SDL_BUTTON_LEFT)
                    {
                        if(insidemenu)
                        {
                            //!Ha a newgame almenuben vagyunk
                            if(insidenewgamemenu)
                            {
                                nevbe = false;
                                //!Back gombra nyomas
                                if(negyzetenbelul(menuevent, 699, 419, 885, 500))
                                {
                                    nevhossz = 1;
                                    jatekosnev[0] = '\0';
                                    fieldx = 1;
                                    fieldy = 1;

                                    LoadPlayMenu();
                                    insidenewgamemenu = false;
                                    insideplay = true;
                                    break;
                                }

                                //!Nevbe
                                if(negyzetenbelul(menuevent, 160,235,360,285))
                                {
                                    nevbe = true;
                                }

                                //!Fieldx-be
                                if(negyzetenbelul(menuevent, 220,335,270,385))
                                {
                                    if(fieldx < 9)
                                    {
                                        fieldx++;
                                        szamx[0] = fieldx + '0';

                                        SDL_Rect rect;
                                        rect.x = 220;
                                        rect.y = 335;
                                        rect.w = 50;
                                        rect.h = 50;

                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &rect);

                                        szovegkiiras(szamx, 220, 335, 50, 50);
                                    }
                                }

                                //!Fieldy-ba
                                if(negyzetenbelul(menuevent, 320,335,370,385))
                                {
                                    if(fieldy < 9)
                                    {
                                        fieldy++;
                                        szamy[0] = fieldy + '0';

                                        SDL_Rect rect;
                                        rect.x = 320;
                                        rect.y = 335;
                                        rect.w = 50;
                                        rect.h = 50;

                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &rect);

                                        szovegkiiras(szamy, 320, 335, 50, 50);
                                    }
                                }

                                //! Kilepesi pont a menu loopbol, at a game loopba
                                if(negyzetenbelul(menuevent, 699,320,895,400))
                                {
                                    //!A mezo es ido tombkent tarolva
                                    foglal(mezo, fieldx, fieldy);
                                    nullaz(mezo);
                                    foglalido(noves, fieldx, fieldy);
                                    nullazido(noves);

                                    //!Jatek tenyleges inditasa
                                    insidemenu = false;
                                    insidenewgamemenu = false;
                                    gameplay = true;
                                    opengame = true;

                                    LoadGame(fieldx, fieldy);
                                    gui(jatekosnev, nevhossz);
                                    break;
                                }
                            }

                            //!Ha a Play almenuben vagyunk
                            if(insideplay)
                            {
                                //!ha a Back-re nyomunk
                                if(negyzetenbelul(menuevent, 392, 389, 578, 470))
                                {
                                    //!Fomenu meghivasa
                                    LoadMenu();
                                    insideplay = false;
                                    insidemainmenu = true;
                                    break;
                                }
                                //!Ha a New Game-re nyomunk
                                if(negyzetenbelul(menuevent, 392, 189, 578, 270))
                                {
                                    LoadNewGameMenu();
                                    insideplay = false;
                                    insidenewgamemenu = true;

                                    nevhossz = 1;
                                    jatekosnev[0] = '\0';
                                    fieldx = 1;
                                    fieldy = 1;

                                    break;
                                }

                                //!Ha a LoadGame-re nyomunk
                                if(negyzetenbelul(menuevent, 392, 289, 578, 370))
                                {
                                    Betoltes(mezo, noves, jatekosnev, &nevhossz, &fieldx, &fieldy);

                                    gameplay = true;
                                    insideplay = false;
                                    insidemenu = false;
                                    break;
                                }
                            }

                            //!Ha az Options almenuben vagyunk
                            if(insideoptions)
                            {
                                if(negyzetenbelul(menuevent, 392, 389, 578, 470))
                                {
                                    LoadMenu();
                                    insideoptions = false;
                                    insidemainmenu = true;
                                    break;
                                }
                            }

                            //!Fomenuben vagyunk
                            if(insidemainmenu)
                            {
                                //!A Jatek inditasa
                                if(negyzetenbelul(menuevent, 699, 219, 896, 301))
                                {
                                    LoadPlayMenu();
                                    insideplay = true;
                                    insidemainmenu = false;
                                    break;
                                }

                                //!A beallitasok megnyitasa
                                if(negyzetenbelul(menuevent, 699, 319, 896, 401))
                                {
                                    LoadOptions();
                                    insideoptions = true;
                                    insidemainmenu = false;
                                    break;
                                }

                                //!Kilepes
                                if(negyzetenbelul(menuevent, 699, 419, 896, 501))
                                {
                                    quit = true;
                                    //!felulet frissitese
                                    SDL_UpdateWindowSurface( window );
                                    break;
                                }
                            }
                        }

                        if(gameplay)
                        {
                            //!In Game Menu a kilepeshez
                            if(ingamemenu)
                            {
                                negyzetenbelul(menuevent, 420,420,615,500);
                                {
                                    gameplay = false;
                                    ingamemenu = false;
                                    insidemenu = true;
                                    insidemainmenu = true;
                                    LoadMenu();

                                    //!Mentes
                                    Mentes(mezo, noves, nevhossz, jatekosnev, fieldx, fieldy);
                                }
                            }

                            //!Beanre kattint
                            if(negyzetenbelul(menuevent, 550,10,637,99))
                            {
                                noveny = 1;
                                break;
                            }

                            //!Carrot-ra kattint
                            if(negyzetenbelul(menuevent, 650,10,737,99))
                            {
                                noveny = 2;
                                break;
                            }

                            //!Paprika-ra kattint
                            if(negyzetenbelul(menuevent, 750,10,837,99))
                            {
                                noveny = 3;
                                break;
                            }

                            //!Potato-ra kattint
                            if(negyzetenbelul(menuevent, 850,10,937,99))
                            {
                                noveny = 4;
                                break;
                            }

                            //!ultetes
                            if(noveny != 0)
                            {
                                ultetesadat(mezo, noves, fieldx, fieldy, menuevent, noveny);
                            }

                            arat(mezo, noves, fieldx, fieldy, menuevent, jatekosnev, nevhossz);
                        }
                    }

                    if(menuevent.button.button == SDL_BUTTON_RIGHT)
                    {
                        if(insidenewgamemenu)
                            {
                                //!Fieldx csokkentese
                                if(negyzetenbelul(menuevent, 220,335,270,385))
                                {
                                    if(fieldx > 1)
                                    {
                                        fieldx--;
                                        szamx[0] = fieldx + '0';
                                        SDL_Rect rect;
                                        rect.x = 220;
                                        rect.y = 335;
                                        rect.w = 50;
                                        rect.h = 50;

                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &rect);

                                        szovegkiiras(szamx, 220, 335, 50, 50);
                                        break;
                                    }
                                }

                                //!Fieldy csokkentese
                                if(negyzetenbelul(menuevent, 320,335,370,385))
                                {
                                    if(fieldy > 1)
                                    {
                                        fieldy--;
                                        szamy[0] = fieldy + '0';
                                        SDL_Rect rect;
                                        rect.x = 320;
                                        rect.y = 335;
                                        rect.w = 50;
                                        rect.h = 50;

                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &rect);

                                        szovegkiiras(szamy, 320, 335, 50, 50);
                                        break;
                                    }
                                }
                            }
                    }

                case SDL_KEYDOWN:
                    if(insidemenu)
                    {
                        //!Backspace lenyomasakor
                        if( menuevent.key.keysym.sym == SDLK_BACKSPACE && nevhossz != 0 )
                        {
                            if(nevbe)
                            {
                                if(nevhossz > 1)
                                {
                                    nevhossz--;
                                    jatekosnev[nevhossz-1] = '\0';
                                    SDL_Rect rect;
                                    rect.x = 160;
                                    rect.y = 235;
                                    rect.w = 200;
                                    rect.h = 50;

                                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                    SDL_RenderFillRect(renderer, &rect);

                                    szovegkiiras(jatekosnev, 160,235, (nevhossz-1)*25,50);
                                }
                            }
                        }
                        break;
                    }

                    //!Esc jatek kozben
                    if(menuevent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        if(gameplay)
                        {
                            openingamemenu();
                            ingamemenu = true;
                            break;
                        }
                    }

                //!Szoveg beiras
                case SDL_TEXTINPUT:
                    if(insidenewgamemenu && menuevent.key.keysym.sym != SDLK_BACKSPACE && nevhossz < 8)
                    {
                        if(nevbe)
                        {
                            nev(jatekosnev, menuevent.text.text, &nevhossz);

                            SDL_Rect rect;
                            rect.x = 160;
                            rect.y = 235;
                            rect.w = 200;
                            rect.h = 50;

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                            SDL_RenderFillRect(renderer, &rect);

                            szovegkiiras(jatekosnev, 160,235,25+(nevhossz-2)*25,50);

                            break;
                        }
                    }
            }
        }

        if(gameplay) megnotte(mezo, noves, fieldx, fieldy);

        if(openmenu)
        {
            LoadMenu();
            openmenu = false;
            insidemenu = true;
        }

        if(opengame)
        {
            opengame = false;
        }
    }

    //!Minden bezarasa es az SDL leallitasa
    free(jatekosnev);
    free(mezo);
    closeall(surface, window);
    TTF_Quit();

    return 0;
}
