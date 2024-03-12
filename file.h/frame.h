// #ifndef FRAME_H
// #define FRAME_H
// #include "Header.h"
// void BuildScreen(){
//     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //=> clear sreen
//     SDL_RenderClear(gRenderer);
//     //loading background
//     SDL_Rect* currentBackground = &gSpriteBackground[ frame /  BACKGROUND_FRAME];
//     gBackgroundTexture.render((SCREEN_WIDTH - currentBackground->w) - picture,(SCREEN_HEIGHT - currentBackground->h), currentBackground );
//     gBackgroundTexture.render((SCREEN_WIDTH*2 - currentBackground->w) - picture ,(SCREEN_HEIGHT - currentBackground->h), currentBackground );
//     //loading base
//     SDL_Rect* currentPiranhaPlant = &gSpritePiranhaPlant[ frame/NUMBER_OF_PIRANHA_PLANT];
//     gPiranhaPlant.render((SCREEN_WIDTH - currentPiranhaPlant->w) - picture,(SCREEN_HEIGHT - currentPiranhaPlant->h), currentPiranhaPlant );
//     gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
//     gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
//     if(++picture >= SCREEN_WIDTH ) picture = 0;
//     if( ++frame / BACKGROUND_FRAME >= BACKGROUND_FRAME)frame = 0;
// }

// #endif
