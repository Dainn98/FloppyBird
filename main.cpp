#include "file.h/Header.h"

int main( int argc, char* argv[]){
    bool init = Initialize();
    bool load = LoadingMedia();    
    game.Play();
    game.FreeBird();
    ShutdownMedia();
    return 0;
}
/*
Check:
p_bullet_threat => 1,2GB
p_bullet_bird => 1,3GB
=> vấn dề ở hàm render() và khi over
p_threat_frame khoong delete, đã tồn tại mTexture , ở free() không return mà delete luôn
*/