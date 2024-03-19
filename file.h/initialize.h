#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "declaration.h"
#include "LTexture.h"
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

			}
		}
	}

	return success;
}
void BuildScreen(){
    
  
    SDL_Rect* currentBackground = &gSpriteBackground[ frame /  BACKGROUND_FRAME]; // LOADING BACKGROUND
    gBackgroundTexture.render((SCREEN_WIDTH - currentBackground->w) - picture,(SCREEN_HEIGHT - currentBackground->h), currentBackground );
    gBackgroundTexture.render((SCREEN_WIDTH*2 - currentBackground->w) - picture ,(SCREEN_HEIGHT - currentBackground->h), currentBackground );

    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);	//LOADING BASE
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
    if(++picture >= SCREEN_WIDTH ) picture = 0;
    if( ++frame / BACKGROUND_FRAME >= BACKGROUND_FRAME)frame = 0;
}
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x <= b.x + b.w &&
            a.x + a.w >= b.x &&
            a.y <= b.y + b.h &&
            a.y + a.h >= b.y);
}
#endif
