#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

const int THREAT_WIDTH = 64; 
const int THREAT_BODY_WIDTH = 60;
const int THREAT_HEIGHT = 64;
const int THREAT_BODY_HEIGHT = 60;
const int NUM_THREAT_FRAME = 20,
        NUM_THREAT = 6,        
        DISTANCE_BETWEEN_THREATS = 400,
        THREAT_VELOCITY = 12,
        SPEED_BULLET_THREATS = 12,
        WIDTH_THREAT = 60,
        HEIGHT_THREAT = 60,
        THREAT_GRAVITY = 1.5,
        THREAT_FRAME_NUME = 8,
        MAX_FALL_SPEED = 10;

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
                                                                // SET BULLET OBECT FOR THREAT_OBJECT
  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}  
                                                                // BULLET LIST  
  std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}                     

  void InitBullet(BulletObject* p_bullet);
  void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,Pipe pipe,const bool isPaused, const bool isRestarted);
  void Reset(const int& xboder);
  void ResetBullet(BulletObject* p_bullet);

  void set_clip_threat();
  void set_frame_threat(const int& fr) {frame_ = fr;}
  void ShowThreat(SDL_Renderer* des);
  SDL_Rect ImplementThreatRect(ThreatObject* p_threat,SDL_Renderer* des,int idx);
  SDL_Rect GetThreatRect();

private:
  int x_val_;
  int y_val_;
  int frame_;
  SDL_Rect clip_[NUM_THREAT_FRAME];

  std::vector<BulletObject*> p_bullet_list_;
};
ThreatObject::ThreatObject(){
  rect_.x = SCREEN_WIDTH;
  rect_.y = SCREEN_HEIGHT*0.5;
  rect_.w = WIDTH_THREAT;
  rect_.h = HEIGHT_THREAT;
  x_val_ = 0;
  y_val_ = 0;
  frame_ = 0;
}
ThreatObject::~ThreatObject(){
if (p_bullet_list_.size() > 0)
  {
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        p_bullet->Free();
        p_bullet = NULL;
      }
    }
    p_bullet_list_.clear();
  }
}
void ThreatObject::set_clip_threat(){
    clip_[0].x = 0;
    clip_[0].y = 0; 
    clip_[0].w = THREAT_WIDTH;
    clip_[0].h = THREAT_HEIGHT;
    
    clip_[1].x = 64;
    clip_[1].y = 0;
    clip_[1].w = THREAT_WIDTH;
    clip_[1].h = THREAT_HEIGHT;
    
    clip_[2].x = 128;
    clip_[2].y = 0;
    clip_[2].w = THREAT_WIDTH;
    clip_[2].h = THREAT_HEIGHT;

    clip_[3].x = 192;
    clip_[3].y = 0;
    clip_[3].w = THREAT_WIDTH;
    clip_[3].h = THREAT_HEIGHT;

    clip_[4].x = 256;
    clip_[4].y = 0;
    clip_[4].w = THREAT_WIDTH;
    clip_[4].h = THREAT_HEIGHT;

    clip_[5].x = 0;
    clip_[5].y = 64;
    clip_[5].w = THREAT_WIDTH;
    clip_[5].h = THREAT_HEIGHT;
    
    clip_[6].x = 64;
    clip_[6].y = 64; 
    clip_[6].w = THREAT_WIDTH;
    clip_[6].h = THREAT_HEIGHT;
    
    clip_[7].x = 128;
    clip_[7].y = 64;
    clip_[7].w = THREAT_WIDTH;
    clip_[7].h = THREAT_HEIGHT;
    
    clip_[8].x = 192;
    clip_[8].y = 64;
    clip_[8].w = THREAT_WIDTH;
    clip_[8].h = THREAT_HEIGHT;

    clip_[9].x = 256;
    clip_[9].y = 64;
    clip_[9].w = THREAT_WIDTH;
    clip_[9].h = THREAT_HEIGHT;

    clip_[10].x = 0;
    clip_[10].y = 128;
    clip_[10].w = THREAT_WIDTH;
    clip_[10].h = THREAT_HEIGHT;

    clip_[11].x = 64;
    clip_[11].y = 128;
    clip_[11].w = THREAT_WIDTH;
    clip_[11].h = THREAT_HEIGHT;
    
    clip_[12].x = 128;
    clip_[12].y = 128; 
    clip_[12].w = THREAT_WIDTH;
    clip_[12].h = THREAT_HEIGHT;
    
    clip_[13].x = 192;
    clip_[13].y = 128;
    clip_[13].w = THREAT_WIDTH;
    clip_[13].h = THREAT_HEIGHT;
    
    clip_[14].x = 256;
    clip_[14].y = 128;
    clip_[14].w = THREAT_WIDTH;
    clip_[14].h = THREAT_HEIGHT;

    clip_[15].x = 0;
    clip_[15].y = 192;
    clip_[15].w = THREAT_WIDTH;
    clip_[15].h = THREAT_HEIGHT;

    clip_[16].x = 64;
    clip_[16].y = 192;
    clip_[16].w = THREAT_WIDTH;
    clip_[16].h = THREAT_HEIGHT;

    clip_[17].x = 128;
    clip_[17].y = 192;
    clip_[17].w = THREAT_WIDTH;
    clip_[17].h = THREAT_HEIGHT;
    
    clip_[18].x = 192;
    clip_[18].y = 192;
    clip_[18].w = THREAT_WIDTH;
    clip_[18].h = THREAT_HEIGHT;
    
    clip_[19].x = 256;
    clip_[19].y = 192;
    clip_[19].w = THREAT_WIDTH;
    clip_[19].h = THREAT_HEIGHT;
}
void ThreatObject::ShowThreat(SDL_Renderer* des){
  if (frame_ >= NUM_THREAT_FRAME) frame_ = 0;
  SDLCommonFunc :: ApplySurfaceClip(this->p_object_texture, des, &clip_[frame_], rect_.x, rect_.y);
}
SDL_Rect ThreatObject::ImplementThreatRect(ThreatObject* p_threat,SDL_Renderer* des,int idx){
  SDL_Rect rect = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, THREAT_BODY_WIDTH, THREAT_BODY_HEIGHT};
  rect.x = p_threat->GetRect().x;
  rect.y = p_threat->GetRect().y;
  // cout << rect.x << " " << rect.y << endl;
  set_frame_threat(idx);
  SetRect(rect.x,rect.y);
  ShowThreat(des);
  // Render(des);
  return rect;
}

                                                                          // MOVE THE THREAT_OBJECT TO THE LEFT
