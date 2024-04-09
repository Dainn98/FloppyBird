#include "file.h/Header.h"

int main( int argc, char* argv[]){
    Initialize();
    LoadingMedia();    
    Game game;
    game.Play();
    game.FreeBird();
    ShutdownMedia();
    return 0;
}
