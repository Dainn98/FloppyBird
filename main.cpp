#include "file.h/Header.h"
int main( int argc, char* argv[] ){
    // srand(time(0));
    init();
    loadMedia();
    
    Game game;
    game.Play();
    
    close();

    return 0;
}
bool loadMedia(){
	bool success = true;     

	gBackgroundTexture.loadFromFile( "Sprites/background.jpg" );
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }

    gBaseSurface.loadFromFile( "Sprites/base.png" );
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        gTextures[i].loadFromFile(imagePath);
    }

    gFly = Mix_LoadWAV("Sound/wing.wav");
    gMusic = Mix_LoadMUS("Sound/music.wav");

    gButtonControlGame[PAUSE].loadFromFile("Sprites/iconpause.png");
    gButtonControlGame[PLAY].loadFromFile("Sprites/iconplay.png");
    gButtonControlGame[REPLAY].loadFromFile("Sprites/iconreplay.jpg");
    gButtonControlGame[EXIT].loadFromFile("Sprites/iconquit.png");
	return success;
}
void close() {
    for (int i = 0; i < 4; ++i) gTextures[i].free(); // => free loaded image
    SDL_DestroyTexture(birdTexture);
 
    gBaseSurface.free();
    gBackgroundTexture.free();

    Mix_FreeChunk( gFly );  gFly = NULL;
    Mix_FreeMusic( gMusic ); gMusic = NULL;
	

    SDL_DestroyTexture(pipeTexture);            //destroy window,texture,render
    SDL_DestroyRenderer(gRenderer);  gRenderer = NULL;
    SDL_DestroyWindow(gWindow);      gWindow= NULL;

    gButtonControlGame[0].free();
    gButtonControlGame[1].free();
    gButtonControlGame[2].free();
    gButtonControlGame[3].free();

    //quit SDL subsystem
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
