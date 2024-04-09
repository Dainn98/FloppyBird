#ifndef COLLISION_WITH_OBSTACLES_H
#define COLLISION_WITH_OBSTACLES_H
// #include "BaseObject.h"
// #include "declaration.h"
// #include "Bird.h"
#include "Pipe.h"
#include "PlantObject.h"
#include "IcicleObject.h"
#include "ThreatObject.h"
#include "ShieldObject.h"
#include "BulletObject.h"
class Collision :public BaseObject{
    public:
    bool CollisionBirdAndPlant(Pipe pipe_,PlantObject plant_,Bird bird_,ExplosionObject CollisionObject_, int num,ShieldObject shield_);
   
    bool CollisionBirdAndIcicle(Pipe pipe_,Bird bird_,IcicleObject icicle_,ExplosionObject CollisionObject_, int num, int& moveY ,ShieldObject shield_);
    
    void ExploringBird(Pipe pipe_,Bird bird_ ,ExplosionObject CollisionObject_);

    void CollisionBirdAndThreat(Pipe pipe_,ThreatObject p_threat_frame,Bird bird_,ExplosionObject CollisionObject_,ThreatObject* p_threat,int num);

    void CollisionBulletBirdandBulletThreat( BulletObject* p_bullet_bird,BulletObject* p_bullet_threat,ThreatObject* p_threat);



};

void Collision::ExploringBird(Pipe pipe_,Bird bird_ ,ExplosionObject CollisionObject_){
    for(int ex = 0; ex < 4; ex++){
        int xPos = ( bird_.strikeObstacle().x + bird_.strikeObstacle().w*0.5) - EXP_WIDTH * 0.5;
        int yPos = ( bird_.strikeObstacle().y + bird_.strikeObstacle().h*0.5) - EXP_HEIGHT * 0.5;
        CollisionObject_.set_frame(ex);
        CollisionObject_.SetRect(xPos,yPos);
        CollisionObject_.ShowEx(gRenderer);
        Mix_PlayChannel( 1, gExplosion, 0 );
        SDL_Delay(50);
        SDL_RenderPresent(gRenderer);
    }
    Mix_PlayChannel( 1, gDie, 0 );
}
bool Collision:: CollisionBirdAndPlant(Pipe pipe_,PlantObject plant_,Bird bird_,ExplosionObject CollisionObject_, int num,ShieldObject shield_){
    
    if(SDLCommonFunc::CheckCollision(plant_.ImplementPlantRect(pipe_,bird_,gRenderer,num),bird_.strikeObstacle())){
        if(!shield_.getIsShield()){
            ExploringBird(pipe_,bird_,CollisionObject_);
            return true;
        }
    }
    return false;
}
bool Collision :: CollisionBirdAndIcicle(Pipe pipe_,Bird bird_,IcicleObject icicle_,ExplosionObject CollisionObject_, int num, int& moveY, ShieldObject shield_){
    if(SDLCommonFunc::CheckCollision(icicle_.ImplementIciclceRect(pipe_,bird_,gRenderer,num,moveY),bird_.strikeObstacle())){
       if(!shield_.getIsShield()) {
        ExploringBird(pipe_,bird_,CollisionObject_);
        return true;
       }
    }
    return false;
}
void Collision:: CollisionBirdAndThreat(Pipe pipe_,ThreatObject p_threat_frame,Bird bird_,ExplosionObject CollisionObject_, ThreatObject* p_threat,int num){
    if(SDLCommonFunc::CheckCollision(p_threat_frame.ImplementThreatRect(p_threat,gRenderer,num),bird_.strikeObstacle())){
        ExploringBird(pipe_,bird_,CollisionObject_);
        // int a = 5;
    }
    
}
void Collision::CollisionBulletBirdandBulletThreat( BulletObject* p_bullet_bird,BulletObject* p_bullet_threat,ThreatObject* p_threat){
    if(SDLCommonFunc::CheckCollision(p_bullet_bird->GetRect(),p_bullet_threat->GetRect())){
        p_bullet_threat->set_is_move(true);                       
        p_bullet_threat->SetRect(p_threat->GetRect().x, p_threat->GetRect().y + p_threat->GetRect().h*0.5);  //RESET BULLET BACK TO THE PREVIOUS POSITION
        p_bullet_threat = NULL;
        p_bullet_bird = NULL;
        p_threat = NULL;
    }
}

#endif
