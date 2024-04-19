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
// #include "Game.h"

// #include "Bird.h"    //ko
// #include "Pipe.h"    //ko
using namespace std;
                                //Loading Sprites,Sound
static char gBaseSurface_path[] = {"Sprites/base.png"};
static char gBackGroundTexture_path[] ={"Sprites/background.jpg"};
static char Intro_path[] = {"Sprites/introx.png"};
static char None_path[] = {"Sprites/none.png"};

static char StartGame_path[] = {"Sprites/startgame1.png"};
static char Tutorial_path[] = {"Sprites/tutorialwd.png"};
static char GameOverMenu_path[] = {"Sprites/gameoverwd.png"};
static char Stats_path[] = {"Sprites/statswd.png"};
// static char StartGame_path[] = {"Sprites/pausewd.png"};

static char Statistics_path[] = {"Stats/stats.txt"};

static char gButtonControlGame_PAUSE_path[] = {"Sprites/pausebutton.png"};
static char gButtonControlGame_PLAY_path[]={"Sprites/playbutton.png"};
static char gButtonControlGame_REPLAY_path[]={"Sprites/restartbutton.png"};
static char gButtonControlGame_EXIT_path[]={"Sprites/stopbutton.png"};


static char Sphere_Bullet_path[] = {"Sprites/bulletBird1.png"};
static char Laser_Bullet_path[] = {"Sprites/bulletBird2.png"};
static char Other_Type_Bullet_path[] = {"Sprites/bulletBird3.png"};
static char Creepy_path[] = {"Sprites/threat1.png"};
static char Threat_path[] = {"Sprites/threat.png"};

static char Money_path[] = {"Sprites/Money.png"};
static char Shield_path[] = {"Sprites/shieldx.png"};
static char Bubble_path[] = {"Sprites/bubbleshieldx.png"};

static char Bullet_Threat1_path[] = {"Sprites/bulletx1.png"};
static char Explosion_path[] = {"Sprites/Expolosion.png"};
static char Explosion_Bullet_path[] = {"Sprites/explosion.png"};
static char Plant_path[] = {"Sprites/plantX.png"};
static char Icicle_path[] = {"Sprites/Icicle2.png"};


static char PipeRed_path[] = {"Sprites/pipeRed.png"};
static char PipeBlue_path[] = {"Sprites/pipeBlue.png"};
static char PipeGreen_path[] = {"Sprites/pipeGreen.png"};

static char gFly_path[] = {"Sound/wing.wav"};
static char gMusic_path[] = {"Sound/musicBackground.wav"};
static char gSwoosh_path[] = {"Sound/swoosh.wav"};
static char gSwapBullet_path[] = {"Sound/swapBullet.wav"};
static char gExplosion_path[] = {"Sound/explosion.wav"};
static char gDie_path[] = {"Sound/die.wav"};
static char gMoneyCol_path[] = {"Sound/moneyCol.wav"};
static char gBubbleAdd_path[] = {"Sound/bubbleAdd.wav"};
static char gBubllePow_path[] = {"Sound/bubblePow.wav"};
static char gScoreIncrement_path[] = {"Sound/scoreMusic.wav"};

#define GA_FAILED -1

                                                //SCREEN
 
const int SCREEN_WIDTH = 1280,    
  SCREEN_HEIGHT = 800,
  BACKGROUND_WIDTH = 1280,
  BACKGROUND_HEIGHT = 800,
  BASE_WIDTH = 1182,
  BASE_HEIGHT = 134,
  BASE_QUARTER_WIDTH = BASE_WIDTH / 4,
  BACKGROUND_FRAME = 8,
  UNDER_LIMIT_THREAT = 200,
  FLYING_ANIMATION_FRAMES_OF_BIRD = 3,

                                                //FONT
  SIZE_OF_FONT = 28,      
                                              //BULLET
  BULLET_TYPES = 2;
                                              //
int bullet[BULLET_TYPES] = {50,51};      
                                                    //FUNCTION
bool Initialize();  
bool LoadingMedia();
void ShutdownMedia();

