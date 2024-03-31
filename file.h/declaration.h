#ifndef DECLARATION_H_
#define DECLARATION_H_
#include <bits/stdc++.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "TextObject.h"
#include "BaseObject.h"

// #include "Bird.h"    //ko
// #include "Pipe.h"    //ko
using namespace std;
                                //Loading Sprites,Sound
static char gBaseSurface_path[] = {"Sprites/base.png"};
static char gBackGroundTexture_path[] ={"Sprites/background.jpg"};

static char gButtonControlGame_PAUSE_path[] = {"Sprites/pausebutton.png"};
static char gButtonControlGame_PLAY_path[]={"Sprites/playbutton.png"};
static char gButtonControlGame_REPLAY_path[]={"Sprites/restartbutton.png"};
static char gButtonControlGame_EXIT_path[]={"Sprites/stopbutton.png"};


static char Sphere_Bullet_path[] = {"Sprites/bulletBird1.png"};
static char Laser_Bullet_path[] = {"Sprites/bulletBird2.png"};
static char Other_Type_Bullet_path[] = {"Sprites/bulletBird3.png"};
static char Creepy_path[] = {"Sprites/creepy.png"};

static char Bullet_Threat1_path[] = {"Sprites/xbullet.png"};
static char Explosion_path[] = {"Sprites/Expolosion.png"};
static char Explosion_Bullet_path[] = {"Sprites/explosion.png"};
static char Plant_path[] = {"Sprites/plantX.png"};
static char Icicle_path[] = {"Sprites/Icicle2.png"};

static char PipeRed_path[] = {"Sprites/pipeRed.png"};
static char PipeBlue_path[] = {"Sprites/pipeBlue.png"};
static char PipeGreen_path[] = {"Sprites/pipeGreen.png"};

static char gFly_path[] = {"Sound/wing.wav"};
static char gMusic_path[] = {"Sound/music.wav"};
static char gSwoosh_path[] = {"Sound/swoosh.wav"};
static char gSwapBullet_path[] = {"Sound/swapBullet.wav"};
static char gExplosion_path[] = {"Sound/explosion.wav"};
static char gDie_path[] = {"Sound/die.wav"};

#define GA_FAILED -1

const int 
                                                //SCREEN
  SCREEN_WIDTH = 1280,    
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
  NUM_THREAT = 4,        
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
  COLOR_KEY_B = 180,
                                              //BULLET
  BULLET_TYPES = 2;
int bullet[BULLET_TYPES] = {50,51};      
                                                    //FUNCTION
bool init();  
bool loadMedia();
void close();
// void BuildScreen();
void COLLISION_WITH_OBSTACLE();
void solveEvent();
int getRandomNumber(int size)   {return rand() % size + 1;}
                                                            //DECLARE SDL
static SDL_Event* g_event;
static SDL_Surface* des    = NULL;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Texture* birdTexture = NULL;
static SDL_Texture* pipeTexture = NULL;
static SDL_Surface* pipeSurface = NULL;
static SDL_Rect emptyObstacle = {0, 0, 0, 0};
static SDL_Rect gSpriteBackground[ BACKGROUND_FRAME ];
static TTF_Font* gFont = NULL;
static TTF_Font* gFontText = NULL;
static TTF_Font* gFontMENU = NULL;

                                                             //DECLARATION FOR MAIN LOOP
double SPEED_OF_PROJECT = 15;
int frame = 0,
    backgroundX = 0,
    FRAME_PER_SECOND = 35,
    picture = 0;
                                                            //MUSIC
Mix_Chunk *gFly = NULL;
Mix_Chunk *gSwoosh = NULL;
Mix_Chunk *gSwapBullet = NULL;
Mix_Chunk *gDie = NULL;
Mix_Chunk *gExplosion = NULL;
Mix_Music *gMusic = NULL;
                                                            //OPTION_CONTROL_GAME
enum Button{
    PAUSE,
    PLAY,
    REPLAY,
    EXIT,
    TOTAL_BUTTON_CONTROL_GAME,
    NONE
};

namespace SDLCommonFunc{
        SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
        void ApplySurfaceClip(SDL_Texture* src, SDL_Renderer* des, SDL_Rect* clip, int x, int y);

        bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
        int MakeRandValue(const int& div_val = 500); //Need to change the Div_val
        // int ShowMenu(SDL_Surface* des, TTF_Font* font);
        bool CheckFocusWithRect(const int& x, const int& y,  const SDL_Rect& rect);
        int ShowMenu(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name);
}

#endif
