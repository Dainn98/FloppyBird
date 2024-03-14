#ifndef LTEXTURE_H
#define LTEXTURE_H
//https://lazyfoo.net/tutorials/SDL/index.php

class LTexture{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		void renderCustomSize(int x, int y, float mScalation);

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
LTexture::LTexture(){
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){	//Deallocate
	free();	
}

bool LTexture::loadFromFile( std::string path ){
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
		//Color key image
		 Uint32 key = SDL_MapRGB(loadedSurface->format,
                                COLOR_KEY_R,
                                COLOR_KEY_G,
                                COLOR_KEY_B);
		SDL_SetColorKey( loadedSurface, SDL_TRUE,key);
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

// #if defined(SDL_TTF_MAJOR_VERSION)
// bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
// {
// 	//Get rid of preexisting texture
// 	free();

// 	//Render text surface
// 	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
// 	if( textSurface != NULL )
// 	{
// 		//Create texture from surface pixels
//         mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
// 		if( mTexture == NULL )
// 		{
// 			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get image dimensions
// 			mWidth = textSurface->w;
// 			mHeight = textSurface->h;
// 		}

// 		//Get rid of old surface
// 		SDL_FreeSurface( textSurface );
// 	}
// 	else
// 	{
// 		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
// 	}

	
// 	//Return success
// 	return mTexture != NULL;
// }
// #endif

void LTexture::free(){
	//Free texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}
void LTexture::setBlendMode( SDL_BlendMode blending ){
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha ){
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::renderCustomSize(int x, int y, float mScalation){
    SDL_Rect renderQuad = {x, y, int(mWidth*mScalation), int(mHeight*mScalation) };

    SDL_RenderCopyEx( gRenderer, mTexture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE );
}
void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()	{return mWidth;}
int LTexture::getHeight()	{return mHeight;}

LTexture gBackgroundTexture,
		gBaseSurface,
		gBird[FLYING_ANIMATION_FRAMES_OF_BIRD],
		// gPiranhaPlant,
		// gIceberg,
		// gPipe[NUMBER_OF_PIPE],	
		gButtonControlGame[TOTAL_BUTTON_CONTROL_GAME],
		gStartGame;

#endif