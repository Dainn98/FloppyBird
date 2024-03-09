#include "file.h/Header.h"
int main(int argc, char* args[]) {
    if (!init()) {
        cout << "Failed to initialize." << endl;
        return -1;
    }//

    // if (argc!= 2) {
    //     cout << "Usage:./main <path>" << endl;
    //     return -1;
    // }
    loadMedia();
    Bird bird;
    Pipe pipe(SCREEN_WIDTH, getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2)); // 1 random
    while (!quit) {
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_w) bird.jump();
            }
        }
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
        if(birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -100) quit = true;
        BuildScreen();
        bird.update();      bird.render();
        pipe.update();      pipe.render();
        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);
        SDL_Delay(DELAY);
        cout << DELAY<<endl;
    }
    close();
    return 0;
}


