#ifndef GENERATING_PIPE_H
#define GENERATING_PIPE_H
class Pipe {
public:
    int x, height,width;
    Pipe(int startX, int pipeHeight) {
        x = startX;
        height = pipeHeight;
        width = PIPE_WIDTH;
    }
    void update() { 
        x -= PIPE_VELOCITY;
        if (x + PIPE_WIDTH < 0) {
            x = SCREEN_WIDTH;
            height = rand() % (SCREEN_HEIGHT - BASE_HEIGHT*2) ; // 2 random
        }
    }
    void render() {
        SDL_Rect upperPipeRect = { x, UPPER_PIPE_OFFSET, PIPE_WIDTH, height  };
        SDL_Rect lowerPipeRect = { x, height + LOWER_PIPE_OFFSET, PIPE_WIDTH, SCREEN_HEIGHT - (LOWER_PIPE_OFFSET+LOWER_PIPE_HEIGHT_OFFSET+height)};
        // SDL_RenderCopy(gRenderer, pipeTexture, NULL, &upperPipeRect);
        SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    }
     SDL_Rect strikeUpperObstacle() {
        SDL_Rect Obstacle = { x, UPPER_PIPE_OFFSET, width, height }; //need to check
        return Obstacle;
    }

    SDL_Rect strikeLowerObstacle() const {
        SDL_Rect Obstacle = { x, height + LOWER_PIPE_OFFSET, width, SCREEN_HEIGHT - height - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET) };//need to check
        return Obstacle;
    }
};

#endif
