#ifndef DECLARATION_H_
#define DECLARATION_H_
#include <bits/stdc++.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
// #include "Bird.h"    //ko
// #include "Pipe.h"    //ko
using namespace std;
                                                      //SCREEN
const int SCREEN_WIDTH = 1280,    
        SCREEN_HEIGHT = 800,
        BACKGROUND_WIDTH = 1280,
        BACKGROUND_HEIGHT = 800,
        BASE_WIDTH = 1182,
        BASE_HEIGHT = 134,
        BASE_QUARTER_WIDTH = BASE_WIDTH / 4,
        BACKGROUND_FRAME = 8,
                                                      //FONT
        SIZE_OF_FONT = 28,      
                                                      //THREAT
        NUM_THREAT = 6,        
        DISTANCE_BETWEEN_THREATS = 400,
        THREAT_VELOCITY = 10,
        SPEED_BULLET_THREATS = 12,
        UNDER_LIMIT_THREAT = 200,
        WIDTH_THREAT = 80,
        HEIGHT_THREAT = 33,
        THREAT_GRAVITY = 1.5,
        THREAT_FRAME_NUME = 8,
        MAX_FALL_SPEED = 10,
                                                      //BIRD
        BIRD_WIDTH = 34,        
        BIRD_HEIGHT = 24,
                                                      //PIPE
        PIPE_WIDTH = 100,       
        NUMBER_OF_PIPE = 100,
        UPPER_PIPE_OFFSET = -40,
        LOWER_PIPE_OFFSET = 150,
        PIPE_HEIGHT = 300,
        FLYING_ANIMATION_FRAMES_OF_BIRD = 3, 
        LOWER_PIPE_HEIGHT_OFFSET = 134,
                                                     //FEATURE
        GRAVITY = 1,          
        BIRD_JUMP_VELOCITY = -15,
        PIPE_VELOCITY = 15,
        COLOR_KEY_R = 167,
        COLOR_KEY_G = 175,
        COLOR_KEY_B = 180;
                                                    //BULLET
int bullet[2] = {50,51};      
                                                    //FUNCTION
bool init();  
bool loadMedia();
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void close();
void BuildScreen();
void COLLISION_WITH_OBSTACLE();
void solveEvent();
int getRandomNumber(int size)   {return rand() % size + 1;}
                                                            //DECLARE SDL
static SDL_Event* g_event;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;
TTF_Font* gFont = NULL;
SDL_Surface* pipeSurface = NULL;
SDL_Rect emptyObstacle = {0, 0, 0, 0};
SDL_Rect gSpriteBackground[ BACKGROUND_FRAME ];
                                                             //DECLARATION FOR MAIN LOOP
bool quit = false;
SDL_Event e;
int frame = 0,
    backgroundX = 0,
    FRAME_PER_SECOND = 35,
    picture = 0;
double DELAY = 20;
                                                            //MUSIC
Mix_Chunk *gFly = NULL;
Mix_Chunk *gSwoosh = NULL;
Mix_Chunk *gSwapBullet = NULL;
Mix_Music *gMusic = NULL;
enum Button{
    PAUSE,
    PLAY,
    REPLAY,
    EXIT,
    TOTAL_BUTTON_CONTROL_GAME,
    NONE
};

namespace SDLCommonFunc{
        SDL_Rect ApplySurface(SDL_Texture* src, SDL_Renderer* des, int x, int y);
        void ApplySurfaceClip(SDL_Texture* src, SDL_Renderer* des, SDL_Rect* clip, int x, int y);

        bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
        int MakeRandValue(const int& div_val = 400); //Need to change the Div_val
        int ShowMenu(SDL_Surface* des, TTF_Font* font);
        bool CheckFocusWithRect(const int& x, const int& y,  const SDL_Rect& rect);
}
void SDLCommonFunc::ApplySurfaceClip(SDL_Texture* src, SDL_Renderer* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    if (clip != NULL) {
        offset.w = clip->w;
        offset.h = clip->h;
    } 
                                                    // QUERY THE TEXTURE TO GET  ITS WIDTH AND HEIGHT IF NO CLIP IS PROVIDED
    else SDL_QueryTexture(src, NULL, NULL, &offset.w, &offset.h);
    SDL_RenderCopy(des, src, clip, &offset);
}



bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

                                                                      // CASE 1 : SIZE 1 < SIZE 2
  if (left_a > left_b && left_a < right_b){
    if (top_a > top_b && top_a < bottom_b)  return true;
  }

  if (left_a > left_b && left_a < right_b){
    if (bottom_a > top_b && bottom_a < bottom_b)  return true;
    }
  
  if (right_a > left_b && right_a < right_b){
    if (top_a > top_b && top_a < bottom_b)  return true;
  }

  if (right_a > left_b && right_a < right_b){
    if (bottom_a > top_b && bottom_a < bottom_b)  return true;
    
  }

                                                                      // CASE 2 : SIZE 1 > SIZE 2
  if (left_b > left_a && left_b < right_a){
    if (top_b > top_a && top_b < bottom_a)  return true;
  }

  if (left_b > left_a && left_b < right_a){
    if (bottom_b > top_a && bottom_b < bottom_a)  return true;
    
  }

  if (right_b > left_a && right_b < right_a){
    if (top_b > top_a && top_b < bottom_a)  return true; 
  }

  if (right_b > left_a && right_b < right_a){
    if (bottom_b > top_a && bottom_b < bottom_a)  return true;
  }

                                                                      //CASE 3 : SIZE 1 == SIZE 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b) return true;
  
  return false;
}


int SDLCommonFunc::MakeRandValue(const int& div_val /*400*/){
  int rand_y = rand()%div_val;
  if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)  rand_y = SCREEN_HEIGHT*0.3;
  return rand_y;
}

#endif
