#ifndef ICICLEOBJECT_H
#define ICICLEOBJECT_H
#include "BaseObject.h"
#include "Pipe.h"
#include "Bird.h"

const int NUM_ICICLE = 6;
const int ICICLE_WIDTH = 48;
const int ICICLE_HEIGHT = 135;
class IcicleObject : public BaseObject{
    public:
        IcicleObject();
        ~IcicleObject();

        void set_clip_icicle();
        void set_frame_icicle(int& fr) {frame_ = fr;}
        void ShowIcicle(SDL_Renderer* des);
        
        SDL_Rect ImplementIciclceRect(Pipe pipe,Bird bird,SDL_Renderer* des,int idx,int& moveY);
    private:
        SDL_Rect clip_[NUM_ICICLE];
        int frame_;
};

IcicleObject::IcicleObject(){
    //To do
    int frame_ = 0;
}
IcicleObject::~IcicleObject(){
    //To do
}
void IcicleObject::set_clip_icicle() {
    clip_[0].x = 0;
    clip_[0].y = 0; 
    clip_[0].w = ICICLE_WIDTH;
    clip_[0].h = ICICLE_HEIGHT ;
    
    clip_[1].x = 96;
    clip_[1].y = 0;
    clip_[1].w = ICICLE_WIDTH;
    clip_[1].h = ICICLE_HEIGHT ;
    
    clip_[2].x = 192;
    clip_[2].y = 0;
    clip_[2].w = ICICLE_WIDTH;
    clip_[2].h = ICICLE_HEIGHT;

    clip_[3].x = 288;
    clip_[3].y = 0;
    clip_[3].w = ICICLE_WIDTH;
    clip_[3].h = ICICLE_HEIGHT;

    clip_[4].x = 385;
    clip_[4].y = 0;
    clip_[4].w = ICICLE_WIDTH;
    clip_[4].h = ICICLE_HEIGHT;

    clip_[5].x = 481;
    clip_[5].y = 0;
    clip_[5].w = ICICLE_WIDTH;
    clip_[5].h = ICICLE_HEIGHT;
}
void IcicleObject::ShowIcicle(SDL_Renderer* des){
    if (frame_ >= NUM_ICICLE) frame_ = 0;
    SDLCommonFunc :: ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}
SDL_Rect IcicleObject:: ImplementIciclceRect(Pipe pipe,Bird bird,SDL_Renderer* des,int idx,int& moveY){
    SDL_Rect rect = {SCREEN_WIDTH,SCREEN_HEIGHT,ICICLE_WIDTH,ICICLE_HEIGHT};
    if(pipe.get_which_pipe() % 3 == 1){
        if(pipe.get_x_val() - bird.get_x_val() <= 100){
            rect.x = pipe.get_x_val() + 10;
            if(pipe.get_height_pipe() < 450){
                rect.y = pipe.get_height_pipe() + UPPER_PIPE_OFFSET;// DELETE THE SITUATION : PIPE_HEIGHT IS REACHING BASE => NOT RENDERING ICICLE 
                if(rect.y > 531) rect.y = 531;
                else rect.y += (++moveY)*ICICLE_WIDTH/1.5;
            }  
            else if(pipe.get_height_pipe() >= 510) rect.y = 0;
            if(pipe.get_x_val() <= 0) moveY = 0;
            set_frame_icicle(idx);
            SetRect(rect.x,rect.y);
            ShowIcicle(des);
        }
    }
    return rect;
}

#endif