int getRandomNumber(int size)   {return rand() % size + 1;}
                                                            //DECLARE SDL
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
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
Mix_Chunk *gMoneyCol = NULL;
Mix_Chunk *gSwapBullet = NULL;
Mix_Chunk *gDie = NULL;
Mix_Chunk *gExplosion = NULL;
Mix_Chunk *gBubbleAdd = NULL;
Mix_Chunk *gBubblePow = NULL;
Mix_Chunk *gScoreIncrement = NULL;
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
        bool CheckFocusWithRect(const int& x, const int& y,  const SDL_Rect& rect);
        void showInfo(string recommend, string str, int x_pos, int y_pos,int text_color,SDL_Rect rect_,string path_,TTF_Font *gFont_);

        int ShowMenuGameOver2(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            const std::string& menu5,
                            const std::string& img_name);

        int ShowMenuStart(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            const std::string& img_name);

        int ShowTutorialWindow(SDL_Renderer* des,
                            TTF_Font* font,
                            const std::string& menu1, 
                            const std::string& menu2,
                            // const std::string& menu3,
                            // const std::string& menu4,
                            const std::string &img_name);        
        int ShowMenuStart2(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            // BaseObject gBackground);   
                            const std::string& img_name);

}
void SDLCommonFunc::ApplySurfaceClip(SDL_Texture* src, SDL_Renderer* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    if (clip != NULL) {
        offset.w = clip->w; 
        offset.h = clip->h;
        SDL_RenderCopyEx(gRenderer, src, clip, &offset,0,NULL,SDL_FLIP_NONE);

    } 
                                                    // QUERY THE TEXTURE TO GET  ITS WIDTH AND HEIGHT IF NO CLIP IS PROVIDED
    else SDL_QueryTexture(src, NULL, NULL, &offset.w, &offset.h);
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
SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);

  return offset;
}

int SDLCommonFunc::ShowTutorialWindow(SDL_Renderer* des,
                            TTF_Font* font,
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name){
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 2;
    char* labels[kMenuNum];

    labels[0] = new char [size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 124,15,37 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, des);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, des);


    SDL_Rect pos[kMenuNum];
    pos[0].x = 300;
    pos[0].y = 450;

    pos[1].x = 800;
    pos[1].y = 465;

    BaseObject gBackground;
    bool ret = gBackground.LoadImageFile(img_file, des);
    SDL_Rect rect_tutor = {200,100,900,485};
    gBackground.RenderImage(des,rect_tutor);


    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[1].Free();
                gBackground.Free();


                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i){
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h){
                        if (!selected[i]){
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                    else{
                        if (selected[i]){
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();

                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();

                    return 1;
                }
            }
        }

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(des, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }


        SDL_RenderPresent(des);
        gBackground.Free();
        text_object[0].Free();
        text_object[1].Free();

        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    text_object[0].Free();
    text_object[1].Free();
    gBackground.Free();
    return 0;
}

int SDLCommonFunc::ShowMenuGameOver2(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            const std::string& menu5,
                            const std::string& img_name)
{
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* ch3 = (char*)menu3.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();
    int size3 = menu3.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 3;
    char* labels[kMenuNum];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];
    labels[2] = new char[size3 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);
    strcpy_s(labels[2], size3+1, ch3);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 124, 15, 37 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, des);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, des);

    text_object[2].SetText(labels[2]);
    text_object[2].setColor(color[0].r, color[0].g, color[0].b);
    text_object[2].loadFromRenderedText(font, des);

    SDL_Rect pos[kMenuNum];
    pos[0].x = 300;
    pos[0].y = 450 ;

    pos[1].x = 550;
    pos[1].y = 350;

    pos[2].x = 700;
    pos[2].y = 450;

    BaseObject gBackground;
    bool ret = gBackground.LoadImageFile(img_file, des);
    SDL_Rect rect_pause = {200,100,900,485};
    // gBackground.RenderImage(des,rect_pause);

    TextObject text_coins;
    TextObject text_score;
    std::string val_str = menu4;
    std::string count_str("Total Coins: ");
    count_str += val_str;
    text_coins.setColor(124,15,37);
    text_coins.SetText(count_str);
    text_coins.loadFromRenderedText(gFontMENU,des);
    std::string val_str2 = menu5;
    std::string count_str2("Highest Score: ");
    count_str2 += val_str2;
    text_score.setColor(124,15,37);
    text_score.SetText(count_str2);
    text_score.loadFromRenderedText(gFontMENU,des);

    gBackground.RenderImage(des,rect_pause);
    text_score.RenderText(des,350, 260);
    text_coins.RenderText(des,350, 190);

    SDL_Event event;
    while (true){
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[1].Free();
                text_object[2].Free();
                gBackground.Free(); 
                text_coins.Free();
                text_score.Free();
                SDL_DestroyTexture(menu[0]);
                SDL_DestroyTexture(menu[1]);
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i){
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h){
                        if (!selected[i]){
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                    else{
                        if (selected[i]){
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        text_object[2].Free();
                        gBackground.Free();
                        text_coins.Free();
                        text_score.Free();
                        // SDL_DestroyTexture(menu[0]);
                        // SDL_DestroyTexture(menu[1]);
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    text_object[2].Free();
                    // SDL_DestroyTexture(menu[0]);
                    // SDL_DestroyTexture(menu[1]);
                    gBackground.Free();
                    text_coins.Free();
                    text_score.Free();
                    return 1;
                }
            }
        }
        
        


        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(des, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }
        SDL_RenderPresent(des);

        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    gBackground.Free();
    text_object[0].Free();
    text_object[1].Free();
    text_object[2].Free();
    SDL_DestroyTexture(menu[0]);
    SDL_DestroyTexture(menu[1]);
    text_coins.Free();
    text_score.Free();
    return 0;
}
void SDLCommonFunc:: showInfo(string recommend, string str, int x_pos, int y_pos,int text_color,SDL_Rect rect_,string path_,TTF_Font *gFont_){
    TextObject text_;
    BaseObject base;
    std::string val_str = str;
    std::string count_str(recommend);
    count_str += val_str;
    text_.SetColor(text_color);
    text_.SetText(count_str);
    text_.loadFromRenderedText(gFont_, gRenderer);
    text_.RenderText(gRenderer, x_pos, y_pos);
    base.LoadImageFile(path_,gRenderer);
    base.RenderImage(gRenderer,rect_);
}
int SDLCommonFunc::ShowMenuStart(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            const std::string& img_name){
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* ch3 = (char*)menu3.c_str();
    char* ch4 = (char*)menu4.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();
    int size3 = menu3.length();
    int size4 = menu4.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 4;
    char* labels[kMenuNum];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];
    labels[2] = new char[size3 + 1];
    labels[3] = new char[size4 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);
    strcpy_s(labels[2], size3+1, ch3);
    strcpy_s(labels[3], size4+1, ch4);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 ,0, 0};
    SDL_Color color[2] = { { 0, 0, 0 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, des);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, des);

    text_object[2].SetText(labels[2]);
    text_object[2].setColor(color[0].r, color[0].g, color[0].b);
    text_object[2].loadFromRenderedText(font, des);

    text_object[3].SetText(labels[3]);
    text_object[3].setColor(color[0].r, color[0].g, color[0].b);
    text_object[3].loadFromRenderedText(font, des);


    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.4 - 80;
    pos[0].y = SCREEN_HEIGHT/3 ;

    pos[1].x = SCREEN_WIDTH*0.5 - 70;
    pos[1].y = SCREEN_HEIGHT/3 + 60;

    pos[2].x = SCREEN_WIDTH/2 - 150;
    pos[2].y = SCREEN_HEIGHT/3 + 120;

    pos[3].x = SCREEN_WIDTH*0.3 ;
    pos[3].y = SCREEN_HEIGHT/3 +180;

    BaseObject gBackground;
    bool ret = gBackground.LoadImageFile(img_file, des);
    gBackground.Render(des, NULL);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[1].Free();
                text_object[2].Free();
                text_object[3].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        text_object[2].Free();
                        text_object[3].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    text_object[2].Free();
                    text_object[3].Free();
                    gBackground.Free();
                    return 1;
                }
            }
        }

        gBackground.Render(des, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(des, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }
        // gBackground.Render(des, NULL);


        SDL_RenderPresent(des);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}