void ThreatObject::HandleMove(const int& x_bordr, const int& y_border){                                   
  rect_.x -= x_val_;                                                                            
  if (rect_.x < 0){
    rect_.x  = SCREEN_WIDTH + getRandomNumber(SCREEN_WIDTH*2);      
    rect_.y= SDLCommonFunc::MakeRandValue();  
  }
}

void ThreatObject::InitBullet(BulletObject* p_bullet){
  // Bird bird;
  if (p_bullet){
    bool ret = p_bullet->LoadImageFile(Bullet_Threat1_path,gRenderer);
    if (ret){
      p_bullet->set_is_move(true);
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
      p_bullet->set_type(BulletObject::SPHERE_BULLET);
      p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
      p_bullet->set_x_val(SPEED_BULLET_THREATS);
      // if(bird.GetIsDie() && p_bullet_list_.size() > 0) p_bullet_list_.pop_back();
      p_bullet_list_.push_back(p_bullet);
    }
  }
}

void ThreatObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,Pipe pipe,const bool isPaused, const bool isRestarted){
  for (int itmb = 0; itmb < p_bullet_list_.size(); itmb++){
    BulletObject* p_bullet = p_bullet_list_.at(itmb);
    if (p_bullet!=NULL && x_limit <= SCREEN_WIDTH*1.2){     //IF P_BULLET IS NOT EMPTY         
      if (p_bullet->get_is_move()){ //BULLET MOVE
        p_bullet->Render(des);
                                                                // TRAJECTION
        if(!isPaused)p_bullet->HandleMoveRightToLeft(itmb);
      }
      else {                   
        p_bullet->set_is_move(true);                       
        p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);  //RESET BULLET BACK TO THE PREVIOUS POSITION
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
  //  p_bullet = NULL;
}
SDL_Rect ThreatObject:: GetThreatRect(){
  SDL_Rect rect = {get_x_val(), get_y_val(), THREAT_BODY_WIDTH, THREAT_BODY_HEIGHT};
  return rect;
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
  //Todo
}
#endif