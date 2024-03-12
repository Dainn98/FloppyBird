#ifndef Game_h
#define Game_h
#include "Pause.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
Bird bird;
Pipe pipe;
Pause OptionInGame;

class Game {
    private:
    int score;
    public:
    
    void Play();
    void updateScore();
};
void Game::Play(){
    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);          //clear screen
    SDL_RenderClear(gRenderer);

    Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); // 1 random
    while (!quit) {
        solveEvent();
         

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


        if(abs(birdStrikeObstacle.x - birdStrikeUpperObstacle.x) <=20 &&
            abs( birdStrikeObstacle.x - birdStrikeLowerObstacle.x) <= 20)
                cout <<" score "<<endl;
        


        if(birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -150) quit = true;
         BuildScreen();
        bird.update();      bird.render();
        pipe.update();      pipe.render();

        OptionInGame.render();

        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);
        SDL_Delay(DELAY);
        // cout << DELAY<<endl;
    }
}
void solveEvent(){
     while (SDL_PollEvent(&e) != 0){
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
            bird.init();  
            


            OptionInGame.mPresentState[PAUSE] = false;
            OptionInGame.mPresentState[REPLAY] = false;
        }
        OptionInGame.render();   
        if(OptionInGame.mPresentState[PAUSE]){
            
        }
    }
}
// void Game::updateScore(){
//     SDL_Rect    birdStrikeObstacle = bird.strikeObstacle(),
//                 birdStrikeUpperObstacle = pipe.strikeUpperObstacle(),
//                 birdStrikeLowerObstacle = pipe.strikeLowerObstacle();
//     if(abs(birdStrikeObstacle.x - birdStrikeUpperObstacle.x) <=20 &&
//       abs( birdStrikeObstacle.x - birdStrikeLowerObstacle.x) <= 20){
//         cout <<" score "<<endl;
//        }
    
// }
#endif
