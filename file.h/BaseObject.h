
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "declaration.h"
#include  "BulletObject.h"

class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  virtual bool LoadImageFile(std::string path, SDL_Renderer* screen); //đường dẫn lấy tấm ảnh 
  void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);        // hàm render()
  
  void Free();
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;};//hàm lưu kích thước ảnh
  SDL_Rect GetRect() const {return rect_;}    //lấy ra ảnh 
  SDL_Texture* GetObject() {return p_object_;}  //lây ra ảnh 
   
protected:
//  std::vector<BulletObject *> p_bullet_list_;
  SDL_Texture* p_object_; //lưu ảnh 
  SDL_Rect rect_; //lưu kích thước ảnh
};

#include "BaseObject.h"


BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImageFile(std::string path, SDL_Renderer* screen)
{
    //The final texture
    Free();
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface != NULL)
    {
        //Color key image
        Uint32 key = SDL_MapRGB(loadedSurface->format,
                                COLOR_KEY_R,
                                COLOR_KEY_G,
                                COLOR_KEY_B);
        SDL_SetColorKey(loadedSurface, SDL_TRUE, key);      //Transparent 

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);  
        if (newTexture != NULL)
        {
            //Get image dimensions
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    p_object_ = newTexture;
    return p_object_ != NULL;
}

void BaseObject::Free()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
    SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}


#endif