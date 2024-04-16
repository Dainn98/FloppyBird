#include "file.h/Header.h"

int main( int argc, char* argv[]){
    Initialize();
    LoadingMedia();
    Menu menu;
    menu.Operation();    
    // Game game;
    // game.Play();
    // game.FreeBird();
    ShutdownMedia();
    return 0;
}
//ThreatObject() => xong
//StartGame() => xong không tăng ram
//Tutorial() => xong không tăng ram
//Highestwd => không tăng ram nhưng mỗi lần nhấp vào là lại tăng 1 lần, xong không giảm


// Set clip Background=> chưa
//Pipe mất sau khi restarr (optioningame = > play,paused) => chưa
//Pipe mất sau khi restart => lỗi ở restart xem lại => chưa
/*Play() =>
    Background() => khonoong tăng ram
    renderObject()
    bird => không tăng ram
    tappingFrame => tăng 10 ram
    text_guide_ => không tăng ram
RenderObject() 
    
    Money() => không tăng ram
    Pipe() => ram tăng không ngừng:)) <cột xong, còn vật bất ngờ)
    shield() => không tăng ram,xong
    check colliwsion shield => ok
  
    gBaseSurface => ok
    optioningame =>ok
    ShowStats() => ok
    threat()=> không tăng ram
    check collision => ok
    check collision icicle  => ok
    check collision pwlant => ok

@ từ play thoát về home ram tăng
@ mỗi chọn vào một nút ở home ram tăng
@ màn hình statics thỉnh thoảng mất đí score
    */

    

