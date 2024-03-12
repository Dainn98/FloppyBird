#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H
#include "BaseObject.h"
class BulletObject;
 
class BulletObject : public BaseObject{

public:
    BulletObject();
    ~BulletObject();
    
    void set_x_val(const int& xVal) { x_val_ = xVal;}
    void  set_y_val(const int& yVal) { y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}


    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const { return is_move_; }

    void HandleMove(const int& x_border, const int& y_border);    
private:
    int x_val_,
        y_val_;
    bool is_move_;
};
BulletObject:: BulletObject(){
    x_val_ = 0;
    y_val_  =0;
    is_move_ =false;
}

 BulletObject:: ~BulletObject(){

}

void BulletObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x += x_val_;
    if(rect_.x > x_border){
        is_move_ = false;
    }
}


#endif