#ifndef ITEM_OBJECT_H
#define ITEM_OBJECT_H
#include "BaseObject.h"

const int MONEY_SIZE = 45;
class MoneyObject : public BaseObject {
    public: 
        MoneyObject();
        ~MoneyObject();

        void set_x_val(const int& val) {x_val_ = val;}
        void set_y_val(const int& val) {y_val_ = val;}
        int get_x_val() const {return x_val_;}
        int get_y_val() const {return y_val_;}

        void HandleMove(const int& x_border, const int& y_border);
        void Reset(const int& x_border);
    private:
        int x_val_;
        int y_val_;
        std::vector<MoneyObject*> p_money_list_;
};
MoneyObject::MoneyObject(){
    x_val_ = 0;
    y_val_ = 0;
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT*0.5;
    rect_.h = MONEY_SIZE;
    rect_.w = MONEY_SIZE;
}
MoneyObject::~MoneyObject(){
    Free();
}
void MoneyObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    // set_x_val(rect_.x);
    if(rect_.x < -SCREEN_WIDTH*0.5){
        rect_.x = SCREEN_WIDTH;
        rect_.y = SDLCommonFunc::MakeRandValue();
    }
}
void MoneyObject::Reset(const int& x_border){
    rect_.x = x_border;
    rect_.y = SDLCommonFunc::MakeRandValue();
}
#endif