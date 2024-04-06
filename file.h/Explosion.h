
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

// #include "BaseObject.h"
// #include "declaration.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;
const int NUM_EXPLOSION = 4;

const int BUL_WIDTH = 60;
const int BUL_HEIGHT = 71;
const int NUM_BULLET_EXPLO = 6;


class ExplosionObject : public BaseObject
{
public:
  ExplosionObject();
  ~ExplosionObject();
   void set_frame(const int& fr) {frame_ = fr;}

  void set_clip_explosion();
  void ShowEx(SDL_Renderer* des);
  int get_exp_width() const {return EXP_WIDTH;}
  int get_exp_height() const {return EXP_HEIGHT;}

  void set_clip_bullet_explosion();
  void ShowBul(SDL_Renderer* des);
  int get_bul_width() const {return BUL_WIDTH;}
  int get_bul_height() const {return BUL_HEIGHT;}


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

void ExplosionObject::set_clip_explosion(){
  for(int exp = 0; exp < NUM_EXPLOSION; exp ++){
    clip_[exp].x = exp*EXP_WIDTH;
    clip_[exp].y = 0;
    clip_[exp].w = EXP_WIDTH;
    clip_[exp].h = EXP_HEIGHT;
  }
}
void ExplosionObject::set_clip_bullet_explosion(){
    for(int i = 0; i < NUM_BULLET_EXPLO;i++){
      clip_[i].x = i * BUL_WIDTH;
      clip_[i].y = 0;
      clip_[i].w = BUL_WIDTH;
      clip_[i].h = BUL_HEIGHT;
    }
}

void ExplosionObject::ShowEx(SDL_Renderer* des){
  if (frame_ >= NUM_EXPLOSION) frame_ = 0;
  SDLCommonFunc::ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}
void ExplosionObject::ShowBul(SDL_Renderer* des){
  if (frame_ >= NUM_BULLET_EXPLO) frame_ = 0;
  SDLCommonFunc::ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}

#endif