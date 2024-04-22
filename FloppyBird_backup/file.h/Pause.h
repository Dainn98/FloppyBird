#ifndef Pause_h
#define Pause_h
// #include "declaration.h"
// #include "BaseObject.h"
//Tham khảo Phan Tho
class Pause : public BaseObject {
public:
    
    Pause();
    ~Pause();
    bool mPresentState[TOTAL_BUTTON_CONTROL_GAME];
    
    SDL_Point mPresentPosi[TOTAL_BUTTON_CONTROL_GAME];
    
    void render();
    
    void handleEvent(SDL_Event* e);
private:
    const int BUTTON_WIDTH = 50;
    const int BUTTON_HEIGHT = 40;
    
    int BOOL_TO_CHECK = 1;
    
    const SDL_Point BUTTON_POSITION[TOTAL_BUTTON_CONTROL_GAME] = { { SCREEN_WIDTH - BUTTON_WIDTH, 16 },
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 16 },
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 61},
                                                            { SCREEN_WIDTH - BUTTON_WIDTH, 108} };
    int zooming;
};

void Pause::handleEvent(SDL_Event* e){
    if(e->type != SDL_MOUSEBUTTONDOWN && e->type != SDL_MOUSEMOTION){
        return;
    }
    
    //Get mouse pos
    int x, y;
    SDL_GetMouseState( &x, &y );
                                                                // PROCESSING 3 BUTTON     
    if( mPresentState[PAUSE] ){                 
                                                                // IN BUTTON PLAY
        if ( x >= BUTTON_POSITION[PLAY].x &&
             x <= BUTTON_POSITION[PLAY].x + BUTTON_WIDTH &
             y >= BUTTON_POSITION[PLAY].y &&
             y <= BUTTON_POSITION[PLAY].y + BUTTON_HEIGHT){
            if( e->type == SDL_MOUSEBUTTONDOWN ){
                mPresentState[PAUSE] = false;
                zooming = PAUSE;
            }
            else{
                zooming = PLAY;
            }
                                                                // IN BUTTON REPLAY
        }
        else if ( x >= BUTTON_POSITION[REPLAY].x &&
                x <=  BUTTON_POSITION[REPLAY].x + BUTTON_WIDTH &&
                y >= BUTTON_POSITION[REPLAY].y &&
                y <= BUTTON_POSITION[REPLAY].y + BUTTON_HEIGHT){
            if( e->type == SDL_MOUSEBUTTONDOWN ){
                mPresentState[REPLAY] = true;
            }
            else{
                zooming = REPLAY;
            }
        }
                                                                // IN BUTTON EXIT
        else if( x >= BUTTON_POSITION[EXIT].x &&
         x <=  BUTTON_POSITION[EXIT].x + BUTTON_WIDTH &&
          y >= BUTTON_POSITION[EXIT].y &&
           y <= BUTTON_POSITION[EXIT].y+ BUTTON_HEIGHT){
            if( e->type == SDL_MOUSEBUTTONDOWN ){
                mPresentState[EXIT] = true;
            }
            else{
                zooming = EXIT;
            }
        }
        else    zooming = NONE;
        
    }
    else{                                                       // PAUSE IS FALSE
        if ( x >= BUTTON_POSITION[PAUSE].x && x <=  BUTTON_POSITION[PAUSE].x + BUTTON_WIDTH && y >= BUTTON_POSITION[PAUSE].y && y <= BUTTON_HEIGHT){
            if( e->type == SDL_MOUSEBUTTONDOWN ){
                mPresentState[PAUSE] = true;
                zooming = PLAY;
            }
            else{
                zooming = PAUSE;
            }
        }
        else        zooming = NONE;
        
    }
}

Pause::Pause(){
    for(int i = PAUSE; i <= EXIT; i++){
        mPresentState[i] = false;
        
        mPresentPosi[i]  = { SCREEN_WIDTH - BUTTON_WIDTH, 16 };
    }
    zooming = NONE;
}

void Pause::render(){
    if( mPresentState[PAUSE] ){                                 // PAUSE IS PRESSED        
        mPresentPosi[EXIT].y   += 2*(mPresentPosi[EXIT].y < BUTTON_POSITION[EXIT].y ? BOOL_TO_CHECK : 0);
        mPresentPosi[REPLAY].y += (mPresentPosi[REPLAY].y < BUTTON_POSITION[REPLAY].y ? BOOL_TO_CHECK : 0);
        mPresentPosi[PLAY].y   += (mPresentPosi[PLAY].y < BUTTON_POSITION[PLAY].y ? BOOL_TO_CHECK : 0);
        
        if(mPresentPosi[EXIT].y == BUTTON_POSITION[EXIT].y){
            for(int i = EXIT; i >= PLAY; i--){
                if(i == zooming){
                    gButtonControlGame[i].renderCustomSize(BUTTON_POSITION[i].x - BUTTON_WIDTH/10, BUTTON_POSITION[i].y - BUTTON_HEIGHT/10, 1.2);
                }
                else{
                    gButtonControlGame[i].render(BUTTON_POSITION[i].x, BUTTON_POSITION[i].y, NULL);
                }
            }
            // FOR EXIT REPLAY PLAY
        }
        else{
            gButtonControlGame[EXIT].render(mPresentPosi[EXIT].x, mPresentPosi[EXIT].y, NULL);
            gButtonControlGame[REPLAY].render(mPresentPosi[REPLAY].x, mPresentPosi[REPLAY].y, NULL);
            gButtonControlGame[PLAY].render(mPresentPosi[PLAY].x, mPresentPosi[PLAY].y, NULL);
        }
    }
    else{
        if(mPresentPosi[EXIT].y > BUTTON_POSITION[PAUSE].y){
            mPresentPosi[EXIT].y -= 2*BOOL_TO_CHECK;
            gButtonControlGame[EXIT].render(mPresentPosi[EXIT].x, mPresentPosi[EXIT].y, NULL);
        }
        if(mPresentPosi[REPLAY].y > BUTTON_POSITION[PAUSE].y){
            mPresentPosi[REPLAY].y -= BOOL_TO_CHECK;
            gButtonControlGame[REPLAY].render(mPresentPosi[REPLAY].x, mPresentPosi[REPLAY].y, NULL);
        }
        
        if(zooming == PAUSE){
            gButtonControlGame[PAUSE].renderCustomSize(BUTTON_POSITION[PAUSE].x - BUTTON_WIDTH/10, BUTTON_POSITION[PAUSE].y - BUTTON_HEIGHT/10, 1.2);
        }
        else{
            gButtonControlGame[PAUSE].render(BUTTON_POSITION[PAUSE].x, BUTTON_POSITION[PAUSE].y, NULL);
        }
    }
    // SDL_RenderPresent(gRenderer);
}
Pause:: ~Pause(){
    //To do
}

#endif /* Pause_h */
