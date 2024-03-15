#include "file.h/Header.h"
int main( int argc, char* argv[]){
    init();
    loadMedia();    
    Game game;
    game.Play();
    game.DeleteAll();
    return 0;
}
bool loadMedia(){
	bool success = true;   

//BACKGROUND LOADING  
	gBackgroundTexture.loadFromFile( "Sprites/background.jpg" );
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }
                                                    //BASE LOADING
    gBaseSurface.loadFromFile( "Sprites/base.png" );
                                                    //BIRD LOADING
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        gBird[i].loadFromFile(imagePath);
    }
                                                    //MUSIC LOADING
    gFly = Mix_LoadWAV("Sound/wing.wav");
    gMusic = Mix_LoadMUS("Sound/musicBackground.wav");
    gSwoosh = Mix_LoadWAV("Sound/swoosh.wav");
    gSwapBullet = Mix_LoadWAV("Sound/swapBullet.wav");
    gExplosion = Mix_LoadWAV("Sound/explosion.wav");
    gDie = Mix_LoadWAV("Sound/die.wav");
                                                    //BUTTON CONTORL LOADING
    gButtonControlGame[PAUSE].loadFromFile("Sprites/pausebutton.png");
    gButtonControlGame[PLAY].loadFromFile("Sprites/playbutton.png");
    gButtonControlGame[REPLAY].loadFromFile("Sprites/restartbutton.png");
    gButtonControlGame[EXIT].loadFromFile("Sprites/stopbutton.png");
	return success;
}
void close() {
                                                    //FREE LTEXTURE
    for (int i = 0; i < FLYING_ANIMATION_FRAMES_OF_BIRD; ++i) gBird[i].free();// => free loaded image
    gBaseSurface.free();
    gBackgroundTexture.free();
    gButtonControlGame[0].free();
    gButtonControlGame[1].free();
    gButtonControlGame[2].free();
    gButtonControlGame[3].free();
                                                    //FREE MUSICE
    Mix_FreeChunk( gFly );  gFly = NULL;
    Mix_FreeMusic( gMusic ); gMusic = NULL;
    Mix_FreeChunk( gSwoosh ); gSwoosh = NULL;
    Mix_FreeChunk( gDie ); gDie = NULL;
    Mix_FreeChunk( gExplosion ); gExplosion = NULL;
    Mix_FreeChunk( gSwapBullet ); gSwapBullet = NULL;
    
	                                                //DESTROY TEXTURE
    SDL_DestroyTexture(pipeTexture);            
    SDL_DestroyTexture(birdTexture);
                                                    //DESTROY RENDER,WINDOW
    SDL_DestroyRenderer(gRenderer);  gRenderer = NULL;
    SDL_DestroyWindow(gWindow);      gWindow= NULL;
                                                    //DESTROY FONT
    // TTF_CloseFont(gFont);
    // gFont = NULL;
                                                    //DESTROY SURFACE
    // SDL_FreeSurface(pipeSurface);
    // pipeSurface = NULL;
    //quit SDL subsystem
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
