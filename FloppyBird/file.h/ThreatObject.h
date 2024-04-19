#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

const int THREAT_WIDTH = 64; 
const int THREAT_BODY_WIDTH = 60;
const int THREAT_HEIGHT = 64;
const int THREAT_BODY_HEIGHT = 60;
const int NUM_THREAT_FRAME = 20;
const int NUM_THREAT = 6;  
const int DISTANCE_BETWEEN_THREATS = 400 ;
const int THREAT_VELOCITY = 12 ;
const int SPEED_BULLET_THREATS = 12 ;
const int WIDTH_THREAT = 60 ;
const int HEIGHT_THREAT = 60 ;
const int THREAT_GRAVITY = 1.5 ;
const int THREAT_FRAME_NUME = 5 ;
const int MAX_FALL_SPEED = 10;
// int frame_ = 0;
class ThreatObject : public BaseObject{
public:
  ThreatObject();
  ~ThreatObject();

  void HandleMove(int isDel); //
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
  void ShowThreat(ThreatObject* p_threat);
  SDL_Rect ImplementThreatRect(ThreatObject* p_threat,int idx);
  SDL_Rect GetThreatRect();
  void LoadImg(std::string path,SDL_Renderer* screen);

private:
  int x_val_;
  int y_val_;
  int frame_;
  int width_frame_;
  int height_frame_;
  SDL_Rect clip_[NUM_THREAT_FRAME];

  std::vector<BulletObject*> p_bullet_list_;
};
ThreatObject::ThreatObject(){
  int height_frame_ = 0;
  int width_frame_ = 0;
  int x_val_ = 0;
  int y_val_ = 0;
  int frame_ = 0;
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
  if(this->p_object_texture == NULL || frame_ >= NUM_THREAT_FRAME) return;
  else
    Free();

}
void ThreatObject::LoadImg(std::string path,SDL_Renderer* screen){
  bool ret = LoadImageFile(path,screen);
  if(ret){
    width_frame_ = rect_.w/THREAT_FRAME_NUME;
    height_frame_ = rect_.h;
  }
}
void ThreatObject::set_clip_threat(){
    if(width_frame_ > 0 && height_frame_ >0){
      for(int i = 0; i < THREAT_FRAME_NUME; i++){
        clip_[i].x = i*width_frame_;
        clip_[i].y = 0;
        clip_[i].w = width_frame_;
        clip_[i].h = height_frame_;
      }
    }
}
void ThreatObject::ShowThreat(ThreatObject* p_threat){
 
  if(p_threat != NULL){
  rect_.x = p_threat->GetRect().x;
  rect_.y = p_threat->GetRect().y;
  rect_.w = width_frame_;
  rect_.h = height_frame_;
  frame_++;
  if(frame_ >= THREAT_FRAME_NUME ||frame_ < 0) frame_ = 0;
  SDL_Rect* curentClip = &clip_[frame_];
  SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
  SDL_RenderCopyEx(gRenderer,p_threat->p_object_texture, curentClip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
  }
  
}
SDL_Rect ThreatObject::ImplementThreatRect(ThreatObject* p_threat,int idx){
  if(p_threat == NULL) return {0,0,0,0};
  else{
    SDL_Rect rect = {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, THREAT_BODY_WIDTH, THREAT_BODY_HEIGHT};
    rect.x = p_threat->GetRect().x;
    rect.y = p_threat->GetRect().y;
    set_frame_threat(idx);
    SetRect(rect.x,rect.y);
    ShowThreat(p_threat);
    return rect;
  }
}

                                                                          // MOVE THE THREAT_OBJECT TO THE LEFT
void ThreatObject::HandleMove(int isDel) {
  rect_.x -=x_val_;
  if (rect_.x < 0) {
    ++isDel;
    rect_.x = SCREEN_WIDTH + getRandomNumber(SCREEN_WIDTH*2);
    rect_.y = SDLCommonFunc::MakeRandValue();
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