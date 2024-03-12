#ifndef DECLARATION_H_
#define DECLARATION_H_
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "feature.h"
using namespace std;
bool init();
bool loadMedia();
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void close();
void BuildScreen();
void COLLISION_WITH_OBSTACLE();

static SDL_Event* g_event;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = nullptr;
SDL_Texture* pipeTexture = nullptr;
TTF_Font* gFont = NULL;
SDL_Surface* pipeSurface = NULL;
SDL_Rect emptyObstacle = {0, 0, 0, 0};
SDL_Rect gSpriteBackground[ BACKGROUND_FRAME ];

//Declaration for Main loop
bool quit = false;
SDL_Event e;
int frame = 0,
    backgroundX = 0,
    picture = 0;
double DELAY = 20;
Mix_Chunk *gFly = NULL;
Mix_Music *gMusic = NULL;
enum Button{
    PAUSE,
    PLAY,
    REPLAY,
    EXIT,
    TOTAL_BUTTON_IN_GAME
};

int getRandomNumber(int size){
        // srand(time(0));
        return rand() % size + 1;
}

#endif
