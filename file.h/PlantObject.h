#ifndef PLANT_OBJECT_H
#define PLANT_OBJECT_H

#include "BaseObject.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"

const int NUM_PLANT = 5;
const int PLANT_WIDTH = 45;
const int PLANT_HEIGHT = 192;
class PlantObject : public BaseObject{
    public:
        PlantObject();
        ~PlantObject();
        
        void set_clip_plant();
        void set_frame_plant( int& fr) {frame_ = fr;}

        void ShowPlant(SDL_Renderer* des);
        SDL_Rect ImplementPlantRect(Pipe pipe, Bird bird,SDL_Renderer* des,int index);
    private:
        int frame_;
        int x_val_;
        int y_val_;
        SDL_Rect clip_[NUM_PLANT];
};
PlantObject::PlantObject() {
    //To do
    frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
}
PlantObject :: ~PlantObject(){
    //To do 
}
 void PlantObject:: set_clip_plant(){
    clip_[0].x = 0;
    clip_[0].y =  110;
    clip_[0].w = PLANT_WIDTH;
    clip_[0].h = PLANT_HEIGHT - clip_[0].y;
    
    clip_[1].x = 210;
    clip_[1].y = 85;
    clip_[1].w = PLANT_WIDTH;
    clip_[1].h = PLANT_HEIGHT - clip_[1].y;
    
    clip_[2].x = 420;
    clip_[2].y = 60;
    clip_[2].w = PLANT_WIDTH;
    clip_[2].h = PLANT_HEIGHT-clip_[2].y;

    clip_[3].x = 650;
    clip_[3].y = PLANT_WIDTH;
    clip_[3].w = PLANT_WIDTH;
    clip_[3].h = PLANT_HEIGHT-clip_[3].y;

    clip_[4].x = 860;
    clip_[4].y = 0;
    clip_[4].w = PLANT_WIDTH;
    clip_[4].h = PLANT_HEIGHT;

 }
void PlantObject:: ShowPlant(SDL_Renderer* des){
    if(frame_ >= NUM_PLANT) frame_ = 0;
    SDLCommonFunc :: ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}

SDL_Rect PlantObject::ImplementPlantRect(Pipe pipe, Bird bird,SDL_Renderer* des,int index){
    SDL_Rect rect = {SCREEN_WIDTH,SCREEN_HEIGHT,PLANT_WIDTH,PLANT_HEIGHT};
    if(pipe.get_which_pipe() % 3 == 0){
        if(pipe.get_x_val() - bird.get_x_val() <= 50){
            index %=NUM_PLANT;
            rect.x = (pipe.get_x_val() + PIPE_WIDTH*0.2);
            rect.y = pipe.get_height_pipe()+ LOWER_PIPE_OFFSET -PLANT_HEIGHT + clip_[index].y ;
            set_frame_plant(index);     
            SetRect(rect.x,rect.y);
            ShowPlant(des);  
        }           
    }
    return rect;
}

#endif