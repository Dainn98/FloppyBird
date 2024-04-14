#ifndef MENU_H
#define MENU_H
#include "Game.h"

class Menu : public BaseObject{
    public:
        Menu();
        ~Menu();
        void Operation();
    private:
        Game game_;
        bool HomeChoice;
        // bool PlayChoice;
        // bool TutorialChoice;
        // bool HighestChoice;
        // bool OverChoice;
};
Menu::Menu(){
    // game_.Initialize();
    // game_.LoadingMedia();
    HomeChoice = true;
    // PlayChoice = false;
    // TutorialChoice = false;
    // HighestChoice = false;
    // OverChoice = false;
}
Menu::~Menu(){
    Free();
}
void Menu::Operation(){
    game_.InitStats();
    Mix_PlayMusic(gMusic, -1);
    while(true){
        game_.ResetStats();
        if (HomeChoice){
            int ret_menu = SDLCommonFunc::ShowMenuStart(gRenderer, gFontMENU, "Start Game", "Exit","Tutorial","Highest Score", StartGame_path);
            if (ret_menu == 0){
                game_.Play();
            }
            else if (ret_menu == 1) exit(0);
            else if (ret_menu == 2){
                int ret_tutorial = SDLCommonFunc::ShowTutorialWindow(gRenderer, gFontText, "", "Got it!", Tutorial_path);
                if (ret_tutorial == 1) continue;                
            }
            else if (ret_menu == 3){
                int ret_highest = SDLCommonFunc::ShowMenuGameOver2(gRenderer, gFontMENU, "Return","Home","Exit game",std::to_string(game_.getMoney()),std::to_string(game_.getHighestScore()), Stats_path);
                if(ret_highest == 2) exit(0);
                else continue;
            }
        }
    }
    game_.FreeBird();
}
#endif