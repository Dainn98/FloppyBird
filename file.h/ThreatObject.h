#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H
#include"BaseObject.h"
#include "declaration.h"
#include "BulletObject.h"
#include "Pipe.h"
#include <vector>
 
class ThreatObject : public BaseObject{
public:
  ThreatObject();
  ~ThreatObject();

  void HandleMove(const int& x_bordr, const int& y_border); //
  void HandleInputAction(SDL_Event events);

  void set_x_val(const int& val) {x_val_ = val;}
  void set_y_val(const int& val) {y_val_ = val;}
  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}
  
  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}    //SET BULLET OBECT FOR THREAT_OBJECT
  std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}                     //BULLET LIST

  void InitBullet(BulletObject* p_bullet);
  void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,Pipe pipe);
  void Reset(const int& xboder);
  void ResetBullet(BulletObject* p_bullet);

private:
  int x_val_,
      y_val_;

  std::vector<BulletObject*> p_bullet_list_;
};
ThreatObject::ThreatObject(){
  rect_.x = SCREEN_WIDTH;
  rect_.y = SCREEN_HEIGHT*0.5;
  rect_.w = WIDTH_THREAT;
  rect_.h = HEIGHT_THREAT;

  x_val_ = 0;
  y_val_ = 0;
}

ThreatObject::~ThreatObject(){
  if (p_bullet_list_.size() > 0){
    for (int i = 0; i < p_bullet_list_.size(); i++){
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if (p_bullet != NULL){
        delete p_bullet;
        p_bullet = NULL;
      }
    }
    p_bullet_list_.clear();
  }
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border){
  rect_.x -= x_val_;        //Move the threat_object to the left
  if (rect_.x < 0){
    rect_.x  = SCREEN_WIDTH;      
    rect_.y= SDLCommonFunc::MakeRandValue();  
  }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
  //Todo
}
void ThreatObject::InitBullet(BulletObject* p_bullet){
  if (p_bullet){
    bool ret = p_bullet->LoadImageFile("Sprites/xbullet.png",gRenderer);
    if (ret){
      p_bullet->set_is_move(true);
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
      p_bullet->set_type(BulletObject::SPHERE_BULLET);
      p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
      p_bullet->set_x_val(SPEED_BULLET_THREATS);
      p_bullet_list_.push_back(p_bullet);
    }
  }
}

void ThreatObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,Pipe pipe){
  for (int itmb = 0; itmb < p_bullet_list_.size(); itmb++){
    BulletObject* p_bullet = p_bullet_list_.at(itmb);
    if (p_bullet!=NULL){              //  IF IT IS NOT EMPTY
      if (p_bullet->get_is_move()){ //    BULLET MOVE
        p_bullet->Render(des);
                                                // p_bullet->HandleMoveRightToLeft(); //Trajectory
        p_bullet->HandleMoveRightToLeft(itmb);
      }
      else{                   
        p_bullet->set_is_move(true);                       
        p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5); //Reset bullet back to the previous position
      }
    }
    if(p_bullet && (SDLCommonFunc::CheckCollision(p_bullet->GetRect(), pipe.strikeLowerObstacle()) || //RESET BULLET WHEN COLLIDE WITH PIPE
                    SDLCommonFunc::CheckCollision(p_bullet->GetRect(), pipe.strikeUpperObstacle()))){
        ResetBullet(p_bullet);
    }
  }
}

void ThreatObject::Reset(const int& xboder){
  rect_.x = xboder; 
  rect_.y = SDLCommonFunc::MakeRandValue();

  for (int irs = 0; irs < p_bullet_list_.size(); irs++){
    BulletObject* p_bullet = p_bullet_list_.at(irs);
    if (p_bullet) ResetBullet(p_bullet);
  }
}

void ThreatObject::ResetBullet(BulletObject* p_bullet){
   p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}
#endif