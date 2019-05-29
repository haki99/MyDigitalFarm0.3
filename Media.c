#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "Headers\Media.h"
#include "Headers\Header.h"
#include "Headers\File_Management.h"


//!Texturak pozicioja
SDL_Rect SrcPos;
SDL_Rect DestPos;

//!Forras pozicio
void SrcPosition(int x, int y, int w, int h)
{
    SrcPos.x = x;
    SrcPos.y = y;
    SrcPos.w = w;
    SrcPos.h = h;
}

//!Celhely pozicio
void DestPosition(int x, int y, int w, int h)
{
    DestPos.x = x;
    DestPos.y = y;
    DestPos.w = w;
    DestPos.h = h;
}

//!Szoveg letrehozasa texturakent
void szovegkiiras( char *szoveg, int x, int y, int w, int h )
{
    if(szoveg == NULL) printf("hiba: NULL a nev");

    TTF_Font *Font = NULL;
    Font = TTF_OpenFont( "Font/CarawayBold.ttf", 75 );
    SDL_Color Szovegszin = { 0, 0, 0 };

	SDL_Surface *text = NULL;

	text = TTF_RenderText_Solid( Font, szoveg, Szovegszin );

    SDL_Texture *SzovegTex = NULL;
    SzovegTex = SDL_CreateTextureFromSurface( renderer, text );

    SDL_FreeSurface( text );

    DestPosition(x, y, w, h);

    SDL_RenderCopy(renderer, SzovegTex, NULL, &DestPos);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(SzovegTex);
    TTF_CloseFont( Font );
}

//!Barmelyik kep betoltese, egy eleresi uttal es a megjelenitendo kep helyevel
void loadpic(char *eleresiut, int x, int y, int w, int h)
{
    SDL_Surface* Kep = NULL;
    SDL_Texture* KepTex = NULL;

    //!kep betoltese
    Kep = SDL_LoadBMP( eleresiut );
	if( Kep == NULL )
	{
		printf( "Nem sikerült betolteni a kepet %s! SDL Error: %s\n", eleresiut, SDL_GetError() );
	}
    KepTex = SDL_CreateTextureFromSurface(renderer, Kep);
    SDL_FreeSurface(Kep);

    //!Menu gombok betoltese
    DestPosition(x,y,w,h);
    SDL_RenderCopy(renderer, KepTex, NULL, &DestPos);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(KepTex);
}

//!Menuk megjelenitese
//!Fomenu
void LoadMenu()
{
    int SDL_RenderClear(SDL_Renderer* renderer);
    SDL_FreeSurface(surface);

    loadpic("Images/Menu/Background.bmp", 0, 0, 960, 540);

    loadpic("Images/Menu/Play.bmp", 700, 220, 195, 80);

    loadpic("Images/Menu/Option.bmp",700,320,195,80);

    loadpic("Images/Menu/Quit.bmp",700,420,195,80);
}

//!Play almenu
void LoadPlayMenu()
{
	int SDL_RenderClear(SDL_Renderer* renderer);
	SDL_FreeSurface(surface);

    loadpic("Images/Menu/Background.bmp",0,0,960,540);

    loadpic("Images/Menu/New_Game.bmp",392.5,190,195,80);

    loadpic("Images/Menu/Load_Game.bmp",392.5,290,195,80);

    loadpic("Images/Menu/Back.bmp",392.5,390,195,80);
}

//!Options almenu
void LoadOptions()
{
	int SDL_RenderClear(SDL_Renderer* renderer);
	SDL_FreeSurface(surface);

    loadpic("Images/Menu/Background.bmp",0,0,960,540);

    loadpic("Images/Menu/Back.bmp",392.5,390,195,80);
}

