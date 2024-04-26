#include "file.h/Header.h"

int main( int argc, char* argv[]){
    Initialize();
    LoadingMedia();
    Menu menu;
    menu.Operation();    
    ShutdownMedia();
    return 0;
}
