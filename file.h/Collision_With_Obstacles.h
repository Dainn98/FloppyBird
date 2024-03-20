#ifndef COLLISION_WITH_OBSTACLES_H
#define COLLISION_WITH_OBSTACLES_H
#include "BaseObject.h"
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "PlantObject.h"
class Collision :public BaseObject{
    public:
    void CollisionBirdAndPlant(Pipe pipe,PlantObject plant,Bird bird,ExplosionObject CollisionObject, SDL_Renderer* gRenderer, int num);
    void ExplosionBirdAndObject(Pipe pipe,Bird bird ,ExplosionObject CollisionObject, SDL_Renderer* gRenderer);

};

void Collision:: CollisionBirdAndPlant(Pipe pipe,PlantObject plant,Bird bird,ExplosionObject CollisionObject, SDL_Renderer* gRenderer, int num){
    if(SDLCommonFunc::CheckCollision(plant.ImplementPlantRect(pipe,bird,gRenderer,num),bird.strikeObstacle())){
        // int a = 5;
        ExplosionBirdAndObject(pipe,bird,CollisionObject,gRenderer);
    }
}
void Collision::ExplosionBirdAndObject(Pipe pipe,Bird bird ,ExplosionObject CollisionObject, SDL_Renderer* gRenderer){
    for(int ex = 0; ex < 4; ex++){
        int xPos = ( bird.strikeObstacle().x + bird.strikeObstacle().w*0.5) - EXP_WIDTH * 0.5;
        int yPos = ( bird.strikeObstacle().y + bird.strikeObstacle().h*0.5) - EXP_HEIGHT * 0.5;
        CollisionObject.set_frame(ex);
        CollisionObject.SetRect(xPos,yPos);
        CollisionObject.ShowEx(gRenderer);
        Mix_PlayChannel( -1, gExplosion, 0 );
        SDL_Delay(100);
        SDL_RenderPresent(gRenderer);
    }
    Mix_PlayChannel( -1, gDie, 0 );
}

#endif
