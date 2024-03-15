#ifndef Game_h
#define Game_h
#include <windows.h>
#include "F:\\Lap trinh cung C++\\FLoppyBird\\file.h\\Object\\SDL\\include\\SDL2\\SDL.h"
#include "Pause.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
#include "impTimer.h"
#include "BaseObject.h"
#include "ThreatObject.h"
#include "Explosion.h"

class Game : public BaseObject{
  
private:    
    int score = 0;
    ThreatObject* p_threat_list = new ThreatObject[NUM_THREAT];
    Bird bird;
    Pipe pipe;
    Pause OptionInGame;
    ImpTimer fps_timer;
    ExplosionObject  explosion;
public:
    void Play();
    void DeleteAll();
    void CollisionWithFrame();
    void changeFPS();
};


void Game::Play(){

// bird.SetRect(SCREEN_WIDTH/4,SCREEN_HEIGHT/2);
//  Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); //  GENERATE THE FIRST PIPE

for(int t = 0; t < NUM_THREAT; t++){                //  GENERATE THE THREAT 
    ThreatObject* p_threat = (p_threat_list + t);
    if(p_threat){
        p_threat->LoadImageFile("Sprites/redbird1.png",gRenderer);
        int rand_y = SDLCommonFunc::MakeRandValue();
        p_threat->SetRect(SCREEN_WIDTH + t*DISTANCE_BETWEEN_THREATS ,rand_y); //400: DISTANCE BETWEEN THREATS
        p_threat->set_x_val(THREAT_VELOCITY);                         // SET VELOCITY_THREAT
        BulletObject* p_bullet = new BulletObject();    //INTIALIZE BULLET FOR THREAT
        p_threat->InitBullet(p_bullet);
    }
}
//INITIALIZE  EXPLOSION OBJECT
    explosion.LoadImageFile("Sprites/Expolosion.png", gRenderer);
    explosion.set_clip();
 Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); //  GENERATE THE FIRST PIPE

