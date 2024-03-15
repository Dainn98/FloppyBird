
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "declaration.h"

class BaseObject{
public:
  BaseObject();
  ~BaseObject();
  virtual bool LoadImageFile(std::string path, SDL_Renderer* screen); //đường dẫn lấy tấm ảnh 
  void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);        // hàm render()
  
  void Free();
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;};//hàm lưu kích thước ảnh
  SDL_Rect GetRect() const {return rect_;}    //lấy ra ảnh 
  SDL_Texture* GetObject() {return p_object_texture;}  //lây ra ảnh 

  void Show(SDL_Surface* des);
  bool LoadImg(const char* file_name);
   
protected:
  SDL_Texture* p_object_texture; //lưu ảnh 
  SDL_Rect rect_; //lưu kích thước ảnh
};
BaseObject::BaseObject(){
    p_object_texture = NULL;
    rect_.x = 0;
    rect_.y = 0;
    // rect_.w = 0;
    // rect_.h = 0; 
}

BaseObject::~BaseObject()   {Free();}

bool BaseObject::LoadImageFile(std::string path, SDL_Renderer* screen){
    Free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());      //Load image at path
    if (loadedSurface != NULL){
        Uint32 key = SDL_MapRGB(loadedSurface->format,
                                COLOR_KEY_R,
                                COLOR_KEY_G,
                                COLOR_KEY_B);                               //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, key);                      //Transparent 
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);   //Create texture from surface pixels
        if (newTexture != NULL) {                                           //Create texture from surface pixels{     
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);                                     //Get rid of old loaded surface
    }
    p_object_texture = newTexture;
    return p_object_texture != NULL;
}

void BaseObject::Free(){
    if (p_object_texture != NULL){
        SDL_DestroyTexture(p_object_texture);
        p_object_texture = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/){         //Clip = NULL
    SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
    if (clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(des, p_object_texture, clip, &renderQuad);
}
#endif