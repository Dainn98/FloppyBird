#ifndef SHIELD_OBJECT_H
#define SHIELD_OBJECT_H
// #include "Bird.h"
// #include "BaseObject.h"

const int SHIELD_WIDTH = 45;
const int SHIELD_HEIGHT = 55;
const int SHIELD_VELOCITY = 10;
const int NUM_SHIELD = 10;
int TIME_SHIELD = 150;
const int SHIELD_SHIELD_ORDER = 1;
// const int DISTANCE_BETWEEN_SHIELDS = SCREEN_WIDTH;
class ShieldObject : public BaseObject {
    public: 
        ShieldObject();
        ~ShieldObject();

        void InitShield();

        void set_x_val(const int& val) {x_val_ = val;}
        void set_y_val(const int& val) {y_val_ = val;}
        int get_x_val() const {return x_val_;}
        int get_y_val() const {return y_val_;}

        void setIsShield(const bool& isShield) {is_shield_ = isShield;}
        bool getIsShield() const {return is_shield_;}
        

        void HandleMove(const int& x_border, const int& y_border);
        void Reset();
    private:
        
        bool is_shield_;
        int x_val_;
        int y_val_;
};
ShieldObject::ShieldObject(){
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT*0.5;
    rect_.w = SHIELD_WIDTH;
    rect_.h = SHIELD_HEIGHT;
    x_val_ = SHIELD_VELOCITY;
    y_val_ = 0;
}
ShieldObject::~ShieldObject(){
    // FreeAll();
    int x_val_ = 0;
    int y_val_ = 0;
    bool is_shield_ = false;
    
}
void ShieldObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < -SCREEN_WIDTH*0.5){
        InitShield();
    }
}
void ShieldObject::Reset(){
    rect_.x = getRandomNumber(5*SCREEN_WIDTH) + 3*SCREEN_WIDTH;
    // rect_.x = SCREEN_WIDTH;
    rect_.y = SDLCommonFunc::MakeRandValue();
}
void ShieldObject::InitShield(){
    rect_.x = getRandomNumber(5*SCREEN_WIDTH) + 3*SCREEN_WIDTH;
    // rect_.x = SCREEN_WIDTH;
    rect_.y = SDLCommonFunc::MakeRandValue();
}

#endif