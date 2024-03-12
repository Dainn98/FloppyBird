#ifndef LOADMEDIA_H
#define LOADMEDIA_H
#include "Header.h"
#include "declaration.h"
bool loadMedia(){
	bool success = true;     
	gBackgroundTexture.loadFromFile( "Sprites/background.jpg" );
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }
    gBaseSurface.loadFromFile( "Sprites/base.png" );
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        gTextures[i].loadFromFile(imagePath);
    }
    gFly = Mix_LoadWAV("Sound/wing.wav");
    gMusic = Mix_LoadMUS("Sound/music.wav");
     gButtonControlGame[PAUSE].loadFromFile("Sprites/iconpause.png");
    gButtonControlGame[PLAY].loadFromFile("Sprites/iconplay.png");
    gButtonControlGame[REPLAY].loadFromFile("Sprites/iconreplay.jpg");
    gButtonControlGame[EXIT].loadFromFile("Sprites/iconquit.png");
	return success;
}
#endif
