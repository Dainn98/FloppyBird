#ifndef Game_h
#define Game_h
#include "Pause.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
#include "impTimer.h"
#include "BaseObject.h"

Bird bird;
Pipe pipe;
Pause OptionInGame;
ImpTimer fps_timer; 

class Game : public BaseObject{
    private:
        
    int score;
    public:
    void Play();
    // void updateScore();
};
void Game::Play(){
    // ImpTimer fps_timer; 
    int score = 0;
    SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);          //clear screen
    SDL_RenderClear(gRenderer);
    Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); // random the first pipe
    while (!quit) {
        fps_timer.start();


        while (SDL_PollEvent(&e) != 0){
        if(e.type == SDL_MOUSEBUTTONDOWN){
            if(e.button.button == SDL_BUTTON_LEFT ){
                bird.LoadBullet();
                // BulletObject* p_bullet = new BulletObject();
                // p_bullet->LoadImageFile("Sprites/xbullet.png",gRenderer);
                // p_bullet->SetRect(this ->rect_.x + BIRD_WIDTH - 20,rect_.y + 0.5*BIRD_HEIGHT);
                // p_bullet->set_x_val(20);
                // p_bullet->set_is_move(true);
                // p_bullet_list_->push_back(p_bullet);                 
            }
        }
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  {quit = true;}
        else if (e.type == SDL_KEYDOWN){
        switch( e.key.keysym.sym ){
            //Play high sound effect
            case SDLK_w:    case  SDLK_UP:  case SDLK_SPACE:
            bird.jump();
            Mix_PlayChannel( -1, gFly, 0 );
            break;

            case SDLK_m:
            if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); //Play the music
            else{
                if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();//Resume the music   
                else  Mix_PauseMusic(); //Pause the music
                }
            break;

            case SDLK_0:
            Mix_HaltMusic();   //Stop the music
            break;
            }
        }
        OptionInGame.handleEvent( &e );
        if (OptionInGame.mPresentState[EXIT])       quit = true; 

        if(OptionInGame.mPresentState[REPLAY]){  
            bird.resetPositon();  
            


            OptionInGame.mPresentState[PAUSE] = false;
            OptionInGame.mPresentState[REPLAY] = false;
        }
        OptionInGame.render();   
        if(OptionInGame.mPresentState[PAUSE]){
            
        }
    }
         
//check collision
        SDL_Rect     birdStrikeObstacle = bird.strikeObstacle(),
                birdStrikeUpperObstacle = pipe.strikeUpperObstacle(),
                birdStrikeLowerObstacle = pipe.strikeLowerObstacle();
        if( checkCollision(birdStrikeLowerObstacle, birdStrikeObstacle)||checkCollision(birdStrikeObstacle, birdStrikeUpperObstacle)){
            /*mã game: sau khi va chạm 
            => reset
            =>revive*/
            // COLLISION_WITH_OBSTACLE();
            quit = true;     
        }

        //tính điểm 
        if(abs(birdStrikeObstacle.x - birdStrikeUpperObstacle.x) <=10 &&
            abs( birdStrikeObstacle.x - birdStrikeLowerObstacle.x) <= 10)
                cout <<++score<<endl;
        


        if(birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -150) quit = true;
         BuildScreen();
        
        bird.HandleBullet(gRenderer);
        bird.update();      bird.render();
        pipe.update();      pipe.render();

        OptionInGame.render();

        SDL_RenderPresent(gRenderer);

        int real_imp_time = fps_timer.get_ticks();          // calculate how long it took to render this
        int time_one_frame = 1000/FRAME_PER_SECOND;         //ms
        if (real_imp_time <time_one_frame){
            int delay_time  = time_one_frame-real_imp_time ;   //delay to make one frame
            if(delay_time >= 0) SDL_Delay(delay_time);
        }
        // SDL_RenderClear(gRenderer);
        // SDL_Delay(DELAY);
        // cout << DELAY<<endl;
    }
}
void solveEvent(){
     
}
#endif
