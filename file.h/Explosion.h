
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "declaration.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;
const int NUM_EXPLOSION = 4;

class ExplosionObject : public BaseObject
{
public:
  ExplosionObject();
  ~ExplosionObject();
  void set_clip();
  void set_frame(const int& fr) {frame_ = fr;}
  void ShowEx(SDL_Renderer* des);


private:
  int frame_;
  SDL_Rect clip_[NUM_EXPLOSION];
};

ExplosionObject::ExplosionObject(){
    //To do
}

ExplosionObject::~ExplosionObject(){
    //To do
}

void ExplosionObject::set_clip(){
  for(int exp = 0; exp < NUM_EXPLOSION; exp ++){
    clip_[exp].x = exp*EXP_WIDTH;
    clip_[exp].y = 0;
    clip_[exp].w = EXP_WIDTH;
    clip_[exp].h = EXP_HEIGHT;
  }
}

void ExplosionObject::ShowEx(SDL_Renderer* des){
  if (frame_ >= 4) frame_ = 0;
  SDLCommonFunc::ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}

#endif