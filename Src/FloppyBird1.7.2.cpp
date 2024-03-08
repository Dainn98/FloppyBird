#include "file.h/Header.h"
int main(int argc, char* args[]) {
    if (!init()) {
        cout << "Failed to initialize." << endl;
        return -1;
    }
    loadMedia();
    bool quit = false;
    SDL_Event e;
    Bird bird;
    Pipe pipe(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - BASE_HEIGHT*2)); // 1 random
    while (!quit) {
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)  quit = true;
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_w) bird.jump();
            }
        }
        SDL_Rect birdStrikeObstacle = bird.strikeObstacle();
        SDL_Rect birdStrikeUpperObstacle = pipe.strikeUpperObstacle();
        SDL_Rect birdStrikeLowerObstacle = pipe.strikeLowerObstacle();
        
        if( checkCollision(birdStrikeLowerObstacle, birdStrikeObstacle)||
            checkCollision(birdStrikeObstacle, birdStrikeUpperObstacle)||
            birdStrikeObstacle.y + birdStrikeObstacle.h >= SCREEN_HEIGHT - BASE_HEIGHT || birdStrikeObstacle.y < -10){
            /*mã game: sau khi va chạm 
            => reset
            =>revive*/
            quit = true;
        }
        // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //=> clear sreen
        // SDL_RenderClear(gRenderer);
        // //loading background
        // SDL_Rect* currentClip = &gSpriteClips[ frame /  BACKGROUND_FRAME];
        // gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) - picture,(SCREEN_HEIGHT - currentClip->h), currentClip );
		// gSpriteSheetTexture.render((SCREEN_WIDTH*2 - currentClip->w) - picture ,(SCREEN_HEIGHT - currentClip->h), currentClip );
        // //loading base
        // gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
        // gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
        BuildScreen();
        bird.update();      bird.render();
        pipe.update();      pipe.render();
        SDL_RenderPresent(gRenderer);
       
        SDL_RenderClear(gRenderer);
        SDL_Delay(DELAY);
    }
    close();
    return 0;
}








// void BuildScreen(){
//     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //=> clear sreen
//     SDL_RenderClear(gRenderer);
//     //loading background
//     SDL_Rect* currentClip = &gSpriteClips[ frame /  BACKGROUND_FRAME];
//     gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) - picture,(SCREEN_HEIGHT - currentClip->h), currentClip );
//     gSpriteSheetTexture.render((SCREEN_WIDTH*2 - currentClip->w) - picture ,(SCREEN_HEIGHT - currentClip->h), currentClip );
//     //loading base
//     gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
//     gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
// }
// bool loadMedia(){
// 	bool success = true;     
// 	if( !gSpriteSheetTexture.loadFromFile( "Sprites/background.jpg" ) ){
// 		printf( "Failed to load background texture image!\n" );
// 		success = false; 
// 	}else{
//         for(int i = 0; i < BACKGROUND_FRAME;i++){
//             gSpriteClips[i].x = 0;
//             gSpriteClips[i].y = 0;
//             gSpriteClips[i].w = BACKGROUND_WIDTH;
//             gSpriteClips[i].h = BACKGROUND_HEIGHT;
//         }
//     }
//     if(!gBaseSurface.loadFromFile( "Sprites/base.png" )){  
// 		printf( "Failed to load base image!\n" );
// 		success = false;
// 	}
//     for(int i = 0; i <FLYING_ANIMATION_FRAMES_OF_BIRD;i++){     //=> continuous bird
//         string imagePath = "Sprites/bluebird" + to_string(i + 1) + ".png"; 
//         if (!gTextures[i].loadFromFile(imagePath))  success = false;
//     }
// 	return success;
// }
// class Bird {
// public:
//     int x, y, velocity, currentFrame,width,height;
//     Bird() {
//         x = SCREEN_WIDTH / 4;
//         y = SCREEN_HEIGHT / 2;
//         velocity = 0;
//         currentFrame = 0;
//         width = BIRD_WIDTH;
//         height = BIRD_HEIGHT;
//     }
//     void jump() {
//         velocity = BIRD_JUMP_VELOCITY;
//     }
//     void update() {
//         velocity += GRAVITY;
//         y += velocity;
//         currentFrame = (currentFrame + 1) % FLYING_ANIMATION_FRAMES_OF_BIRD;
//     }
//     void render() {
//         gTextures[currentFrame].render(x, y);
//     }
//     SDL_Rect strikeObstacle() const {
//         SDL_Rect Obstacle = { x, y, width, height };
//         return Obstacle;
//     }
// };
// void close() {
//     for (int i = 0; i < 4; ++i) gTextures[i].free(); // => free loaded image
//     SDL_DestroyTexture(birdTexture);
//     gBackgroundTexture.free();
//     gSpriteSheetTexture.free();
//     gBaseSurface.free();
//    //destroy window,texture,render
//     SDL_DestroyTexture(pipeTexture);
//     SDL_DestroyRenderer(gRenderer);
//     SDL_DestroyWindow(gWindow);
//     gRenderer = NULL;
//     gWindow= NULL;
//     //quit SDL subsystem
//     IMG_Quit();
//     SDL_Quit();
// }