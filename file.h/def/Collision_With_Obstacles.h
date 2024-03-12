#ifndef COLLISION_WITH_OBSTACLES_H
#define COLLISION_WITH_OBSTACLES_H
#include "Header.h"
void COLLISION_WITH_OBSTACLE(){
 
}
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x <= b.x + b.w &&
            a.x + a.w >= b.x &&
            a.y <= b.y + b.h &&
            a.y + a.h >= b.y);
}
#endif
