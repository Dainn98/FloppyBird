#ifndef MONEY_OBJECT_H
#define MONEY_OBJECT_H
// #include "declaration.h"
// #include "BaseObject.h"
// #include "Pipe.h"

const int MONEY_SIZE = 45;
const int NUM_MONEY = 3;
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
    for(MoneyObject* ptr : p_money_list_) {
        if(ptr != NULL){
            ptr->Free();
            ptr = NULL;
        }
    }
    p_money_list_.clear();
}
void MoneyObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    // set_x_val(rect_.x);
    if(rect_.x < -SCREEN_WIDTH*0.5){
        rect_.x = SCREEN_WIDTH+ (getRandomNumber(SCREEN_WIDTH*1.5));
        rect_.y = SDLCommonFunc::MakeRandValue();
    }
}
void MoneyObject::Reset(const int& x_border){
    rect_.x = x_border;
    rect_.y = SDLCommonFunc::MakeRandValue();
}
#endif