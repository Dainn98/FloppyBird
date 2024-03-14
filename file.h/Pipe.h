#ifndef GENERATING_PIPE_H
#define GENERATING_PIPE_H
#include "declaration.h"
#include "LTexture.h"

class Pipe:public BaseObject {
public:
    Pipe();
    ~Pipe();

    Pipe(int posX, int pipe_height);

    void update();
    void render();

    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    SDL_Rect strikeUpperObstacle();
    SDL_Rect strikeLowerObstacle();
private:
    int x_val_,
        y_val_,
        height_,
        width_,
        whichPipe;
};

Pipe::Pipe(){
    x_val_ = SCREEN_WIDTH;
    y_val_ = getRandomNumber(PIPE_HEIGHT)+BASE_HEIGHT;
};
Pipe::Pipe(int posX, int pipe_height){
    x_val_ = posX;
    height_ = pipe_height;
    width_ = PIPE_WIDTH;
    
}
void Pipe::update() { 
        x_val_ -= PIPE_VELOCITY;
        if (x_val_ + PIPE_WIDTH < 0) { //số lần xuất hiện pipe
            x_val_ = SCREEN_WIDTH;
            whichPipe = getRandomNumber(NUMBER_OF_PIPE);
            height_ = getRandomNumber(PIPE_HEIGHT)+BASE_HEIGHT;
            FRAME_PER_SECOND += 0.5;
            if(height_ < BASE_HEIGHT + 20) height_ = 0;
        }
    }
void Pipe::render(){
    SDL_Rect lowerPipeRect ={x_val_,
                            height_ + LOWER_PIPE_OFFSET,
                            PIPE_WIDTH,
                            SCREEN_HEIGHT - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET + height_)},          
             upperPipeRect ={x_val_,
                            UPPER_PIPE_OFFSET,
                            PIPE_WIDTH,
                            height_};  

    if(whichPipe % 3 == 0) {
        pipeSurface = IMG_Load("Sprites/pipeRed.png");
        upperPipeRect = emptyObstacle;
        }
    else if(whichPipe % 3 == 1){
        pipeSurface = IMG_Load("Sprites/pipeBlue.png");
        lowerPipeRect = emptyObstacle;
    }
    else if (whichPipe % 3 == 2) pipeSurface = IMG_Load("Sprites/pipeGreen.png");
    
    SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);
}
SDL_Rect Pipe:: strikeUpperObstacle(){
    if(whichPipe % 3 == 0) return emptyObstacle;
    SDL_Rect Obstacle = { x_val_, UPPER_PIPE_OFFSET, width_, height_ }; //need to check
    return Obstacle;
}
SDL_Rect Pipe:: strikeLowerObstacle() {
    if(whichPipe % 3 == 1) return emptyObstacle;
    SDL_Rect Obstacle = { x_val_, height_ + LOWER_PIPE_OFFSET, width_, SCREEN_HEIGHT - height_ - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET) };//need to check
    return Obstacle;
}
Pipe::~Pipe(){
    x_val_ = 0;
    y_val_ = 0;
    height_ = 0;
    width_ = 0;
    whichPipe = -1;
}
#endif