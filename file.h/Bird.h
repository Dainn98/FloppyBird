#ifndef BIRD_H
#define BIRD_H
// #include "F:\Lap trinh cung C++\FLoppyBird\file.h\Object\SDL\include\SDL2"
#include "F:\\Lap trinh cung C++\\FLoppyBird\\file.h\\Object\\SDL\\include\\SDL2\\SDL.h"
#include "declaration.h"
#include "BulletObject.h"
#include <vector>
// #include "defLTexture.h"
class Bird;
class Bird : public BaseObject {
public:
    Bird();
    ~Bird();
     

    void resetPositon();    //reset position when restart
    void Free(); //thieu

    void update();
    void render();
    void jump();

    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void  set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void LoadBullet();
    // std::vector<BulletObject *> p_bullet_list_;
    void set_bullet_list(std::vector<BulletObject *> bullet_list){
        p_bullet_list_ = bullet_list;    
    }
    std::vector<BulletObject *> get_bullet_list() const {return p_bullet_list_;}
    SDL_Rect strikeObstacle() const;
    void HandleBullet(SDL_Renderer* des);
private:
    std::vector<BulletObject *> p_bullet_list_;
    int x_val_,
        y_val_,
        velocity_,
        currentFrame,
        width_,
        height_;
};
Bird::Bird(){
    x_val_ = SCREEN_WIDTH / 4;
    y_val_ = SCREEN_HEIGHT / 2;
    velocity_ = 0;
    currentFrame = 0;
    width_ = BIRD_WIDTH;
    height_ = BIRD_HEIGHT;
}
Bird :: ~Bird(){
    Free();
}
void Bird ::resetPositon(){
     x_val_ = SCREEN_WIDTH / 4;
    y_val_ = SCREEN_HEIGHT / 2;
    velocity_ = 0;
    currentFrame = 0;
    width_ = BIRD_WIDTH;
    height_ = BIRD_HEIGHT;
}
void Bird::jump(){
    velocity_ = BIRD_JUMP_VELOCITY;
}
void Bird :: render(){
    gBird[currentFrame].render(x_val_, y_val_);
}
SDL_Rect Bird :: strikeObstacle() const {
        SDL_Rect Obstacle = { x_val_, y_val_, width_, height_ };
        return Obstacle;
    }
void Bird::update() {
        velocity_ += GRAVITY;
        y_val_ += velocity_;
        currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
}
void Bird:: Free(){
    //thieu
}

void Bird::LoadBullet(){
        BulletObject* p_bullet = new BulletObject();
        p_bullet->LoadImageFile("Sprites/xbullet.png",gRenderer);
        p_bullet->SetRect(this ->x_val_ + BIRD_WIDTH - 20,y_val_ + 0.5*BIRD_HEIGHT);
        p_bullet->set_x_val(20);
        p_bullet->set_is_move(true);
        p_bullet_list_.push_back(p_bullet);        
}
void Bird::HandleBullet(SDL_Renderer* des){
    for(int i = 0; i < p_bullet_list_.size();i++){
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet != NULL){
            if(p_bullet ->get_is_move() == true){
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else{
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet != NULL){
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}
#endif
















































// int x, y, velocity, currentFrame,width,height;
//     // Bird();
//     Bird(){
//         x = SCREEN_WIDTH / 4;
//         y = SCREEN_HEIGHT / 2;
//         velocity = 0;
//         currentFrame = 0;
//         width = BIRD_WIDTH;
//         height = BIRD_HEIGHT;
//     }
//     void resetPositon(){
//         x = SCREEN_WIDTH / 4;
//         y = SCREEN_HEIGHT / 2;
//         velocity = 0;
//         currentFrame = 0;
//         width = BIRD_WIDTH;
//         height = BIRD_HEIGHT;
//     }
//     void jump() {
//         velocity = BIRD_JUMP_VELOCITY;
//     }
//     void update() {
//         velocity += GRAVITY;
//         y += velocity;
//         currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
//     }
//     void render() {
//         gBird[currentFrame].render(x, y);
//     }
//     SDL_Rect strikeObstacle() const {
//         SDL_Rect Obstacle = { x, y, width, height };
//         return Obstacle;
//     }