int SDLCommonFunc::ShowMenuStart2(SDL_Renderer* des, TTF_Font* font, 
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& menu3,
                            const std::string& menu4,
                            const std::string& img_name){
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* ch3 = (char*)menu3.c_str();
    char* ch4 = (char*)menu4.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();
    int size3 = menu3.length();
    int size4 = menu4.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 4;
    char* labels[kMenuNum];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];
    labels[2] = new char[size3 + 1];
    labels[3] = new char[size4 + 1];

    strcpy_s(labels[0], size1+1, ch1);
    strcpy_s(labels[1], size2+1, ch2);
    strcpy_s(labels[2], size3+1, ch3);
    strcpy_s(labels[3], size4+1, ch4);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 ,0, 0};
    SDL_Color color[2] = { { 0, 0, 0 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, des);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, des);

    text_object[2].SetText(labels[2]);
    text_object[2].setColor(color[0].r, color[0].g, color[0].b);
    text_object[2].loadFromRenderedText(font, des);

    text_object[3].SetText(labels[3]);
    text_object[3].setColor(color[0].r, color[0].g, color[0].b);
    text_object[3].loadFromRenderedText(font, des);


    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.4 - 80;
    pos[0].y = SCREEN_HEIGHT/3 ;

    pos[1].x = SCREEN_WIDTH*0.5 - 70;
    pos[1].y = SCREEN_HEIGHT/3 + 60;

    pos[2].x = SCREEN_WIDTH/2 - 150;
    pos[2].y = SCREEN_HEIGHT/3 + 120;

    pos[3].x = SCREEN_WIDTH*0.3 ;
    pos[3].y = SCREEN_HEIGHT/3 +180;

    BaseObject gBackground;
    bool ret = gBackground.LoadImageFile(img_file, des);
    SDL_Rect rect_start = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[1].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, des);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        text_object[2].Free();
                        text_object[3].Free();
                        gBackground.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    text_object[2].Free();
                    text_object[3].Free();
                    gBackground.Free();
                    return 1;
                }
            }
        }

        // gBackground.Render(des, NULL);
        gBackground.RenderImage(gRenderer,rect_start);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(des, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }


        SDL_RenderPresent(des);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
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

#endif
