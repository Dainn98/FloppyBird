#ifndef DECLARATION_H_
#define DECLARATION_H_
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
//SCREEN
const int SCREEN_WIDTH = 1280,
        SCREEN_HEIGHT = 800,
        BACKGROUND_WIDTH = 1280,
        BACKGROUND_HEIGHT = 800,
        BASE_WIDTH = 1182,
        BASE_HEIGHT = 134,
        BASE_QUARTER_WIDTH = BASE_WIDTH / 4,
        UPPER_PIPE_OFFSET = -40,
        LOWER_PIPE_OFFSET = 150,
        NUMBER_OF_PIPE = 1000,
        LOWER_PIPE_HEIGHT_OFFSET = 134,
        BACKGROUND_FRAME = 8,
        SIZE_OF_FONT = 28,
        
//Bird
        BIRD_WIDTH = 40,
        BIRD_HEIGHT = 30,
//Pipe
        PIPE_WIDTH = 100,
        PIPE_HEIGHT = 300,
        FLYING_ANIMATION_FRAMES_OF_BIRD = 3, 
//Feature 
        
        GRAVITY = 1,
        BIRD_JUMP_VELOCITY = -15,
        PIPE_VELOCITY = 15,
        COLOR_KEY_R = 167,
        COLOR_KEY_G = 175,
        COLOR_KEY_B = 180;
const int NUMBER_OF_PIRANHA_PLANT = 5;
//Declaration for Main loop
bool quit = false;
SDL_Event e;
int frame = 0,
    backgroundX = 0,
    picture = 0;
double DELAY = 20;

// void initializeRandomSeed() {
//     srand(time(0));
// }
int getRandomNumber(int size){
        // srand(time(0));
        return rand() % size + 1;
}
// LTexture gBackgroundTexture;
// LTexture gStretchedSurface;
// LTexture gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
// static SDL_Window* g_window = NULL;
// static SDL_Renderer* g_renderer = NULL;
// #include <SDL_mixer.h>
// #include <string>
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
#endif
