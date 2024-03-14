#ifndef Game_h
#define Game_h
#include <windows.h>
#include "Pause.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
#include "impTimer.h"
#include "BaseObject.h"
#include "ThreatObject.h"

Bird bird;
Pipe pipe;
Pause OptionInGame;
ImpTimer fps_timer; 

class Game : public BaseObject{
  
private:    
    int score = 0;
    ThreatObject* p_threat_list = new ThreatObject[NUM_THREAT];
public:
    void Play();
    void  DeleteAll();
    void changeFPS();
};
void Game::Play(){


Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); //  GENERATE THE FIRST PIPE

for(int t = 0; t < NUM_THREAT; t++){                //  GENERATE THE THREAT 
    ThreatObject* p_threat = (p_threat_list + t);
    if(p_threat){
    p_threat->LoadImageFile("Sprites/redbird1.png",gRenderer);
    // int rand_y = rand()%(SCREEN_HEIGHT - BASE_HEIGHT);
    // if (rand_y > SCREEN_HEIGHT - BASE_HEIGHT) rand_y = SCREEN_HEIGHT*0.3;
     int rand_y = SDLCommonFunc::MakeRandValue();
    p_threat->SetRect(SCREEN_WIDTH + t*DISTANCE_BETWEEN_THREATS ,rand_y); //400: DISTANCE BETWEEN THREATS
    p_threat->set_x_val(THREAT_VELOCITY);                         // SET VELOCITY_THREAT
    BulletObject* p_bullet = new BulletObject();    //INTIALIZE BULLET FOR THREAT
    p_threat->InitBullet(p_bullet);
    }
}
 






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
    }
}

    SDL_Rect     birdStrikeObstacle = bird.strikeObstacle(),         //COLLISION
            birdStrikeUpperObstacle = pipe.strikeUpperObstacle(),
            birdStrikeLowerObstacle = pipe.strikeLowerObstacle();
    if(birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -150) quit = true;        
    if( checkCollision(birdStrikeLowerObstacle, birdStrikeObstacle)||checkCollision(birdStrikeObstacle, birdStrikeUpperObstacle)){
        /*mã game: sau khi va chạm 
        => reset
        =>revive*/
        // COLLISION_WITH_OBSTACLE();
        quit = true;     
    }
    //tính điểm 
    if(abs(birdStrikeObstacle.x - birdStrikeUpperObstacle.x) <=10 || abs( birdStrikeObstacle.x - birdStrikeLowerObstacle.x) <= 10)    cout << ++score<<endl;
        
    BuildScreen();                              //RENDER

    bird.HandleBullet(gRenderer);               //BULLET 

    bird.update();      bird.render();          //BIRD

    for(int tt = 0; tt < NUM_THREAT;tt++){      //IMPLEMENT THREAT
        ThreatObject* p_threat = (p_threat_list + tt);
        if(p_threat){                           //CHECK POINTER IS NULL OR NOT
            p_threat->Render(gRenderer);
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);
        }
        
    }

    pipe.update();      pipe.render();          //PIPE

    OptionInGame.render();                      //OPTION_CONTROL_GAME
    SDL_RenderPresent(gRenderer);

    changeFPS();                                //FPS
    }
    
}
void Game :: DeleteAll(){
    delete[] p_threat_list;
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
#endif
