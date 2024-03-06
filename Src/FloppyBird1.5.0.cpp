
//Hoàn thiện hình ảnh và logic5
#include "file.h/CommonFunc.h"
#include "file.h/CommonTexture.h"
LTexture gBackgroundTexture,
         gBaseSurface,
         gSpriteSheetTexture,
         gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
const int BACKGROUND_FRAME = 8;
SDL_Rect gSpriteClips[ BACKGROUND_FRAME ];
/*#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include <windows.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

static SDL_Event* g_event;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;
//SCREEN
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int BASE_WIDTH = 1182;
const int BASE_HEIGHT = 134;
const int BASE_QUARTER_WIDTH = BASE_WIDTH / 4;
const int UPPER_PIPE_OFFSET = -25;
const int LOWER_PIPE_OFFSET = 150;
const int LOWER_PIPE_HEIGHT_OFFSET = 134;

//Bird
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
//Pipe
const int PIPE_WIDTH = 100;
const int PIPE_HEIGHT = 300;
const int FLYING_ANIMATION_FRAMES_OF_BIRD = 3; 
//Feature 
const int SPEED = 20;
const int GRAVITY = 1;
const int JUMP_VELOCITY = -15;
const int PIPE_VELOCITY = 15;
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


// LTexture gBackgroundTexture;
// LTexture gStretchedSurface;
// LTexture gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
// static SDL_Window* g_window = NULL;
// static SDL_Renderer* g_renderer = NULL;
// #include <SDL_mixer.h>
#endif
*/
/*#include "CommonFunc.h"
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}*/
bool loadMedia()
{
	bool success = true;     
	if( !gSpriteSheetTexture.loadFromFile( "Sprites/background1.jpg" ) ){
		printf( "Failed to load background texture image!\n" );
		success = false; 
	}else{
        gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 0 ].h = BACKGROUND_HEIGHT;

		gSpriteClips[ 1 ].x =  0;
		gSpriteClips[ 1 ].y =  0;
		gSpriteClips[ 1 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 1 ].h = BACKGROUND_HEIGHT;
		
		gSpriteClips[ 2 ].x = 	0;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 2 ].h = BACKGROUND_HEIGHT;

		gSpriteClips[ 3 ].x = 	0;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 3 ].h = BACKGROUND_HEIGHT;
		gSpriteClips[ 4 ].x =   0;
		gSpriteClips[ 4 ].y =   0;
		gSpriteClips[ 4 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 4 ].h = BACKGROUND_HEIGHT;

		gSpriteClips[ 5 ].x =  0;
		gSpriteClips[ 5 ].y =  0;
		gSpriteClips[ 5 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 5 ].h = BACKGROUND_HEIGHT;
		
		gSpriteClips[ 6 ].x = 	0;
		gSpriteClips[ 6 ].y =   0;
		gSpriteClips[ 6 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 6 ].h = BACKGROUND_HEIGHT;

		gSpriteClips[ 7 ].x = 	0;
		gSpriteClips[ 7 ].y =   0;
		gSpriteClips[ 7 ].w =  BACKGROUND_WIDTH;
		gSpriteClips[ 7 ].h = BACKGROUND_HEIGHT;

    }
    if(!gBaseSurface.loadFromFile( "Sprites/basePlus.png" )){  
		printf( "Failed to load base image!\n" );
		success = false;
	}
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        if (!gTextures[i].loadFromFile(imagePath))  success = false;
    }
	return success;
}

class Bird {
public:
    int x, y, velocity, currentFrame;
    Bird() {
        x = SCREEN_WIDTH / 4;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
        currentFrame = 0;
    }
    void jump() {
        velocity = JUMP_VELOCITY;
    }
    void update() {
        velocity += GRAVITY;
        y += velocity;
        currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
    }
    void render() {
        gTextures[currentFrame].render(x, y);
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
            height = rand() % (SCREEN_HEIGHT - PIPE_HEIGHT);
        }
    }
    void render() {
        SDL_Rect upperPipeRect = { x, UPPER_PIPE_OFFSET, PIPE_WIDTH, height };
        SDL_Rect lowerPipeRect = { x, height + LOWER_PIPE_OFFSET, PIPE_WIDTH, SCREEN_HEIGHT - height - (LOWER_PIPE_OFFSET+LOWER_PIPE_HEIGHT_OFFSET)};
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &upperPipeRect);
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    }
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    gWindow = SDL_CreateWindow("Flying Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Surface* pipeSurface = IMG_Load("Sprites/pipe-green.png");
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);
    return true;
}

void close() {
    for (int i = 0; i < 4; ++i) gTextures[i].free(); // => free loaded image
    SDL_DestroyTexture(birdTexture);
    gBackgroundTexture.free();
    gSpriteSheetTexture.free();
    gBaseSurface.free();
   //destroy window,texture,render
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow= NULL;
    //quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        cout << "Failed to initialize." << endl;
        return -1;
    }
    loadMedia();
    bool quit = false;
    SDL_Event e;
    int frame = 0,
        backgroundX = 0,
        picture = 0;
    Bird bird;
    Pipe pipe(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - BASE_HEIGHT) + BASE_HEIGHT);
    while (!quit) {
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) bird.jump();
            }
        }
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //=> clear sreen
        SDL_RenderClear(gRenderer);
        //loading background
        // gBackgroundTexture.render( 0, 0 );
        SDL_Rect* currentClip = &gSpriteClips[ frame /  BACKGROUND_FRAME];
        gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) - picture,(SCREEN_HEIGHT - currentClip->h), currentClip );
		gSpriteSheetTexture.render((SCREEN_WIDTH*2 - currentClip->w) - picture ,(SCREEN_HEIGHT - currentClip->h), currentClip );
        //loading base
        gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
        gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT );
        bird.update();      bird.render();
        pipe.update();      pipe.render();
        SDL_RenderPresent(gRenderer);
        if(++picture >= SCREEN_WIDTH ) picture = 0;
		if( ++frame / BACKGROUND_FRAME >= BACKGROUND_FRAME)frame = 0;
        SDL_RenderClear(gRenderer);
        SDL_Delay(DELAY);
    }
    close();
    return 0;
}
