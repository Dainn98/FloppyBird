#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "declaration.h"
#include "LTexture.h"
#include "Game.h"
Game mGame;
//https://lazyfoo.net/tutorials/SDL/index.php
bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )	printf( "Warning: Linear texture filtering not enabled!" );
		
		//Create window
		gWindow = SDL_CreateWindow( "BY TUAN ANH", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}else{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ){
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				Mix_AllocateChannels(64);


				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
   				gFontText  = TTF_OpenFont("Sprites/turok.ttf",28);
				  if(gFontText == NULL){
					printf("Failed to load font %s!\n", "Sprites/turok.ttf");
					success = false;
				  }
				gFontMENU = TTF_OpenFont("Sprites/turok.ttf", 80);
				 if (gFontMENU == NULL)
				{
					printf("Failed to load font menu %s!\n", "Sprites/turok.ttf");
					success = false;
				}

			}
		}
	}

	return success;
}
#endif
