#ifndef LTEXTURE_H
#define LTEXTURE_H
#include "Header.h"
//https://lazyfoo.net/tutorials/SDL/index.php
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

// bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
// {
//     //Get rid of preexisting texture
//     free();

//     //Render text surface
//     SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
//     if( textSurface == NULL )
//     {
//         printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
//     }
//     else
//     {
//         //Create texture from surface pixels
//         mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
//         if( mTexture == NULL )
//         {
//             printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
//         }
//         else
//         {
//             //Get image dimensions
//             mWidth = textSurface->w;
//             mHeight = textSurface->h;
//         }

//         //Get rid of old surface
//         SDL_FreeSurface( textSurface );
//     }
    
//     //Return success
//     return mTexture != NULL;
// }
LTexture gBackgroundTexture,
         gBaseSurface,
         gSpriteSheetTexture,
         gTextures[FLYING_ANIMATION_FRAMES_OF_BIRD];
SDL_Rect gSpriteClips[ BACKGROUND_FRAME ];

#endif