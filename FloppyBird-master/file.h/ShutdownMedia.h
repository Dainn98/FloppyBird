#ifndef SHUTDOWN_MEDIA_H
#define SHUTDOWN_MEDIA_H
// #include "declaration.h"
void ShutdownMedia() {
                                                                    //FREE LTEXTURE
    for (int i = 0; i < FLYING_ANIMATION_FRAMES_OF_BIRD; ++i) gBird[i].free();// => free loaded image
    gBaseSurface.free();
    gBackgroundTexture.free();
    gButtonControlGame[0].free();
    gButtonControlGame[1].free();
    gButtonControlGame[2].free();
    gButtonControlGame[3].free();
                                                                    //FREE MUSICE
    Mix_FreeChunk( gFly );gFly = NULL;
    Mix_FreeMusic( gMusic ); gMusic = NULL;
    Mix_FreeChunk( gSwoosh ); gSwoosh = NULL;
    Mix_FreeChunk( gMoneyCol ); gMoneyCol = NULL;
    Mix_FreeChunk( gDie ); gDie = NULL;
    Mix_FreeChunk( gExplosion ); gExplosion = NULL;
    Mix_FreeChunk( gSwapBullet ); gSwapBullet = NULL;
    Mix_FreeChunk( gBubbleAdd ); gBubbleAdd = NULL;
    Mix_FreeChunk( gBubblePow ); gBubblePow = NULL;
    Mix_FreeChunk( gScoreIncrement ); gScoreIncrement = NULL;
	                                                                //DESTROY TEXTURE
    SDL_DestroyTexture(pipeTexture); pipeTexture = NULL;   
    pipeSurface = NULL;

                                                                    //DESTROY RENDER,WINDOW
    SDL_DestroyRenderer(gRenderer);  gRenderer = NULL;
    SDL_DestroyWindow(gWindow);      gWindow= NULL;
                                                                    //DESTROY FONT
    TTF_CloseFont(gFontText);gFontText = NULL;
    TTF_CloseFont(gFontMENU);gFontMENU = NULL;
    TTF_CloseFont(gFont);gFont = NULL;
                                                                    //DESTROY SURFACE
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
#endif