while (!quit) {
    fps_timer.start();
    while (SDL_PollEvent(&e) != 0){
//MOUSEBUTTONDOWN
    if(e.type == SDL_MOUSEBUTTONDOWN)       
    if(e.button.button == SDL_BUTTON_LEFT ){
        bird.LoadBullet();
        Mix_PlayChannel(-1,gSwoosh,0);
    }

//  KEY
    if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  {quit = true;}
    else if (e.type == SDL_KEYDOWN){
        switch( e.key.keysym.sym ){  
            case SDLK_b:
                std::swap(bullet[0],bullet[1]); //SWITCH TYPE BULLET (IN DECLARATION)
                Mix_PlayChannel(-1,gSwapBullet,0);
                break;

            case SDLK_w: case  SDLK_UP:  case SDLK_SPACE:   //BIRD SWING
                bird.jump();
                Mix_PlayChannel( -1, gFly, 0 );
                break;

            case SDLK_m://PLAY THE MUSIC
                if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); 
                else{
                    if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();   //RESUME THE MUSIC 
                    else  Mix_PauseMusic();                 //PAUSE THE MUSIC                       
                }
                break;

            case SDLK_0:    //STOP THE MUSIC
                Mix_HaltMusic();   
                break;
        }
    }
///OPTION_CONTROL_GAME LOGIC

    OptionInGame.handleEvent( &e );
    if (OptionInGame.mPresentState[EXIT])       quit = true; 

    if(OptionInGame.mPresentState[REPLAY]){  
        bird.resetPositon();  
        OptionInGame.mPresentState[PAUSE] = false;
        OptionInGame.mPresentState[REPLAY] = false;
    }
    OptionInGame.render();   
    if(OptionInGame.mPresentState[PAUSE]){
        // Sleep(500); //10s
        SDL_Delay(100);
        // return;
    }
}

    if( bird.strikeObstacle().y +  bird.strikeObstacle().h >= SCREEN_HEIGHT - BASE_HEIGHT ||  bird.strikeObstacle().y < - PIPE_HEIGHT) quit = true;     

    if( checkCollision(pipe.strikeLowerObstacle(),  bird.strikeObstacle())||checkCollision( bird.strikeObstacle(), pipe.strikeUpperObstacle())){
        /*mã game: sau khi va chạm 
        => reset
        =>revive*/
        // COLLISION_WITH_OBSTACLE();
        quit = true;     
    }
    //tính điểm 
    if(abs( bird.strikeObstacle().x - pipe.strikeUpperObstacle().x) <=10 || abs(  bird.strikeObstacle().x - pipe.strikeLowerObstacle().x) <= 10)    cout << ++score<<endl;
                                                //LOADING SCREEN_FRAME
    BuildScreen();                              
                                                //BIRD & BULLET_BIRD => UPDATE POSITION AND RENDER 
    bird.update(); 
    bird.HandleBullet(gRenderer,pipe); 


    bird.render();          

    for(int tt = 0; tt < NUM_THREAT;tt++){                                    //IMPLEMENT THREAT
        ThreatObject* p_threat = (p_threat_list + tt);
        if(p_threat){                                                         //CHECK POINTER IS NULL OR NOT
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->Render(gRenderer);
                                                                            //GENERATE BULLET FOR THREAT
            p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT,pipe);     
                                                                            //CHECK COLLISION BIRD AND THREATS
            bool is_collision = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_threat->GetRect());
            // bool is_collision = SDLCommonFunc::CheckCollision( bird.strikeObstacle(),p_threat->GetRect());
            if(is_collision){

                for(int ex = 0; ex < 4; ex++){
                    int xPos = ( bird.strikeObstacle().x + bird.strikeObstacle().w*0.5) - EXP_WIDTH * 0.5;
                    int yPos = ( bird.strikeObstacle().y + bird.strikeObstacle().h*0.5) - EXP_HEIGHT * 0.5;
                    explosion.set_frame(ex);
                    explosion.SetRect(xPos,yPos);
                    explosion.ShowEx(gRenderer);
                    SDL_Delay(100);
                }
                /*if(GAME OVER){
                    delete[] p_threat_list;
                }*/
                //To do
                //isDie
                //choose button replay,exit
                quit = true;
            }
            //CHECK BULLET_BIRD WITH THREATS
            std::vector<BulletObject*> bullet_list = bird.get_bullet_list();
            for(int ib = 0; ib < bullet_list.size(); ib++){
                BulletObject* p_bullet = bullet_list.at(ib);
                if(p_bullet!=NULL){
                    bool ret_collision = SDLCommonFunc::CheckCollision(p_bullet->GetRect(),p_threat->GetRect());
                    if(ret_collision){
                        //=> DELETE THREATS, BULLET_BIRD => INCREASE MONEY,ITEMS,..
                        p_threat->Reset(SCREEN_WIDTH + tt * DISTANCE_BETWEEN_THREATS);  //RESET POSI THREAT
                        bird.RemoveBullet(ib);                                          //REMOVE BULLET BIRD
                    }                    
                }
            }
        }
    }

    pipe.update();      pipe.render();          //PIPE

    OptionInGame.render();                      //OPTION_CONTROL_GAME
    SDL_RenderPresent(gRenderer);

    changeFPS();                                //FPS
    }
    
}
void Game :: DeleteAll(){
    close();
   
}
void Game :: changeFPS(){
    int real_imp_time = fps_timer.get_ticks();          // calculate how long it took to render this
    int time_one_frame = 1000/FRAME_PER_SECOND;         //ms
    if (real_imp_time < time_one_frame){
        int delay_time  = time_one_frame-real_imp_time ;   //delay to make one frame
        if(delay_time >= 0) SDL_Delay(delay_time);
    }
}
void Game::CollisionWithFrame(){
    
}
#endif
