#ifndef COLLISION_WITH_OBSTACLES_H
#define COLLISION_WITH_OBSTACLES_H
#include "BaseObject.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "PlantObject.h"
#include "IcicleObject.h"
class Collision :public BaseObject{
    public:
    void CollisionBirdAndPlant(Pipe pipe_,PlantObject plant_,Bird bird_,ExplosionObject CollisionObject_, SDL_Renderer* des, int num);
   
    void CollisionBirdAndIcicle(Pipe pipe_,Bird bird_,IcicleObject icicle_,ExplosionObject CollisionObject_,SDL_Renderer* des, int num, int& moveY );
    
    void ExploringBird(Pipe pipe_,Bird bird_ ,ExplosionObject CollisionObject_, SDL_Renderer* des);


};

void Collision::ExploringBird(Pipe pipe_,Bird bird_ ,ExplosionObject CollisionObject_, SDL_Renderer* des){
    for(int ex = 0; ex < 4; ex++){
        int xPos = ( bird_.strikeObstacle().x + bird_.strikeObstacle().w*0.5) - EXP_WIDTH * 0.5;
        int yPos = ( bird_.strikeObstacle().y + bird_.strikeObstacle().h*0.5) - EXP_HEIGHT * 0.5;
        CollisionObject_.set_frame(ex);
        CollisionObject_.SetRect(xPos,yPos);
        CollisionObject_.ShowEx(des);
        Mix_PlayChannel( -1, gExplosion, 0 );
        SDL_Delay(100);
        SDL_RenderPresent(des);
    }
    Mix_PlayChannel( -1, gDie, 0 );
}
void Collision:: CollisionBirdAndPlant(Pipe pipe_,PlantObject plant_,Bird bird_,ExplosionObject CollisionObject_, SDL_Renderer* des, int num){
    if(SDLCommonFunc::CheckCollision(plant_.ImplementPlantRect(pipe_,bird_,des,num),bird_.strikeObstacle())){
        ExploringBird(pipe_,bird_,CollisionObject_,des);
    }
}

void Collision :: CollisionBirdAndIcicle(Pipe pipe_,Bird bird_,IcicleObject icicle_,ExplosionObject CollisionObject_,SDL_Renderer* des, int num, int& moveY){
    if(SDLCommonFunc::CheckCollision(icicle_.ImplementIciclceRect(pipe_,bird_,des,num,moveY),bird_.strikeObstacle())){
        ExploringBird(pipe_,bird_,CollisionObject_,des);
    }
    
}
#endif
