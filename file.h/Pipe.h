#ifndef GENERATING_PIPE_H
#define GENERATING_PIPE_H
#include "declaration.h"
#include "LTexture.h"
SDL_Rect gSpritePiranhaPlant[ NUMBER_OF_PIRANHA_PLANT ];
class Pipe {
public:
    int x, height,width,whichPipe;
    Pipe();
    Pipe(int startX, int pipeHeight);
    void update();
    void render();
    SDL_Rect strikeUpperObstacle();
    SDL_Rect strikeLowerObstacle();
    void intit(){
        x = SCREEN_WIDTH;
        height = getRandomNumber(PIPE_HEIGHT)+BASE_HEIGHT;
    }

};
Pipe::Pipe(){};
Pipe::Pipe(int startX, int pipeHeight){
    x = startX;
    height = pipeHeight;
    width = PIPE_WIDTH;
    
}
void Pipe::update() { 
        x -= PIPE_VELOCITY;
        if (x + PIPE_WIDTH < 50) { //số lần xuất hiện pipe
            x = SCREEN_WIDTH;
            // whichPipe = (++whichPipe) % 3 + 1;
            whichPipe = getRandomNumber(NUMBER_OF_PIPE);
            // height = rand() % (SCREEN_HEIGHT - BASE_HEIGHT*2) ; //  random 2
            height = getRandomNumber(PIPE_HEIGHT)+BASE_HEIGHT;
            DELAY -= 0.05;
            if(height < 20) height = 0;
        }
    }
void Pipe::render(){
    
        if(whichPipe % 3 == 0) {
            SDL_Rect lowerPipeRect = { x, height + LOWER_PIPE_OFFSET, PIPE_WIDTH, SCREEN_HEIGHT - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET + height)};          
            pipeSurface = IMG_Load("Sprites/pipeRed.png");
            SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
            }
        
        else if(whichPipe % 3 == 1){
            SDL_Rect upperPipeRect = { x, UPPER_PIPE_OFFSET, PIPE_WIDTH, height };   
            pipeSurface = IMG_Load("Sprites/pipeBlue.png");
            SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        }
        else if (whichPipe % 3 == 2){
            SDL_Rect lowerPipeRect = { x, height + LOWER_PIPE_OFFSET, PIPE_WIDTH, SCREEN_HEIGHT - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET + height)}; 
            SDL_Rect upperPipeRect = { x, UPPER_PIPE_OFFSET, PIPE_WIDTH, height  };   
            pipeSurface = IMG_Load("Sprites/pipeGreen.png");
            SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
            SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        }
        pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
        // SDL_FreeSurface(pipeSurface);
}
SDL_Rect Pipe:: strikeUpperObstacle(){
    if(whichPipe % 3 == 0) return emptyObstacle;
    SDL_Rect Obstacle = { x, UPPER_PIPE_OFFSET, width, height }; //need to check
    return Obstacle;
    // return emptyObstacle;
}
SDL_Rect Pipe:: strikeLowerObstacle() {
    if(whichPipe % 3 == 1) return emptyObstacle;
    SDL_Rect Obstacle = { x, height + LOWER_PIPE_OFFSET, width, SCREEN_HEIGHT - height - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET) };//need to check
    return Obstacle;
}

#endif
/*void Pipe::render(){
        SDL_Rect lowerPipeRect = { x, height + LOWER_PIPE_OFFSET, PIPE_WIDTH, SCREEN_HEIGHT - (LOWER_PIPE_OFFSET+LOWER_PIPE_HEIGHT_OFFSET+height)};
        SDL_Rect upperPipeRect = { x, UPPER_PIPE_OFFSET, PIPE_WIDTH, height  };        
        // int ranNum = getRandomNumber(NUMBER_OF_PIPE); //declaration
        // switch (whichPipe){
        //     case 1:  
        //         SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect); 
        //         break;
        //     case 2:
        //         SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        //         break;
        //     case 3: 
        //         SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
        //         SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        //     default:
        //         break;

        // }
        // SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
        // SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        // if(whichPipe == 1) SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);

        // else if (whichPipe == 2)SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);

        // else if(whichPipe == 3){
        //     SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
        //     SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        // }
         if(whichPipe == 1)pipeSurface = IMG_Load("Sprites/pipeRed.png");

        else if (whichPipe == 3)pipeSurface = IMG_Load("Sprites/pipeGreen.png");

        else if(whichPipe == 2) pipeSurface = IMG_Load("Sprites/pipeBlue.png");
        if(whichPipe == 1) SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);

        else if (whichPipe == 2)SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);

        else if(whichPipe == 3){
            SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
            SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        }
        pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
         SDL_FreeSurface(pipeSurface);
}*/