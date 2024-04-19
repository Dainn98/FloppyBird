
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "declaration.h"

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
class BaseObject{
public:
  BaseObject();
  ~BaseObject();
  virtual bool LoadImageFile(std::string path, SDL_Renderer* screen); //LOADING IMAGE FROM FILE 
  void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);        // RENDER CLIP,IMAGE
  void RenderImage(SDL_Renderer* des,SDL_Rect ret /*=NULL*/);
  
  void Free();
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}; //FUNCTION SET DIMESION FOR IMAGE
  SDL_Rect GetRect() const {return rect_;}    //GET DIMESION OF IMAGE
  SDL_Texture* GetObjectTexture() {return p_object_texture;}  //GET IMAGE

  bool LoadImg(const char* file_name);
   
protected:

  SDL_Texture* p_object_texture; // IMAGE (TEXTURE)
  SDL_Rect rect_; // DIMESION OF IMAGE

};
BaseObject::BaseObject(){
    p_object_texture = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()   {
    // Free();
}

bool BaseObject::LoadImageFile(std::string path, SDL_Renderer* screen){
    Free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());      //LOAD IMAGE AT PATH
    if(loadedSurface == NULL){
        std::cout << "Unable to load image " << path.c_str() << " SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else{
        Uint32 key = SDL_MapRGB(loadedSurface->format,
                                COLOR_KEY_R,
                                COLOR_KEY_G,
                                COLOR_KEY_B);                               //COLOR KEY IMAGE
        SDL_SetColorKey(loadedSurface, SDL_TRUE, key);                      //SET COLOR KEY INTO TRANSPARENT COLOR
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);   //CREATE TEXTURE FROM SURFACE PIXELS
        if (newTexture != NULL) {                                              
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);                                     //GET RID OF  OLDLOADED SURFACE
    }
    p_object_texture = newTexture;
    return p_object_texture != NULL;
}

void BaseObject::Free(){
    if (p_object_texture != NULL && (uintptr_t)p_object_texture != 0x12c00000047) {
        SDL_DestroyTexture(p_object_texture);
        p_object_texture = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
    // if (p_object_texture != NULL) {
    //     SDL_DestroyTexture(p_object_texture);
    //     p_object_texture = NULL;
    //     rect_.w = 0;
    //     rect_.h = 0;
    // }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/){         //Clip = NULL
    SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
    if (clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(des, p_object_texture, clip, &renderQuad);
}
void BaseObject :: RenderImage(SDL_Renderer* des,SDL_Rect ret /*=NULL*/){
    SDL_Rect* clip = NULL;
    SDL_Rect renderQuad = { ret.x, ret.y, ret.w, ret.h };
    SDL_RenderCopy(des, p_object_texture, clip, &renderQuad);
}

#endif