#ifndef Game_h
#define Game_h
#include <windows.h>
#include "F:\\Lap trinh cung C++\\FLoppyBird\\file.h\\Object\\SDL\\include\\SDL2\\SDL.h"
// #include "F:\Lap trinh cung C++\FLoppyBird\file.h\Object\SDL\include\SDL2\SDL_ttf.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Pause.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
#include "impTimer.h"
#include "BaseObject.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "PlantObject.h"
#include "Collision_With_Obstacles.h"



class Game : public BaseObject{
  
private:    
    unsigned int bullet_type_ = 50;
  
    ThreatObject* p_threat_list = new ThreatObject[NUM_THREAT];
    Bird bird;
    Pipe pipe;
    Pause OptionInGame;
    ImpTimer fps_timer;
    ExplosionObject explosion_Collision;
    ExplosionObject bullet_explosion;
    IcicleObject icicle;
    PlantObject plant;
    Collision collision;
    TextObject text_count_;  
    TextObject text_money_game_;

public:
    void Play();
};


void Game::Play(){
    SDL_SetRenderDrawColor(gRenderer,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B,0xFF);       //CLEAR SCREEN   
	SDL_RenderClear(gRenderer);
    Mix_PlayMusic( gMusic, -1 );

again_label:

//TEXT  
    text_count_.SetColor(TextObject::BLACK_TEXT);
    text_money_game_.SetColor(TextObject::WHITE_TEXT);
                                                                        //  GENERATE THE FIRST PIPE
    Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); 
                                                                        //  GENERATE THE THREAT 
    for(int t = 0; t < NUM_THREAT; t++){                
        ThreatObject* p_threat = (p_threat_list + t);
        if(p_threat){
            p_threat->LoadImageFile(Creepy_path,gRenderer);
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_threat->SetRect(SCREEN_WIDTH + t*DISTANCE_BETWEEN_THREATS ,rand_y); 
            p_threat->set_x_val(THREAT_VELOCITY);                           // SET VELOCITY_THREAT
            BulletObject* p_bullet = new BulletObject();                    //INTIALIZE BULLET FOR THREAT
            p_threat->InitBullet(p_bullet); 
        }
    }
                                                                            //INITIALIZE  EXPLOSION OBJECT
    explosion_Collision.LoadImageFile(Explosion_path, gRenderer);
    explosion_Collision.set_clip_explosion();
    bullet_explosion.LoadImageFile(Explosion_Bullet_path,gRenderer);
    bullet_explosion.set_clip_bullet_explosion();

    plant.LoadImageFile(Plant_path,gRenderer);
    plant.set_clip_plant();

    icicle.LoadImageFile(Icicle_path,gRenderer);
    icicle.set_clip_icicle();


    unsigned int money = 0;
    unsigned int  score = 0;
     int moveY = 0;

                                                                            //INITIALIZE PIRANHA OBJECT

                                                                            //INITIALIZE ICE OBJCET
