
#include "file.h/CommonFunc.h"
#include "file.h/CommonTexture.h"
#include "file.h/GeneratingBird.h"
LTexture gBackgroundTexture;
LTexture gStretchedSurface;
LTexture gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
bool loadMedia()
{
	bool success = true;    
	if( !gBackgroundTexture.loadFromFile( "Sprites/background.jpg" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if(!gStretchedSurface.loadFromFile( "Sprites/base.png" )){
		printf( "Failed to load base image!\n" );
		success = false;
	}
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png";
        if (!gTextures[i].loadFromFile(imagePath))  success = false;
    }
	return success;
}

class Pipe {
public:
    int x, height;

    Pipe(int startX, int pipeHeight) {
        x = startX;
        height = pipeHeight;
    }

    void update() { 
        x -= PIPE_VELOCITY;
        if (x + PIPE_WIDTH < 0) {
            x = SCREEN_WIDTH;
            height = rand() % (SCREEN_HEIGHT - 200) ;
        }
    }

    void render() {
        SDL_Rect upperPipeRect = { x, -25, PIPE_WIDTH, height };
        SDL_Rect lowerPipeRect = { x, height + 150, PIPE_WIDTH, SCREEN_HEIGHT - height - 150 -134};
        SDL_RenderCopy(gRenderer, pipeTexture, nullptr, &upperPipeRect);
        SDL_RenderCopy(gRenderer, pipeTexture, nullptr, &lowerPipeRect);
    }
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_Surface* birdSurface = IMG_Load("sprites/redbird-midflap.png");
    birdTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    SDL_Surface* pipeSurface = IMG_Load("sprites/pipe-red.png");
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    return true;
}

void close() {
    for (int i = 0; i < 4; ++i) gTextures[i].free();
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyRenderer(gRenderer);
    gBackgroundTexture.free();
    gStretchedSurface.free();
    gRenderer = NULL;
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


int main(int argc, char* args[]) {
    if (!init()) {
        std::cout << "Failed to initialize." << std::endl;
        return -1;
    }
    loadMedia();
    bool quit = false;
    SDL_Event e;

    Bird bird;
    Pipe pipe(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 200) + 100);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    bird.jump();
                }
            }
        }

        bird.update();
        pipe.update();

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.render( 0, 0 );
        gStretchedSurface.render(0,504);

        bird.render();
        pipe.render();
        SDL_RenderPresent(gRenderer);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(16);
    }

    close();

    return 0;
}
