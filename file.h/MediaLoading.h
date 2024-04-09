#ifndef MEDIA_LOADING_H
#define MEDIA_LOADING_H
// #include "declaration.h"
bool LoadingMedia(){
	bool success = true;   
                                                                    //BACKGROUND LOADING  
	gBackgroundTexture.loadFromFile( gBackGroundTexture_path );
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }
                                                                    //BASE LOADING
    gBaseSurface.loadFromFile( gBaseSurface_path );
                                                                    //BIRD LOADING
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        gBird[i].loadFromFile(imagePath);
    }
                                                                    //MUSIC LOADING
    gFly = Mix_LoadWAV(gFly_path);
    gMusic = Mix_LoadMUS(gMusic_path);
    gSwoosh = Mix_LoadWAV(gSwoosh_path);
    gMoneyCol = Mix_LoadWAV(gMoneyCol_path);
    gSwapBullet = Mix_LoadWAV(gSwapBullet_path);
    gExplosion = Mix_LoadWAV(gExplosion_path);
    gDie = Mix_LoadWAV(gDie_path);
    gBubbleAdd = Mix_LoadWAV(gBubbleAdd_path);
    gBubblePow = Mix_LoadWAV(gBubllePow_path);
    gScoreIncrement = Mix_LoadWAV(gScoreIncrement_path);
                                                                    //BUTTON CONTORL LOADING
    gButtonControlGame[PAUSE].loadFromFile(gButtonControlGame_PAUSE_path);
    gButtonControlGame[PLAY].loadFromFile(gButtonControlGame_PLAY_path);
    gButtonControlGame[REPLAY].loadFromFile(gButtonControlGame_REPLAY_path);
    gButtonControlGame[EXIT].loadFromFile(gButtonControlGame_EXIT_path);
	return success;
}
#endif
