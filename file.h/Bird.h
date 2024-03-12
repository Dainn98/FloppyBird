#ifndef BIRD_H
#define BIRD_H
#include "declaration.h"
// #include "defLTexture.h"
class Bird {
public:
    int x, y, velocity, currentFrame,width,height;
    // Bird();
    Bird(){
        x = SCREEN_WIDTH / 4;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
        currentFrame = 0;
        width = BIRD_WIDTH;
        height = BIRD_HEIGHT;
    }
    void init(){
        x = SCREEN_WIDTH / 4;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
        currentFrame = 0;
        width = BIRD_WIDTH;
        height = BIRD_HEIGHT;
    }
    void jump() {
        velocity = BIRD_JUMP_VELOCITY;
    }
    void update() {
        velocity += GRAVITY;
        y += velocity;
        currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
    }
    void render() {
        gTextures[currentFrame].render(x, y);
    }
    SDL_Rect strikeObstacle() const {
        SDL_Rect Obstacle = { x, y, width, height };
        return Obstacle;
    }
};

#endif
