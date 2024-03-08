#ifndef LOADMEDIA_H
#define LOADMEDIA_H
#include "Header.h"
#include "declaration.h"
bool loadMedia(){
	bool success = true;     
	if( !gBackgroundTexture.loadFromFile( "Sprites/background.jpg" ) ){
		printf( "Failed to load background texture image!\n" );
		success = false; 
	}else{
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }
    }
    if(!gBaseSurface.loadFromFile( "Sprites/base.png" )){  
		printf( "Failed to load base image!\n" );
		success = false;
	}
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        if (!gTextures[i].loadFromFile(imagePath))  success = false;
    }
    
    //  switch (whichPipe){
    //         case 1:  
    //             pipeSurface = IMG_Load("Sprites/pipeRed.png");
    //             break;
    //         case 2:
    //             pipeSurface = IMG_Load("Sprites/pipeBlue.png");
    //             break;
    //         case 3: 
    //             pipeSurface = IMG_Load("Sprites/pipeGreen.png"); 
    //             break;
    //         default:
    //             break;
    //     }
    // if(whichPipe == 1)pipeSurface = IMG_Load("Sprites/pipeRed.png");

    // else if (whichPipe == 3)pipeSurface = IMG_Load("Sprites/pipeGreen.png");

    // else if(whichPipe == 2) pipeSurface = IMG_Load("Sprites/pipeBlue.png");

    // SDL_Surface* pipeSurface = IMG_Load("Sprites/pipeGreen.png");
    // pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    // SDL_FreeSurface(pipeSurface);
	return success;
}
#endif
