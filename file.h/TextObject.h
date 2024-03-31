#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "BaseObject.h"
// #include "declaration.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
class TextObject : public BaseObject{
  public:
    TextObject();
    ~TextObject();
    enum TextColor{
      RED_TEXT = 0,
      WHITE_TEXT = 1,
      BLACK_TEXT = 2,
    };
   
    void SetText(const std::string& text) {str_val_ = text;}
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(const int& type);

    bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);

    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth() const {return width_;}
    int getHeight() const {return height_;}
    
  private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};
TextObject::TextObject(){
  rect_.x = 10;
  rect_.y = 10;

  text_color_.r = 0xFF;
  text_color_.g = 0xFF;
  text_color_.b = 0xFF;
}

TextObject::~TextObject(){
  //To do
}

void TextObject::SetColor(const int& type){
  if (type == RED_TEXT){
    SDL_Color color = {0xFF, 0, 0};
    text_color_ = color;
  }
  else if (type == WHITE_TEXT){
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    text_color_ = color;
  }
  else{
    SDL_Color color = {0, 0, 0};
    text_color_ = color;
  }
}

bool TextObject::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen){
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);  //RENDER TEXT_SURFACE
  if( textSurface != NULL ){
    texture_ = SDL_CreateTextureFromSurface(screen, textSurface );                        //CREATE TEXTURE FROM SURFACE PIXELS
    if( texture_ != NULL ){   
      width_ = textSurface->w;                                                            //GET IMAGE DIMENSIONS
      height_ = textSurface->h;
    }
    SDL_FreeSurface( textSurface );
  }
  return texture_ != NULL;
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */){
  SDL_Rect renderQuad = { x, y, width_, height_ };
  if( clip != NULL ){                                                                     //GET IMAGE DIMENSIONS
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip );            //RENDER SCREEN
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue){
  text_color_.r = red;
  text_color_.g = green;
  text_color_.b = blue;
}
#endif