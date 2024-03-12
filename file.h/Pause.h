#ifndef Pause_h
#define Pause_h
#include "declaration.h"
//Tham khảo SV Phan Tho
class Pause {
public:
    
    Pause();
    // mCurrentPos

    bool mPresentState[TOTAL_BUTTON_CONTROL_GAME]; //mPresentState
    
    SDL_Point mPresentPosi[TOTAL_BUTTON_CONTROL_GAME];
    
    void render();

    void handleEvent(SDL_Event* e);
private:
    const int BUTTON_WIDTH = 50;
    const int BUTTON_HEIGHT = 40;    

    int DENTA_Y = 1;

    const SDL_Point BUTTON_POSITION[TOTAL_BUTTON_CONTROL_GAME] = { { SCREEN_WIDTH - BUTTON_WIDTH, 16 },
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 16 },
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 56},
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 110} };
};

void Pause::handleEvent(SDL_Event* e){
    if(e->type == SDL_MOUSEBUTTONDOWN){
        //Get mouse pos
        int PosiX, PosiY;
        SDL_GetMouseState( &PosiX, &PosiY );
        //Working with 3 button
        if( mPresentState[PAUSE] ){                 
            if ( PosiX >= BUTTON_POSITION[PLAY].x &&
                 PosiY >= BUTTON_POSITION[PLAY].y &&
                 PosiX <=  BUTTON_POSITION[PLAY].x + BUTTON_WIDTH &&
                 PosiY <= BUTTON_POSITION[PLAY].y + BUTTON_HEIGHT )              mPresentState[PAUSE] = false; //Choose continue play
            
            else if ( PosiX >= BUTTON_POSITION[REPLAY].x && 
                      PosiY >= BUTTON_POSITION[REPLAY].y && 
                    PosiX <=  BUTTON_POSITION[REPLAY].x + BUTTON_WIDTH &&
                    PosiY <= BUTTON_POSITION[REPLAY].y + BUTTON_HEIGHT )         mPresentState[REPLAY] = true;  //choose to restart
            
            else if( PosiX >= BUTTON_POSITION[EXIT].x &&
                     PosiY >= BUTTON_POSITION[EXIT].y &&
                     PosiX <=  BUTTON_POSITION[EXIT].x + BUTTON_WIDTH &&
                     PosiY <= BUTTON_POSITION[EXIT].y+ BUTTON_HEIGHT)            mPresentState[EXIT] = true;   //Choose to quit
        }else mPresentState[PAUSE] = ( PosiX >= BUTTON_POSITION[PAUSE].x && PosiX <=  BUTTON_POSITION[PAUSE].x + BUTTON_WIDTH && PosiY >= BUTTON_POSITION[PAUSE].y && PosiY <= BUTTON_HEIGHT);
        
    }
}
Pause::Pause(){
    for(int i = PAUSE; i <= EXIT; i++){
        mPresentState[i] = false;

        mPresentPosi[i]  = { SCREEN_WIDTH - BUTTON_WIDTH, 16 };
    }
}

void Pause::render(){
    if( mPresentState[PAUSE] ){
        gButtonControlGame[EXIT].render(mPresentPosi[EXIT].x, mPresentPosi[EXIT].y, NULL);
        gButtonControlGame[REPLAY].render(mPresentPosi[REPLAY].x, mPresentPosi[REPLAY].y, NULL);
        gButtonControlGame[PLAY].render(mPresentPosi[PLAY].x, mPresentPosi[PLAY].y, NULL);
        
        mPresentPosi[EXIT].y   += 2*(mPresentPosi[EXIT].y < BUTTON_POSITION[EXIT].y ? DENTA_Y : 0);
        mPresentPosi[REPLAY].y += (mPresentPosi[REPLAY].y < BUTTON_POSITION[REPLAY].y ? DENTA_Y : 0);
        mPresentPosi[PLAY].y   += (mPresentPosi[PLAY].y < BUTTON_POSITION[PLAY].y ? DENTA_Y : 0);
    }
    else{
        if(mPresentPosi[EXIT].y > BUTTON_POSITION[PAUSE].y){
            mPresentPosi[EXIT].y -= 2*DENTA_Y;
            gButtonControlGame[EXIT].render(mPresentPosi[EXIT].x, mPresentPosi[EXIT].y, NULL);
        }
        if(mPresentPosi[REPLAY].y > BUTTON_POSITION[PAUSE].y){
            mPresentPosi[REPLAY].y -= DENTA_Y;
            gButtonControlGame[REPLAY].render(mPresentPosi[REPLAY].x, mPresentPosi[REPLAY].y, NULL);
        }
        
        gButtonControlGame[PAUSE].render(BUTTON_POSITION[PAUSE].x , BUTTON_POSITION[PAUSE].y, NULL);
    }
}

#endif /* Pause_h */
