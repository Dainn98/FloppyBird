#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "declaration.h"
//https://lazyfoo.net/tutorials/SDL/index.php
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }   
    gWindow = SDL_CreateWindow("Floppy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);
    
    // SDL_Surface* pipeSurface = IMG_Load("Sprites/pipeGreen.png");
    // pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    // SDL_FreeSurface(pipeSurface);
    return true;
}

#endif
