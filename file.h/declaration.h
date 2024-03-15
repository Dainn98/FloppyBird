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

const int SCREEN_WIDTH = 1280,    //SCREEN
        SCREEN_HEIGHT = 800,
        BACKGROUND_WIDTH = 1280,
        BACKGROUND_HEIGHT = 800,
        BASE_WIDTH = 1182,
        BASE_HEIGHT = 134,
        BASE_QUARTER_WIDTH = BASE_WIDTH / 4,
        BACKGROUND_FRAME = 8,
      
        SIZE_OF_FONT = 28,      //FONT

        NUM_THREAT = 6,        //THREAT
        DISTANCE_BETWEEN_THREATS = 400,
        THREAT_VELOCITY = 10,
        SPEED_BULLET_THREATS = 12,
        UNDER_LIMIT_THREAT = 200,
        WIDTH_THREAT = 80,
        HEIGHT_THREAT = 33,
        THREAT_GRAVITY = 1.5,
        THREAT_FRAME_NUME = 8,
        MAX_FALL_SPEED = 10,

        BIRD_WIDTH = 34,        //BIRD
        BIRD_HEIGHT = 24,

        PIPE_WIDTH = 100,       //PIPE
        NUMBER_OF_PIPE = 1000,
        UPPER_PIPE_OFFSET = -40,
        LOWER_PIPE_OFFSET = 150,
        PIPE_HEIGHT = 300,
        FLYING_ANIMATION_FRAMES_OF_BIRD = 3, 
        LOWER_PIPE_HEIGHT_OFFSET = 134,

        GRAVITY = 1,          //FEATURE
        BIRD_JUMP_VELOCITY = -15,
        PIPE_VELOCITY = 15,
        COLOR_KEY_R = 167,
        COLOR_KEY_G = 175,
        COLOR_KEY_B = 180;

int bullet[2] = {50,51};      //BULLET

bool init();  //FUNCTION
bool loadMedia();
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void close();
void BuildScreen();
void COLLISION_WITH_OBSTACLE();
void solveEvent();
int getRandomNumber(int size)   {return rand() % size + 1;}

static SDL_Event* g_event;//DECLARE SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;
TTF_Font* gFont = NULL;
SDL_Surface* pipeSurface = NULL;
SDL_Rect emptyObstacle = {0, 0, 0, 0};
SDL_Rect gSpriteBackground[ BACKGROUND_FRAME ];

bool quit = false;//DECLARATION FOR MAIN LOOP
SDL_Event e;
int frame = 0,
    backgroundX = 0,
    FRAME_PER_SECOND = 35,
    picture = 0;
double DELAY = 20;

Mix_Chunk *gFly = NULL;//MUSIC
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

//doi ten
namespace SDLCommonFunc{
        // SDL_Surface* LoadImage(std::string file_path);
        // void CleanUp();

        SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);  //FOR CHALLANGE
        void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);

        bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
        int MakeRandValue(const int& div_val = 400); //Need to change the Div_val
        int ShowMenu(SDL_Surface* des, TTF_Font* font);
        bool CheckFocusWithRect(const int& x, const int& y,  const SDL_Rect& rect);
}

bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
  if (x >= rect.x && x <= rect.x + rect.w &&
      y >= rect.y && y <= rect.y + rect.h)
  {
    return true;
  }
  return false;
}

// SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
// {
//   SDL_Surface * load_image = NULL;
//   SDL_Surface* optimize_image = NULL;
//   load_image = IMG_Load(file_path.c_str());
//   if (load_image != NULL)
//   {
//     optimize_image= SDL_DisplayFormat(load_image);
//     SDL_FreeSurface(load_image);

//     if (optimize_image != NULL) 
//     {
//       UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
//       SDL_SetColorKey(optimize_image, 0x00001000, color_key);
//     }
//   }
//   return optimize_image;
// }


SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);

  return offset;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, clip, des, &offset);
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

  // Case 1: size object 1 < size object 2
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

  // Case 2: size object 1 < size object 2
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

  // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b) return true;
  
  return false;
}


int SDLCommonFunc::MakeRandValue(const int& div_val /*400*/)
{
  int rand_y = rand()%div_val;
  if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
  {
    rand_y = SCREEN_HEIGHT*0.3;
  }
  return rand_y;
}

#endif
