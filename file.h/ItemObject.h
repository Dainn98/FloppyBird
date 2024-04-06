#ifndef ITEM_OBJECT_H
#define ITEM_OBJECT_H
// #include "BaseObject.h"

const int ITEM_WIDTH = 45;
const int ITEM_HEIGHT = 55;
class ItemObject : public BaseObject {
    public: 
        ItemObject();
        ~ItemObject();

        void set_x_val(const int& val) {x_val_ = val;}
        void set_y_val(const int& val) {y_val_ = val;}
        int get_x_val() const {return x_val_;}
        int get_y_val() const {return y_val_;}

        void HandleMove(const int& x_border, const int& y_border);
        void Reset(const int& x_border);
    private:
        int x_val_;
        int y_val_;
        std::vector<ItemObject*> p_item_list_;
};
ItemObject::ItemObject(){
    x_val_ = 0;
    y_val_ = 0;
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT*0.5;
    rect_.h = ITEM_WIDTH;
    rect_.w = ITEM_HEIGHT;
}
ItemObject::~ItemObject(){
    Free();
}
void ItemObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    // set_x_val(rect_.x);
    if(rect_.x < -SCREEN_WIDTH*0.5){
        rect_.x = SCREEN_WIDTH;
        rect_.y = SDLCommonFunc::MakeRandValue();
    }
}
void ItemObject::Reset(const int& x_border){
    rect_.x = x_border;
    rect_.y = SDLCommonFunc::MakeRandValue();
}
#endif