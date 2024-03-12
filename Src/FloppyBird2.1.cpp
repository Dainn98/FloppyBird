#include "file.h/Header.h"
void solveEvent();
Bird bird;
Pipe pipe;
Pause OptionInGame;
int main(int argc, char* args[]) {
    //create SDL and Window
    init();
    loadMedia();

    SDL_SetRenderDrawColor(gRenderer,0,0,0,0);          //clear screen
    SDL_RenderClear(gRenderer);

    Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); // 1 random
    while (!quit) {
        solveEvent();
         if(OptionInGame.mCurrentState[REPLAY]){  
              OptionInGame.mCurrentState[PAUSE] = false;
            OptionInGame.mCurrentState[REPLAY] = false;
        }
        BuildScreen();
        OptionInGame.render();   
        if(OptionInGame.mCurrentState[PAUSE]){
            

        }

//check collision
        // SDL_Rect     birdStrikeObstacle = bird.strikeObstacle(),
        //         birdStrikeUpperObstacle = pipe.strikeUpperObstacle(),
        //         birdStrikeLowerObstacle = pipe.strikeLowerObstacle();
        // if( checkCollision(birdStrikeLowerObstacle, birdStrikeObstacle)||checkCollision(birdStrikeObstacle, birdStrikeUpperObstacle)){
        //     /*mã game: sau khi va chạm 
        //     => reset
        //     =>revive*/
        //     // COLLISION_WITH_OBSTACLE();
        //     quit = true;     
        // }
        // if(birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -150) quit = true;
        bird.update();      bird.render();
        pipe.update();      pipe.render();

        OptionInGame.render();

        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);
        SDL_Delay(DELAY);
        cout << DELAY<<endl;
    }
    close();
    return 0;
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
            if (OptionInGame.mCurrentState[EXIT])       quit = true; 
    }
}

