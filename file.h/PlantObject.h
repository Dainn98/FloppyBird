#ifndef PLANT_OBJECT_H
#define PLANT_OBJECT_H

#include "BaseObject.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"

const int NUM_PLANT = 5;
// const int PLANT_WIDTH = 133;
const int PLANT_HEIGHT = 192;
class PlantObject : public BaseObject{
    public:
        PlantObject();
        ~PlantObject();
        
        void set_clip_plant();
        void set_frame( int& fr) {frame_ = fr;}
        void ShowPlant(SDL_Renderer* des);
        void ImplementPlant(Pipe pipe, Bird bird,SDL_Renderer* des,int ppp);
        // int get_rect_clip() const return{;}
        SDL_Rect get_rect_plant(const int num)  const {return clip_[num];}
        void CollisionBirdAndPlant(Bird bird,ExplosionObject explosion_Collision, SDL_Renderer* gRenderer, int& num);


    private:
        int frame_;
        SDL_Rect clip_[NUM_PLANT];
};
PlantObject::PlantObject() {
    //To do
}
PlantObject :: ~PlantObject(){
    //To do 
}
 void PlantObject:: set_clip_plant(){
    clip_[0].x = 0;
    clip_[0].y =  110;
    clip_[0].w = 45;
    clip_[0].h = PLANT_HEIGHT - clip_[0].y;
    
    clip_[1].x = 210;
    clip_[1].y = 85;
    clip_[1].w = 45;
    clip_[1].h = PLANT_HEIGHT - clip_[1].y;
    
    clip_[2].x = 420;
    clip_[2].y = 60;
    clip_[2].w = 45;
    clip_[2].h = PLANT_HEIGHT-clip_[2].y;

    clip_[3].x = 650;
    clip_[3].y = 45;
    clip_[3].w = 45;
    clip_[3].h = PLANT_HEIGHT-clip_[3].y;

    clip_[4].x = 860;
    clip_[4].y = 0;
    clip_[4].w = 45;
    clip_[4].h = PLANT_HEIGHT;

 }
void PlantObject:: ShowPlant(SDL_Renderer* des){
    if(frame_ >= NUM_PLANT) frame_ = 0;
    SDLCommonFunc :: ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}
void PlantObject::ImplementPlant(Pipe pipe, Bird bird,SDL_Renderer* des,int ppp){
    if(pipe.get_which_pipe() % 3 == 0){
        if(pipe.get_x_val() - bird.get_x_val() <= 50){
                    ppp %=5;
                    int x_pos = (pipe.get_x_val() + PIPE_WIDTH*0.2);
                    int y_pos = pipe.get_height_pipe()+ LOWER_PIPE_OFFSET -PLANT_HEIGHT + clip_[ppp].y ;
                    set_frame(ppp);
                    SetRect(x_pos,y_pos);
                    ShowPlant(des);  
        }           
    }
    // ++ppp;
}
void PlantObject::CollisionBirdAndPlant(Bird bird,ExplosionObject explosion_Collision, SDL_Renderer* gRenderer, int& num){
    num = 4;
    if(SDLCommonFunc::CheckCollision(get_rect_plant(num),bird.strikeObstacle())){
        int a = 4;
    }
    
}
#endif