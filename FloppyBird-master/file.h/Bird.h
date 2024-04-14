#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include "BulletObject.h"
#include "Explosion.h"
#include "ShieldObject.h"
                                             //BIRD
const int BIRD_WIDTH = 34,        
        BIRD_HEIGHT = 24,
        GRAVITY = 1,          
        BIRD_JUMP_VELOCITY = -15;

class Bird;
class Bird : public BaseObject {
public:
    Bird();
    ~Bird();
     
    void resetPositon();    //reset position when restart
    void FreeBullet();

    void update();
    void render();
    void jump();

    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}


    void LoadBullet();
    void set_bullet_list(std::vector<BulletObject *> bullet_list)   {p_bullet_list_ = bullet_list;}
    std::vector<BulletObject *> get_bullet_list() const {return p_bullet_list_;}
    void HandleBullet(SDL_Renderer* des,Pipe pipe);
    void HandleInputAction(SDL_Event events);

    // void DoFalling(SDL_Renderer* des);
    // bool GetFalling() const { return is_falling_; }
    // void SetFalling(bool falling) { is_falling_ = falling; }

    bool GetIsDie() const { return is_die_; }
    void SetIsDie(bool is_die) {is_die_ = is_die;}

    void RemoveBullet(const int& idx);

    void ExplosionBirdAndThreat(ExplosionObject explosion_Collision);
    void renderShield(ShieldObject shield_);
    
    SDL_Rect strikeObstacle() const;
private:
    std::vector<BulletObject *> p_bullet_list_;

    int x_val_;
    int y_val_;
    int velocity_;
    int currentFrame;
    int width_;
    int height_;

    bool is_falling_;
    bool is_die_;
};

Bird::Bird(){
                                //POSITION
    x_val_ = SCREEN_WIDTH / 4;
    y_val_ = SCREEN_HEIGHT/3;
    width_ = BIRD_WIDTH;
    height_ = BIRD_HEIGHT;

    rect_.x = x_val_;
    rect_.y = y_val_;
    rect_.w = width_;
    rect_.h = height_;
    
    velocity_ = 0;
    currentFrame = 0;
    is_die_ = false;
    is_falling_ = false;
}
Bird :: ~Bird(){
    //To do
}
void Bird ::resetPositon(){
    x_val_ = SCREEN_WIDTH / 4;
    y_val_ = SCREEN_HEIGHT/3;
    velocity_ = 0;
    currentFrame = 0;
    width_ = BIRD_WIDTH;
    height_ = BIRD_HEIGHT;
}
void Bird::jump(){velocity_ = BIRD_JUMP_VELOCITY;}

void Bird :: render(){gBird[currentFrame].render(x_val_, y_val_);}

SDL_Rect Bird :: strikeObstacle() const {
    SDL_Rect Obstacle = { x_val_, y_val_, width_, height_ };
    return Obstacle;
}

void Bird::update() {
        velocity_ += GRAVITY;
        y_val_ += velocity_;
        currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
}
void Bird:: FreeBullet(){
    for(BulletObject* p_bullet : p_bullet_list_){
        if(p_bullet != NULL){
            p_bullet->Free();
            p_bullet = NULL;
        }
    }
    p_bullet_list_.clear();
}

void Bird::LoadBullet(){
    BulletObject* p_bullet = new BulletObject();
    p_bullet->set_bullet_type(bullet[0]);
    p_bullet->LoadImgBullet(gRenderer);
    p_bullet->SetRect(this ->x_val_ + BIRD_WIDTH - 20,y_val_ + 0.5*BIRD_HEIGHT);
    p_bullet->set_x_val(30);
    p_bullet->set_is_move(true);
    p_bullet_list_.push_back(p_bullet);        
}

void Bird::HandleBullet(SDL_Renderer* des,Pipe pipe){
    for(int i = 0; i < p_bullet_list_.size();i++){
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet != NULL){
            if(p_bullet ->get_is_move() == true){
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else {
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet != NULL){
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
        if(p_bullet && (SDLCommonFunc::CheckCollision(p_bullet->GetRect(), pipe.strikeLowerObstacle()) ||//DELETE BULLET WHEN COLLIDE WITH PIPE
                        SDLCommonFunc::CheckCollision(p_bullet->GetRect(), pipe.strikeUpperObstacle()))) {
            delete p_bullet;
            p_bullet = NULL;
            p_bullet_list_.erase(p_bullet_list_.begin() + i);
            i--; // Decrement i to account for the erased element
        }
    }
}

void Bird::RemoveBullet(const int& idx){
  for (int i = 0; i < p_bullet_list_.size(); i++){
    if (idx < p_bullet_list_.size()){
      BulletObject* p_bullet = p_bullet_list_.at(idx);
    //   delete p_bullet;
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);
      if (p_bullet != NULL){
        p_bullet->Free();
        p_bullet = NULL;
      }
    }
  }
}
void Bird::HandleInputAction(SDL_Event e){
    if(e.type == SDL_MOUSEBUTTONDOWN)  
        if(e.button.button == SDL_BUTTON_LEFT ){
            LoadBullet();
            Mix_PlayChannel(-1,gSwoosh,0);
        }
       
        else if (e.type == SDL_KEYDOWN){
            switch( e.key.keysym.sym ){  
                case SDLK_b:
                                                                                //SWITCH TYPE BULLET (IN DECLARATION)
                    std::swap(bullet[0],bullet[1]); 
                    Mix_PlayChannel(-1,gSwapBullet,0);
                    break;
                                                                                //BIRD SWING
                case SDLK_w: case  SDLK_UP:  case SDLK_SPACE:   
                    jump();
                    Mix_PlayChannel( -1, gFly, 0 );
                    break;
                                                                                //PLAY THE MUSIC
                case SDLK_m:
                    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); 
                    else{
                        if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();           //RESUME THE MUSIC 
                        else  Mix_PauseMusic();                                 //PAUSE THE MUSIC                       
                    }
                    break;
                                                                                //STOP THE MUSIC
                case SDLK_0:    
                    Mix_HaltMusic();   
                    break;
            }
        }
}
void Bird::ExplosionBirdAndThreat(ExplosionObject explosion_Collision){
    for(int ex = 0; ex < 4; ex++){
        int xPos = ( strikeObstacle().x + strikeObstacle().w*0.5) - EXP_WIDTH * 0.5;
        int yPos = ( strikeObstacle().y + strikeObstacle().h*0.5) - EXP_HEIGHT * 0.5;
        explosion_Collision.set_frame(ex);
        explosion_Collision.SetRect(xPos,yPos);
        explosion_Collision.ShowEx(gRenderer);
        Mix_PlayChannel( -1, gExplosion, 0 );
        SDL_Delay(100);
        SDL_RenderPresent(gRenderer);
    }
}

void Bird::renderShield(ShieldObject shield_){
    if(shield_.getIsShield()){
        shield_.LoadImageFile(Bubble_path,gRenderer);
        shield_.SetRect(strikeObstacle().x - BIRD_WIDTH/3,strikeObstacle().y - BIRD_HEIGHT/2);
        shield_.Render(gRenderer);
    }
    else{
        shield_.Free();
    }
}

#endif