#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 634;
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
const int PIPE_WIDTH = 100;
const int PIPE_HEIGHT = 300;
const int GRAVITY = 1;
const int BIRD_JUMP_VELOCITY = -15;
const int PIPE_VELOCITY = 40;

SDL_Window* window = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;
SDL_Renderer* gRenderer = NULL;
////https://lazyfoo.net/tutorials/SDL/index.php
class LTexture{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile( std::string path );
		void free();
		void render( int x, int y );
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};
LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()   {   free(); }

bool LTexture::loadFromFile( std::string path )
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	else{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free(){
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render( int x, int y ){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}
int LTexture::getWidth()    {   return mWidth;  }
int LTexture::getHeight()   {   return mHeight; }
LTexture gBackgroundTexture;
LTexture gStretchedSurface;
bool loadMedia(){
	bool success = true;    
	if( !gBackgroundTexture.loadFromFile( "Sprites/background.jpg" ) ){
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if(!gStretchedSurface.loadFromFile( "Sprites/base.png" )){
		printf( "Failed to load base image!\n" );
		success = false;
	}
	return success;
}

class Bird {
public:
    int x, y, velocity;

    Bird() {
        x = SCREEN_WIDTH / 4;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
    }

    void jump() {
        velocity = BIRD_JUMP_VELOCITY;
    }

    void update() {
        velocity += GRAVITY;
        y += velocity;
    }

    void render() {
        SDL_Rect birdRect = { x, y, BIRD_WIDTH, BIRD_HEIGHT };
        SDL_RenderCopy(gRenderer, birdTexture, NULL, &birdRect);
    }
};

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
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &upperPipeRect);
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    }
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_Surface* birdSurface = IMG_Load("sprites/redbird1.png");
    birdTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    SDL_Surface* pipeSurface = IMG_Load("sprites/pipeRed.png");
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    return true;
}

void close() {
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyRenderer(gRenderer);
    gBackgroundTexture.free();
    gStretchedSurface.free();
    gRenderer = NULL;
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);
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
