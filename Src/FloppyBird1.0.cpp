
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
const int PIPE_WIDTH = 100;
const int PIPE_HEIGHT = 300;
const int GRAVITY = 1;
const int BIRD_JUMP_VELOCITY = -15;

SDL_Window* gWindow = NULL; 
SDL_Renderer* gRenderer = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;

class Bird {
public:
    int x, y, velocity;
    Bird() {
        x = SCREEN_WIDTH / 2;
        y = SCREEN_HEIGHT / 2;
        velocity = 0;
    }

    void jump() {
        velocity = BIRD_JUMP_VELOCITY;
    }

    void update() {
        velocity += GRAVITY;
        y += velocity;
    }

    void render() {
        SDL_Rect birdRect = { x, y, BIRD_WIDTH, BIRD_HEIGHT };
        SDL_RenderCopy(gRenderer, birdTexture, NULL, &birdRect);
    }
};

class Pipe {
public:
    int x, height;

    Pipe(int startX, int pipeHeight) {
        x = startX;
        height = pipeHeight;
    }

    void update() {
        x -= 5;
        if (x + PIPE_WIDTH < 0) {
            x = SCREEN_WIDTH;
            height = rand() % (SCREEN_HEIGHT - 200) + 100;
        }
    }

    void render() {
        SDL_Rect upperPipeRect = { x, 0, PIPE_WIDTH, height };
        SDL_Rect lowerPipeRect = { x, height + 150, PIPE_WIDTH, SCREEN_HEIGHT - height - 150 };
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &upperPipeRect);
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
    }
};

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Floppy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_Surface* birdSurface = IMG_Load("Sprites/redbird1.png");
    birdTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    SDL_Surface* pipeSurface = IMG_Load("Sprites/pipeRed.png");
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    return true;
}

void close() {
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cout << "Failed to initialize." << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    Bird bird;
    Pipe pipe(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 200) + 100);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    bird.jump();
                }
            }
        }

        bird.update();
        pipe.update();

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        bird.render();
        pipe.render();

        SDL_RenderPresent(gRenderer);
        SDL_Delay(15);
    }

    close();

    return 0;
}
