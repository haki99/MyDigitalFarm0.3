#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include "Headers\Init.h"
#include "Headers\Header.h"


void init()
{
    int SCREEN_WIDTH = 960;
    int SCREEN_HEIGHT = 540;

	//!ISDL inicializalasa
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "Nem sikerult az SDL-t inicializalni! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//!Ablak letrehozasa
		window = SDL_CreateWindow( "MyDigitalFarm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Nem sikerult az ablakot letrehozni! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//!Felulet letrehozasa
			surface = SDL_GetWindowSurface( window );
			if( surface == NULL)
            {
                printf( "Nem sikerult a feluletet letrehozni! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {
                renderer = SDL_CreateRenderer(window, -1, 0);
                if( renderer == NULL)
                {
                    printf( "Nem sikerult a renderer-t letrehozni! SDL_Error: %s\n", SDL_GetError() );
                }
            }
            SDL_StartTextInput();
		}
	}
}
