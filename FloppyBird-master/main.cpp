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
//Pipe mất sau khi restarr (optioningame = > play,paused)
//Pipe mất sau khi restart => lỗi ở restart xem lại 
