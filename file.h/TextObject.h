#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "BaseObject.h"
#include "declaration.h"
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
    void SetColor(const int& type);
  void CreateGameText (TTF_Font* font, SDL_Surface* des);


    // bool CreateGameText(TTF_Font* gFont, SDL_Renderer* screen);
  bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
// void Free();

// // void setColor(Uint8 red, Uint8 green, Uint8 blue);
// // void setColor(int type);

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
  text_color_.r = 255;
  text_color_.g = 255;
  text_color_.b = 255;
}

TextObject::~TextObject(){

}

void TextObject::SetColor(const int& type)
{
  if (type == RED_TEXT)
  {
    SDL_Color color = {255, 0, 0};
    text_color_ = color;
  }
  else if (type == WHITE_TEXT)
  {
    SDL_Color color = {255, 255, 255};
    text_color_ = color;
  }
  else
  {
    SDL_Color color = {0, 0, 0};
    text_color_ = color;
  }
}
void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
  p_object_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
  Show(des);
}
bool TextObject::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen)
{
  //Render text surface
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
  if( textSurface != NULL )
  {
    //Create texture from surface pixels
    texture_ = SDL_CreateTextureFromSurface(screen, textSurface );
    if( texture_ != NULL )
    {
      //Get image dimensions
      width_ = textSurface->w;
      height_ = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
  }

  //Return success
  return texture_ != NULL;
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, width_, height_ };

  //Set clip rendering dimensions
  if( clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip );
}

#endif