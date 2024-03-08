#ifndef FRAME_H
#define FRAME_H
#include "Header.h"
void BuildScreen(){
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //=> clear sreen
    SDL_RenderClear(gRenderer);
    //loading background
    SDL_Rect* currentClip = &gSpriteClips[ frame /  BACKGROUND_FRAME];
    gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) - picture,(SCREEN_HEIGHT - currentClip->h), currentClip );
    gSpriteSheetTexture.render((SCREEN_WIDTH*2 - currentClip->w) - picture ,(SCREEN_HEIGHT - currentClip->h), currentClip );
    //loading base
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
    if(++picture >= SCREEN_WIDTH ) picture = 0;
    if( ++frame / BACKGROUND_FRAME >= BACKGROUND_FRAME)frame = 0;
}

#endif