//!NewGameMenu al-almenu
void LoadNewGameMenu()
{
    int SDL_RenderClear(SDL_Renderer* renderer);
    SDL_FreeSurface(surface);

    //!Hatter
    loadpic("Images/Menu/Background.bmp",0,0,960,540);

    //!Menu
    loadpic("Images/Menu/Play.bmp",700,320,195,80);

    loadpic("Images/Menu/Back.bmp",700,420,195,80);

    //!Head
    loadpic("Images/Menu/Head_NewGame.bmp",230,10,500,75);

    //!Nev
    loadpic("Images/Menu/Name.bmp",10,225,166.5,83.5);

    DestPosition(160,235,200,50);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &DestPos);

    //!Mezo
    DestPosition(220,335,50,50);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &DestPos);

    DestPosition(320,335,50,50);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &DestPos);

    loadpic("Images/Menu/Size_Of_Field.bmp",10,320,166.5,83.5);

    loadpic("Images/Menu/X.bmp",270,335,50,50);

    szovegkiiras("1", 220, 335, 25, 50);
    szovegkiiras("1", 320, 335, 25, 50);
}

//!In-game
//!Felulet
void LoadGame(int fieldx, int fieldy)
{
    int SDL_RenderClear(SDL_Renderer* renderer);
    SDL_FreeSurface(surface);

    //!Kek hatter beallitasa
    DestPosition(0,0,960,540);
    SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
    SDL_RenderFillRect(renderer, &DestPos);

    //!Fu betoltese
    int x1 = -30;
    int y1 = -25;
    //!18x24-es terep
    for(int i = 1; i < 24; i++)
    {
        for(int j = 1; j < 18; j++)
        {
            if(j > 6 && j <= fieldx+6 && i > 10 && i <= fieldy+10)
            {
                loadpic("Images/Game/Main/soil_tile.bmp",x1,y1,60,50);
                x1 += 60;
            }
            else
            {
                loadpic("Images/Game/Main/grass_tile.bmp",x1,y1,60,50);
                x1 += 60;
            }
        }
        if( x1 == 990) x1 = 0;
        else x1 = -30;
        y1 += 25;
    }
}

//!Felhasznaloval kapcsolatba lepo gombok/megjelentitok
void gui(char *jatekosnev, int nevhossz)
{
    int SDL_RenderClear(SDL_Renderer* renderer);
    SDL_FreeSurface(surface);

    //!Novenyek ikonjai
    loadpic("Images/Game/GUI/Bean/bean_icon.bmp",550,10,87,89);
    loadpic("Images/Game/GUI/Carrot/carrot_icon.bmp",650,10,87,89);
    loadpic("Images/Game/GUI/Paprika/paprika_icon.bmp",750,10,87,89);
    loadpic("Images/Game/GUI/Potato/potato_icon.bmp",850,10,87,89);

    //!Nev box
    loadpic("Images/Game/GUI/Box.bmp",10,20,300,50);

    szovegkiiras(jatekosnev, 30, 25, 25+(nevhossz-2)*25, 50);
}

//!Egy noveny elultetese egy bizonyos pozicioba
void ultetes( int noveny, int x, int y)
{
    if(noveny == 1) loadpic("Images/Game/GUI/Bean/bean_1.bmp",x-5,y-60,39,86.5);

    if(noveny == 2) loadpic("Images/Game/GUI/Carrot/carrot_1.bmp",x+5,y-5,21.5,34);

    if(noveny == 3) loadpic("Images/Game/GUI/Paprika/paprika_1.bmp",x-10,y-60,38,86.5);

    if(noveny == 4) loadpic("Images/Game/GUI/Potato/potato_1.bmp",x+5,y-5,21.5,34);

    if(noveny == 5) loadpic("Images/Game/GUI/Bean/bean_4.bmp",x-6.5,y-62.5,50.5,98.5);

    if(noveny == 6) loadpic("Images/Game/GUI/Carrot/carrot_4.bmp",x-16,y-60,61.5,84.5);

    if(noveny == 7) loadpic("Images/Game/GUI/Paprika/paprika_4.bmp",x-10,y-60,38,86.5);

    if(noveny == 8) loadpic("Images/Game/GUI/Potato/potato_4.bmp",x-5,y-70,42.5,96.5);
}

//!Esc-re nyomva a megjelenitendo menu
void openingamemenu()
{
    loadpic("Images/Game/GUI/Continue.bmp",420,320,195,80);

    loadpic("Images/Game/GUI/Quit.bmp",420,420,195,80);
}
