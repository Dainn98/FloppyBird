#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H
#include "BaseObject.h"

class BulletObject;

#define WIDTH_LASER 35
#define HEIGHT_LASER 5
#define WIDTH_SPHERE 25
#define HEIGHT_SPHERE 10

 
class BulletObject : public BaseObject{

public:
    BulletObject();
    ~BulletObject();
    
    enum BulletType{
        SPHERE_BULLET = 50,
        LASER_BULLET = 51,
        DYNAMIC_BULLET = 52,
    };
    void freeBulletObject();
    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}
    void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;};
    
    int get_type() const {return bullet_type_;}
    void set_type(const int& type) {bullet_type_ = type;}
    unsigned int get_bullet_type() const {return bullet_type_;}
    void set_bullet_type(const unsigned int& bulletType) {bullet_type_ = bulletType;}

    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const { return is_move_; }
   
    void HandleMove(const int& x_border, const int& y_border);   
    void HandleMoveRightToLeft(const int& trajectory_bullet ); 
    double Trajectory_Sin(double time, double amplitude, double frequency, double phaseShift, double verticalShift) {return amplitude * sin(2 * PI * frequency * time + phaseShift) + verticalShift;}

    void HandleInputAction(SDL_Event events);

    void LoadImgBullet(SDL_Renderer* des);
private:
    int x_val_,
        y_val_;
    double amplitude = 10.0;     // Biên độ
    double frequency = 100.0;     // Tần số
    double phaseShift = 0.0;    // Dịch chuyển ngang
    double verticalShift = 0.0; // Dịch chuyển dọc
    double time = 0.5;
    double degree = 30.0;
    const double PI = 3.14159265;
    bool is_move_;
    unsigned int bullet_type_;
};
BulletObject:: BulletObject(){
    x_val_ = 0;
    y_val_  = 0;
    is_move_ =false;
    bullet_type_ = SPHERE_BULLET;
}

BulletObject:: ~BulletObject(){
    //
}
void BulletObject::freeBulletObject(){
   
}


void BulletObject::LoadImgBullet(SDL_Renderer* des){
    if(bullet_type_ == SPHERE_BULLET){
        LoadImageFile(Sphere_Bullet_path,des);
    }else if (bullet_type_ == LASER_BULLET){
    LoadImageFile(Laser_Bullet_path,des);    
    }else{
        LoadImageFile(Other_Type_Bullet_path,des);
    }
}
void BulletObject::HandleMove(const int& x_border, const int& y_border){    //BULLET FOR MAIN BIRD
    rect_.x += x_val_ * 2;
    if(rect_.x > x_border){
        is_move_ = false;
    }
}
void BulletObject::HandleMoveRightToLeft(const int& trajectory_bullet) {
    rect_.x -= x_val_ * 3; // VELOCITY_BULLET
    if (rect_.x < 0)
        is_move_ = false;
    if (trajectory_bullet == 1)  rect_.y -= Trajectory_Sin(time, amplitude, frequency, phaseShift, verticalShift);
    else if (trajectory_bullet  == 2)   rect_.y -= Trajectory_Sin(time, amplitude, frequency, degree, verticalShift);
    else if (trajectory_bullet == 3)   rect_.y -= Trajectory_Sin(time, amplitude, frequency, phaseShift, degree);
    else rect_.y +=0;   //trajectory_bullet: 0
}

void BulletObject::HandleInputAction(SDL_Event events)
{
  ;//Todo
}
#endif