#ifndef GENERATING_PIPE_H
#define GENERATING_PIPE_H
// #include "declaration.h"
// #include "LTexture.h"
const int   PIPE_WIDTH = 100,       
            NUMBER_OF_PIPE = 100,
            UPPER_PIPE_OFFSET = -40,
            LOWER_PIPE_OFFSET = 150,
            PIPE_HEIGHT = 300,
            LOWER_PIPE_HEIGHT_OFFSET = 134,
            PIPE_VELOCITY = 15;
class Pipe:public BaseObject {
public:
    Pipe();
    ~Pipe();

    void init_pipe();

    void update();
    void render();

    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}
    int get_width_pipe() const {return width_;}
    int get_height_pipe() const{return height_;}
    int get_which_pipe() const {return which_pipe_;}

    SDL_Rect strikeUpperObstacle();
    SDL_Rect strikeLowerObstacle();
private:
    int x_val_,
        y_val_,
        height_,
        width_,
        which_pipe_= getRandomNumber(NUMBER_OF_PIPE);;
};

Pipe::Pipe(){
    x_val_ = SCREEN_WIDTH;
    y_val_ = getRandomNumber(PIPE_HEIGHT)+BASE_HEIGHT;
    width_ = PIPE_WIDTH;

};
// Pipe::Pipe(int posX, int pipe_height){
//     x_val_ = posX;
//     height_ = pipe_height;
// }
void Pipe:: init_pipe(){
    x_val_ = SCREEN_WIDTH;
    height_ = getRandomNumber(SCREEN_HEIGHT - BASE_HEIGHT*2);
}
void Pipe::update() { 
        x_val_ -= PIPE_VELOCITY;
        if (x_val_ + PIPE_WIDTH < 0) { //số lần xuất hiện pipe
            x_val_ = SCREEN_WIDTH;
            which_pipe_ = getRandomNumber(NUMBER_OF_PIPE);
            height_ = getRandomNumber(PIPE_HEIGHT*1.5)+BASE_HEIGHT;
            FRAME_PER_SECOND += 0.5;
            if(height_ < 150){
                which_pipe_ = 2;
                height_ = PIPE_HEIGHT;
            }
        }
    }
void Pipe::render(){
    SDL_Rect lowerPipeRect ={x_val_,
                            height_ + LOWER_PIPE_OFFSET,
                            PIPE_WIDTH,
                            // SCREEN_HEIGHT - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET + height_)},
                            SCREEN_HEIGHT - LOWER_PIPE_OFFSET - LOWER_PIPE_HEIGHT_OFFSET},          
             upperPipeRect ={x_val_,
                            UPPER_PIPE_OFFSET,
                            PIPE_WIDTH,
                            height_};  

    if(which_pipe_ % 3 == 0) {
        pipeSurface = IMG_Load(PipeRed_path);
        upperPipeRect = emptyObstacle;
        }
    else if(which_pipe_ % 3 == 1){
        pipeSurface = IMG_Load(PipeBlue_path);
        lowerPipeRect = emptyObstacle;
    }
    else if (which_pipe_ % 3 == 2) pipeSurface = IMG_Load(PipeGreen_path);
    
    SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    SDL_RenderCopyEx(gRenderer, pipeTexture, NULL, &upperPipeRect, 0.0, NULL, SDL_FLIP_VERTICAL);
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);
}
SDL_Rect Pipe:: strikeUpperObstacle(){
    if(which_pipe_ % 3 == 0) return emptyObstacle;
    SDL_Rect Obstacle = { x_val_, UPPER_PIPE_OFFSET, width_, height_ }; //need to check
    return Obstacle;
}
SDL_Rect Pipe:: strikeLowerObstacle() {
    if(which_pipe_ % 3 == 1) return emptyObstacle;
    SDL_Rect Obstacle = { x_val_, height_ + LOWER_PIPE_OFFSET, width_, SCREEN_HEIGHT - height_ - (LOWER_PIPE_OFFSET + LOWER_PIPE_HEIGHT_OFFSET) };//need to check
    return Obstacle;
}
Pipe::~Pipe(){
    x_val_ = 0;
    y_val_ = 0;
    height_ = 0;
    width_ = 0;
    which_pipe_ = 0;
    FreeAll();
}
#endif