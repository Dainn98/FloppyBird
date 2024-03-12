#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
using namespace std;
// #include "file.h/initialize.h"
// #include "file.h/loadMedia.h"
// #include "file.h/LTexture.h"
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = nullptr;
SDL_Texture* pipeTexture = nullptr;
class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile( string path );
		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( int x, int y, SDL_Rect* clip = NULL );
		int getWidth();
		int getHeight();
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor ); //chua
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
LTexture::~LTexture()	{free();}

bool LTexture::loadFromFile( string path ){
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	else{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )	printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
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
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )	{SDL_SetTextureColorMod( mTexture, red, green, blue );}
void LTexture::setBlendMode( SDL_BlendMode blending )	{SDL_SetTextureBlendMode( mTexture, blending );}	
void LTexture::setAlpha( Uint8 alpha )	{SDL_SetTextureAlphaMod( mTexture, alpha );}
void LTexture::render( int x, int y, SDL_Rect* clip ){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
int LTexture::getWidth()	{return mWidth;}

int LTexture::getHeight()	{return mHeight;}




// LTexture gPiranhaPlant,
//         gIceberg;
// LTexture gPipe[NUMBER_OF_PIPE];
bool init();
bool loadMedia();
static SDL_Event* g_event;


SDL_Surface* pipeSurface = NULL;
SDL_Rect emptyObstacle = {0, 0, 0, 0};
//SCREEN
const int SCREEN_WIDTH = 1280,
        SCREEN_HEIGHT = 800,
        BACKGROUND_WIDTH = 1280,
        BACKGROUND_HEIGHT = 800,
        BASE_WIDTH = 1182,
        BASE_HEIGHT = 134,
        BASE_QUARTER_WIDTH = BASE_WIDTH / 4,
        UPPER_PIPE_OFFSET = -40,
        LOWER_PIPE_OFFSET = 150,
        NUMBER_OF_PIPE = 1000,
        LOWER_PIPE_HEIGHT_OFFSET = 134,
        BACKGROUND_FRAME = 8,
        SIZE_OF_FONT = 28,
        
//Bird
        BIRD_WIDTH = 40,
        BIRD_HEIGHT = 30,
//Pipe
        PIPE_WIDTH = 100,
        PIPE_HEIGHT = 300,
        FLYING_ANIMATION_FRAMES_OF_BIRD = 3, 
//Feature 
        
        GRAVITY = 1,
        BIRD_JUMP_VELOCITY = -15,
        PIPE_VELOCITY = 15,
        COLOR_KEY_R = 167,
        COLOR_KEY_G = 175,
        COLOR_KEY_B = 180;
const int NUMBER_OF_PIRANHA_PLANT = 5;
SDL_Rect gSpriteBackground[ BACKGROUND_FRAME ];
LTexture gBackgroundTexture,
         gBaseSurface,
        //  gSpriteSheetTexture,
         gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }   
    gWindow = SDL_CreateWindow("Floppy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    
    // SDL_Surface* pipeSurface = IMG_Load("Sprites/pipeGreen.png");
    // pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    // SDL_FreeSurface(pipeSurface);
    return true;
}
bool loadMedia(){
	bool success = true;     
	if( !gBackgroundTexture.loadFromFile( "Sprites/background.jpg" ) ){
		printf( "Failed to load background texture image!\n" );
		success = false; 
	}else{
        for(int i = 0; i < BACKGROUND_FRAME;i++){
            gSpriteBackground[i].x = 0;
            gSpriteBackground[i].y = 0;
            gSpriteBackground[i].w = BACKGROUND_WIDTH;
            gSpriteBackground[i].h = BACKGROUND_HEIGHT;
        }
    }
    if(!gBaseSurface.loadFromFile( "Sprites/base.png" )){  
		printf( "Failed to load base image!\n" );
		success = false;
	}
    for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
        string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
        if (!gTextures[i].loadFromFile(imagePath))  success = false;
    }
    
	return success;
}
class Pipe;

std::list<Pipe*> pipeLists;

class Pipe {
    private:
    LTexture mTexture;
    int mPosX, mPosY;
    int mHeight;
    int mWidth;

    public:
    Pipe();
    ~Pipe();
    Pipe(int posX, int posY);
    void initializePipe();
    void update();
    void renderPipe();
    void deletePipe();
    bool isRender();
    bool isOffScreen();
    void loadIMG();

    int getPosX() const;
    int getPosY() const;
    int getHeight() const;
    int getWidth();
};

int  getRandNum(int randMin, int randMax) {
    return (rand() % (randMax - randMin) + randMin);
}

void Pipe::initializePipe() {
    mTexture.loadFromFile("Sprites/pipeGreen.png");
}

Pipe::Pipe() {
    mPosX = 0;
    mPosY = 0;
    mHeight = 0;
    mWidth = 0;
}

Pipe::~Pipe() {
    mTexture.free();
}

Pipe::Pipe(int posX, int height) {
    mPosX = posX;
    mHeight = height;
    mWidth = PIPE_WIDTH;
}

void generatePipe() {
    Pipe *pipe = new Pipe(SCREEN_WIDTH, getRandNum(BASE_HEIGHT * 2, SCREEN_HEIGHT));
    pipeLists.push_back(pipe);

    for (auto iter = pipeLists.begin(); iter != pipeLists.end();) {
        if ((*iter)->isOffScreen()) {
            delete *iter;
            iter = pipeLists.erase(iter);
        } else {
            iter++;
        }
    }
}

bool Pipe::isRender() {
    mPosX -= PIPE_VELOCITY;

    if (isOffScreen()) {
        return false;
    }

    SDL_Rect rect_pipe;
    rect_pipe.x = 0;
    rect_pipe.y = 0;
    rect_pipe.h = mHeight;
    rect_pipe.w = mTexture.getWidth();

    mTexture.render(mPosX, mPosY, &rect_pipe);

    return true;
}

int Pipe::getPosX() const {
    return mPosX;
}

int Pipe::getPosY() const {
    return mPosY;
}

int Pipe::getHeight() const {
    return mHeight;
}

int Pipe::getWidth() {
    return mTexture.getWidth();
}

void Pipe::deletePipe() {
    // clear pipes
    for (auto pipe : pipeLists) {
        delete pipe;
    }
    pipeLists.clear();
}
int main(int argc, char* args[]) {
    init();
    loadMedia();
    // Tạo các ống nước
    for (int i = 0; i < NUMBER_OF_PIPE; i++) {
        generatePipe();
    }
    Pipe pipe;
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        for (auto iter = pipeLists.begin(); iter != pipeLists.end();) {
            if ((*iter)->isRender()) {
                (*iter)->renderPipe();
                iter++;
            } else {
                delete *iter;
                iter = pipeLists.erase(iter);
            }
        }

        SDL_RenderPresent(gRenderer);
    }

    // ... (Giải phóng bộ nhớ và đóng SDL)

    return 0;
}