while (!quit) {
    fps_timer.start();
    while (SDL_PollEvent(&e) != 0){
                                                                            //MOUSEBUTTONDOWN
        if(e.type == SDL_MOUSEBUTTONDOWN)       
        if(e.button.button == SDL_BUTTON_LEFT ){
            bird.LoadBullet();
            Mix_PlayChannel(-1,gSwoosh,0);
        }
                                                                                //KEY
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  {quit = true;}
        else if (e.type == SDL_KEYDOWN){
            switch( e.key.keysym.sym ){  
                case SDLK_b:
                                                                                //SWITCH TYPE BULLET (IN DECLARATION)
                    std::swap(bullet[0],bullet[1]); 
                    Mix_PlayChannel(-1,gSwapBullet,0);
                    break;
                                                                                //BIRD SWING
                case SDLK_w: case  SDLK_UP:  case SDLK_SPACE:   
                    bird.jump();
                    Mix_PlayChannel( -1, gFly, 0 );
                    break;
                                                                                //PLAY THE MUSIC
                case SDLK_m:
                    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); 
                    else{
                        if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();           //RESUME THE MUSIC 
                        else  Mix_PauseMusic();                                 //PAUSE THE MUSIC                       
                    }
                    break;
                                                                                //STOP THE MUSIC
                case SDLK_0:    
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
            goto again_label;
        }
        OptionInGame.render();   
        if(OptionInGame.mPresentState[PAUSE]){
    //To do
        }
    }
    // if( bird.strikeObstacle().y +  bird.strikeObstacle().h >= SCREEN_HEIGHT - BASE_HEIGHT ||  bird.strikeObstacle().y < - PIPE_HEIGHT) quit = true;     

    if( SDLCommonFunc::CheckCollision (pipe.strikeLowerObstacle(),bird.strikeObstacle())||
        SDLCommonFunc::CheckCollision (bird.strikeObstacle(),pipe.strikeUpperObstacle())){
        //To do GameOver
            collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
            // Mix_PlayChannel( -1, gDie, 0 );
    }
    //tính điểm 
                                                                                                //LOADING SCREEN_FRAME
    BuildScreen();                              
                                                                                                //BIRD & BULLET_BIRD => UPDATE POSITION AND RENDER 
    bird.update();
    bird.HandleBullet(gRenderer,pipe);                      
    bird.render();   
                                                                                                //IMPLEMETN PLANT & COLLISION
    int random_plant = getRandomNumber(NUM_PLANT)-1;
    collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,gRenderer,random_plant);
                                                                                                //IMPLEMETN ICICLE & COLLISION
    int random_icicle = getRandomNumber(NUM_ICICLE)-1;
    collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,gRenderer,random_icicle,moveY);
                                                                                                //IMPLEMENT THREAT
    for(int tt = 0; tt < NUM_THREAT;tt++){                                   
        ThreatObject* p_threat = (p_threat_list + tt);
        if(p_threat){                                                                           //CHECK POINTER IS NULL OR NOT
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->Render(gRenderer);                                                        //LOADING BULLET FOR THREAT                            
            p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT,pipe);   
            std::vector<BulletObject*> bullet_arr = p_threat->GetBulletList();
            bool Collision_Bird_BulletOfThreat = false;
            for (int am = 0; am < bullet_arr.size(); am++){
                BulletObject* p_bullet = bullet_arr.at(am);
                if (p_bullet){
                    Collision_Bird_BulletOfThreat = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), bird.strikeObstacle());
                    if (Collision_Bird_BulletOfThreat == true){
                    p_threat->ResetBullet(p_bullet);
                    collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
                    break;
                    }
                }
            }
                                                                                            //CHECK COLLISION BIRD AND THREATS
            bool Collision_Bird_Threat = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_threat->GetRect());
            if(Collision_Bird_Threat){
                collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
                //To do
            }
                                                                                            //CHECK BULLET_BIRD WITH THREATS
            std::vector<BulletObject*> bullet_list = bird.get_bullet_list();
            for(int ib = 0; ib < bullet_list.size(); ib++){
                BulletObject* p_bullet = bullet_list.at(ib);
                if(p_bullet!=NULL){
                    bool ret_collision = SDLCommonFunc::CheckCollision(p_bullet->GetRect(),p_threat->GetRect());
                    if(ret_collision){
                        money++;
                        //=> DELETE THREATS, BULLET_BIRD => INCREASE MONEY,ITEMS,..
                         for(int ex = 0; ex < 4; ex++){
                            int xPos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - BUL_WIDTH * 0.5 ;
                            int yPos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - BUL_HEIGHT * 0.5;
                            bullet_explosion.set_frame(ex);
                            bullet_explosion.SetRect(xPos,yPos);
                            bullet_explosion.ShowBul(gRenderer);
                            Mix_PlayChannel( -1, gExplosion, 0 );
                        }
                        p_threat->Reset(SCREEN_WIDTH + tt * DISTANCE_BETWEEN_THREATS);  //RESET POSI THREAT
                        bird.RemoveBullet(ib);                                          //REMOVE BULLET BIRD
                    }                    
                }
            }
        }
    }
                                                                                        //PIPE
    pipe.update();      pipe.render();         
                                                                                        //Base
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);

                                                                                        //OPTION_CONTROL_GAME
    OptionInGame.render();                      
                                                                                        //SHOW MONEY
    std::string val_str_money = std::to_string(money);
    std::string count_money_str(" ");
    count_money_str += val_str_money;
    text_money_game_.SetText(count_money_str);
    text_money_game_.loadFromRenderedText(gFontText, gRenderer);
    text_money_game_.RenderText(gRenderer, SCREEN_WIDTH*0.1, 2);
                                                                                        //SHOW SCORE
    if(abs( bird.strikeObstacle().x - pipe.strikeUpperObstacle().x) <=10 || abs(  bird.strikeObstacle().x - pipe.strikeLowerObstacle().x) <= 10)    ++score;
    std::string val_str_mark = std::to_string(score);
    std::string count_str("Score: ");
    count_str += val_str_mark;
    text_count_.SetText(count_str);
    text_count_.loadFromRenderedText(gFontText, gRenderer);
    text_count_.RenderText(gRenderer, SCREEN_WIDTH*0.01, 2);
                                                                                        //LOADING ALL
    SDL_RenderPresent(gRenderer);
                                                                                        //CHANGE FPS
    int real_imp_time = fps_timer.get_ticks();          
    int time_one_frame = 1000/FRAME_PER_SECOND;         
    if (real_imp_time < time_one_frame){
        int delay_time  = time_one_frame-real_imp_time ;   
        if(delay_time >= 0) SDL_Delay(delay_time);
    }
    }
}
#endif
