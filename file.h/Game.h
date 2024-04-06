#ifndef Game_h
#define Game_h
#include "Pause.h"
#include "impTimer.h"
#include "Collision_With_Obstacles.h"
#include "MoneyObject.h"
#include "ItemObject.h"
//Maybe delete
#include "BaseObject.h"
#include "declaration.h"
#include "Explosion.h"
#include "ThreatObject.h"
#include "TextObject.h"
#include "PlantObject.h"
#include "IcicleObject.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
class Game : public BaseObject{
private:    
    unsigned int bullet_type_ = 50;
    // unsigned long long money;
    // unsigned long long highestScore;
    unsigned long long  scoreCur;
    unsigned long long moneyCur;
    unsigned long long money;
    unsigned long long highestScore;
    int moveY = 0;
    int NUM_THREAT_CURRENT = 1;
    
    bool isPaused = false;
    bool isTapped = false;
    bool isRestarted = false;
    bool isPlayed = true;
    bool quit = false;
    bool isDyingBird = false;
    bool isAgain = false;
    
    int random_plant;
    int random_icicle;
    int random_threat;
    int fps_manual = 0;
    
    // int NUM_PIPE = 3;
    // Pipe* p_pipe_list = new Pipe[NUM_PIPE];

    ThreatObject* p_threat_list = new ThreatObject[NUM_THREAT];
    ThreatObject p_threat_frame;
    int NUM_MONEY = 2;
    MoneyObject* p_money_list = new MoneyObject[NUM_MONEY];
    
    BulletObject* p_bullet_threat;
    BulletObject* p_bullet_bird;
    std::vector<BulletObject*> bullet_list;
    std::vector<BulletObject*> bullet_arr;

    Bird bird;
    Pipe pipe;
    Pause OptionInGame;
    ImpTimer fps_timer;
    ExplosionObject explosion_Collision;
    ExplosionObject bullet_explosion;
    IcicleObject icicle;
    PlantObject plant;
    Collision collision;
    TextObject text_count_;  
    TextObject text_money_game_;

    BaseObject TappingFrame;
    BaseObject MoneyFrame;
        
public:
    Game();
    ~Game();

    void Play();

    void HandleInputAction(SDL_Event &e);
    void HandleWhenPause();
    void HandleWhenPlay();
    void HandleWhenGameOver();
    void HandleWhenReplay();
    void HandleWhenCollision();
    void CheckCollision();

    void ImplementThreat();
    void setBulletForThreat();

    void ImplementMoney();

    // void ImplementPipe();
    // void SetPipe();
    void setIsTapped(const bool isTapped_) {isTapped = isTapped_;}
    bool getIsTapped() const {return isTapped;}
    void setIsPaused(const bool isPaused_) {isPaused = isPaused_;}
    bool getIsPaused() const {return isPaused;}
    void setIsPlayed(const bool isPlayed_) {isPlayed = isPlayed_;}
    bool getIsPlayed() const {return isPlayed;}
    void setIsRestarted(const bool isRestarted_) {isRestarted = isRestarted_;}
    bool getIsRestarted() const {return isRestarted;}
    
    void ShowStats();

    // void showItem(const size_t val, const std::string& path);
    void BuildBackground_Base();

    void ResetStats();
    void changeFPS();

};

Game::Game(){
    //To do
}
Game::~Game(){
    // FreeBird();
}

void Game::Play(){
    int ret_menu = SDLCommonFunc::ShowMenuStart(gRenderer, gFontMENU, "Start Game", "Exit","Tutorial","Highest Score", "Sprites/startgame.png");
    if (ret_menu == 1) quit = true;
    

    SDL_Event e;
                                        //   GENERATE THE THREAT POSITION FIRST AND SET THE BULLET FOR THREAT
    setBulletForThreat();

    ResetStats();

while (!quit) {
    fps_timer.start();
    
    while (SDL_PollEvent(&e) != 0){                                                          
        if(e.type == SDL_MOUSEBUTTONDOWN)  
        if(e.button.button == SDL_BUTTON_LEFT ){
            bird.LoadBullet();
            Mix_PlayChannel(-1,gSwoosh,0);
        }
                                                                                //KEY
        if (e.type == SDL_QUIT) quit = true;
        
        
        else if (e.type == SDL_KEYDOWN){
            switch( e.key.keysym.sym ){  
                case SDLK_b:
                                                                                //SWITCH TYPE BULLET (IN DECLARATION)
                    std::swap(bullet[0],bullet[1]); 
                    Mix_PlayChannel(-1,gSwapBullet,0);
                    break;
                                                                                //BIRD SWING
                case SDLK_w: case  SDLK_UP:  case SDLK_SPACE:   
                    isTapped = true;
                    bird.jump();
                    Mix_PlayChannel(-1, gFly, 0 );
                    break;
                case SDLK_ESCAPE:
                    OptionInGame.mPresentState[PAUSE] = true;
                    // quit = true;
                    break;
                                                                                //PLAY THE MUSIC
                case SDLK_m:
                    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); 
                    else{
                        if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();           //RESUME THE MUSIC 
                        else  Mix_PauseMusic();                                 //PAUSE THE MUSIC                       
                    }
                    break;
                                                                                //STOP THE MUSIC
                case SDLK_0:    
                    Mix_HaltMusic();   
                    break;
            }
    
        }         
                                        //OPTION_CONTROL_GAME LOGIC
        OptionInGame.handleEvent( &e );
        if (OptionInGame.mPresentState[EXIT]) quit = true; 
        
    }

        if(OptionInGame.mPresentState[REPLAY]){  
            OptionInGame.mPresentState[PAUSE] = false;
            OptionInGame.mPresentState[REPLAY] = false;
            setIsRestarted(true);
            ResetStats();
        }

        SDL_SetRenderDrawColor(gRenderer,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B,0xFF);  
        SDL_RenderClear( gRenderer );
        if(OptionInGame.mPresentState[PLAY]){
            setIsPlayed(true);
            HandleWhenPlay();
        }

        if(OptionInGame.mPresentState[PAUSE]){
            OptionInGame.mPresentState[REPLAY] = false;
            OptionInGame.mPresentState[EXIT] = false;
            setIsPaused(true);
            HandleWhenPause();
            continue;
        }

        if(bird.GetIsDie()) HandleWhenGameOver();
        else HandleWhenPlay();
            
        if(Mix_PausedMusic())   Mix_ResumeMusic();
        CheckCollision();
        changeFPS();
        SDL_RenderPresent(gRenderer);
    } 
    std::ofstream outputFile("Stats/stats.txt");
    highestScore = max(highestScore,scoreCur);
    money += moneyCur;
    outputFile << highestScore << " " << money;
    cout << highestScore << " " << money << endl;
}
                                                                                                //IMPLEMENT THREAT
void Game::ImplementThreat(){
    // random_threat = getRandomNumber(NUM_THREAT_FRAME)-1;
    for(int tt = 0; tt < NUM_THREAT;tt++){ 
        ThreatObject* p_threat;
        p_threat = (p_threat_list + tt);
        if(p_threat){                       //CHECK POINTER IS NULL OR NOT               
            if(!getIsPaused()){
                random_threat = getRandomNumber(NUM_THREAT_FRAME)-1;                       
                p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            }
                                                                                                //IMPLEMENT THREAT
            collision.CollisionBirdAndThreat(pipe,p_threat_frame,bird,explosion_Collision,gRenderer,p_threat,random_threat);
                                                                                                        //LOADING BULLET FOR THREAT                            
            p_threat->MakeBullet(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT,pipe,getIsPaused(),getIsRestarted());   
            bullet_arr = p_threat->GetBulletList();

            bool Collision_Bird_BulletOfThreat = false;
            for (int am = 0; am < bullet_arr.size(); am++){
                p_bullet_threat = bullet_arr.at(am);
                if (p_bullet_threat){
                    Collision_Bird_BulletOfThreat = SDLCommonFunc::CheckCollision(p_bullet_threat->GetRect(), bird.strikeObstacle());
                    if (Collision_Bird_BulletOfThreat == true){
                    p_threat->ResetBullet(p_bullet_threat);
                    collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
                    // bird.SetIsDie(true);
                    break;
                    }
                }
            }
                                                                                            //CHECK COLLISION BIRD AND THREATS
            bool Collision_Bird_Threat = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_threat->GetRect());
            if(Collision_Bird_Threat){
                collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
                // bird.SetIsDie(true);
            }
                                                                                            //CHECK BULLET_BIRD WITH THREATS
            bullet_list = bird.get_bullet_list();
            for(int ib = 0; ib < bullet_list.size(); ib++){
                p_bullet_bird = bullet_list.at(ib);
                if(p_bullet_bird!=NULL){
                    collision.CollisionBulletBirdandBulletThreat(p_bullet_bird,p_bullet_threat,p_threat);
                    bool ret_collision = SDLCommonFunc::CheckCollision(p_bullet_bird->GetRect(),p_threat->GetRect());
                    if(ret_collision){
                        moneyCur++;
                        //=> DELETE THREATS, BULLET_BIRD => INCREASE MONEY,ITEMS,..
                         for(int ex = 0; ex < 4; ex++){
                            int xPos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - BUL_WIDTH * 0.5 ;
                            int yPos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - BUL_HEIGHT * 0.5;
                            bullet_explosion.set_frame(ex);
                            bullet_explosion.SetRect(xPos,yPos);
                            bullet_explosion.ShowBul(gRenderer);
                            Mix_PlayChannel( -1, gExplosion, 0 );
                        }
                        if(!isPaused)p_threat->Reset(SCREEN_WIDTH + tt * DISTANCE_BETWEEN_THREATS);  //RESET POSI THREAT
                        bird.RemoveBullet(ib);                                          //REMOVE BULLET BIRD
                    }                    
                }
            }
        }
    }
}
void Game::ResetStats(){
    SDL_SetRenderDrawColor(gRenderer,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B,0xFF);         //CLEAR SCREEN   
	SDL_RenderClear(gRenderer);
    Mix_PlayMusic( gMusic, -1 );
    pipe.init_pipe();
    bird.resetPositon();
    bird.SetIsDie(false);
    bullet_list.clear();
    bullet_arr.clear();
    setIsTapped(false);
                                                //TEXT  
    text_count_.SetColor(TextObject::BLACK_TEXT);
    text_money_game_.SetColor(TextObject::WHITE_TEXT);   

    std::ifstream inputFile("Stats/stats.txt");

        while(!inputFile.eof()){
            inputFile >> highestScore;
            inputFile >> money;
        }
        cout << highestScore << " " << money << endl;

    scoreCur = 0;
    moneyCur = 0;
    moveY = 0;
    // money = 0;
    //                                       //GENERATE THE THREAT POSITION 
    for(int t = 0; t < NUM_THREAT; t++){                
        ThreatObject* p_init_threat = (p_threat_list + t);
        if(p_init_threat){
            // p_init_threat->LoadImageFile(Creepy_path,gRenderer);
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_init_threat->SetRect(SCREEN_WIDTH + t*DISTANCE_BETWEEN_THREATS ,rand_y); 
            p_init_threat->set_x_val(THREAT_VELOCITY);           // SET VELOCITY_THREAT
            
            for(int idx = 0; idx < bullet_arr.size(); idx++){
                p_bullet_threat = bullet_arr.at(idx);
                if(p_bullet_threat){
                    // p_bullet->set_is_move(true);
                    p_bullet_threat->SetRect(p_init_threat->GetRect().x,p_init_threat->GetRect().y);

                }
            }

        }
    }
    for(int m = 0; m < NUM_MONEY; m++){
        MoneyObject* p_money = (p_money_list + m);
        if(p_money){
            p_money->LoadImageFile(Money_path,gRenderer);
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_money->SetRect(SCREEN_WIDTH + m*SCREEN_WIDTH*0.9,rand_y);
            p_money->set_x_val(THREAT_VELOCITY);// SET VELOCITY_MONEY
        }
    }
                                                                //INITIALIZE  EXPLOSION OBJECT
    explosion_Collision.LoadImageFile(Explosion_path, gRenderer);
    explosion_Collision.set_clip_explosion();
                                                                //INITIALIZE BULLET_EXPLOSION OBJECT
    bullet_explosion.LoadImageFile(Explosion_Bullet_path,gRenderer);
    bullet_explosion.set_clip_bullet_explosion();
                                                //INITIALIZE PIRANHA OBJECT
    plant.LoadImageFile(Plant_path,gRenderer);
    plant.set_clip_plant();
                                                //INITIALIZE ICE OBJCET
    icicle.LoadImageFile(Icicle_path,gRenderer);
    icicle.set_clip_icicle();

    p_threat_frame.LoadImageFile(Threat_path,gRenderer);
    p_threat_frame.set_clip_threat();

    setIsRestarted(false);
}
void Game::CheckCollision(){
     if( bird.strikeObstacle().y +  bird.strikeObstacle().h >= SCREEN_HEIGHT - BASE_HEIGHT ||  bird.strikeObstacle().y < - PIPE_HEIGHT) {
        // isDyingBird = true;
        // bird.SetIsDie(true);
    }     
    if(abs( bird.strikeObstacle().x - pipe.strikeUpperObstacle().x) <= 10 || 
       abs( bird.strikeObstacle().x - pipe.strikeLowerObstacle().x) <= 10 )    ++scoreCur;

    if( SDLCommonFunc::CheckCollision (pipe.strikeLowerObstacle(),bird.strikeObstacle())||
        SDLCommonFunc::CheckCollision (bird.strikeObstacle(),pipe.strikeUpperObstacle())){
        //To do GameOver
            collision.ExploringBird(pipe,bird,explosion_Collision,gRenderer);
            // isDyingBird = true;
            // bird.SetIsDie(true);
    }
    
}
void Game::HandleWhenReplay(){
    ResetStats();
    
}
void Game::HandleWhenPlay(){
                            //RENDER BACKGROUND
    BuildBackground_Base();                       
                                    //BIRD & BULLET_BIRD => UPDATE POSITION AND RENDER 
    bird.HandleBullet(gRenderer,pipe);                      
    bird.render();  
    if(getIsTapped()== false){
        TappingFrame.LoadImageFile(Intro_path,gRenderer);
        SDL_Rect TapFrame = {SCREEN_WIDTH/2,SCREEN_HEIGHT/5,250,300};
        TappingFrame.RenderImage(gRenderer,TapFrame);
        return;
    }else{
    if(++fps_manual % 2 == 0){
        random_threat = getRandomNumber(NUM_THREAT_FRAME)-1;
        random_plant = getRandomNumber(NUM_PLANT)-1;
        random_icicle = getRandomNumber(NUM_ICICLE)-1;
    }
    collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,gRenderer,random_plant);
    collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,gRenderer,random_icicle,moveY);
                    //IMPLEMENT THREAT & COLLISION
    ImplementThreat();
    ImplementMoney();
    bird.update();
    
                                    //PIPE
    pipe.update();      pipe.render();    
    // ImplementPipe();
    // pipe.update();     
                                                    //LOADING BASE
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
                            //OPTION_CONTROL_GAME
    OptionInGame.render();                      
    ShowStats();
    setIsPlayed(false);
    }
                                                //IMPLEMETN PLANT,ICECLE & CHECK COLLISION 

}
void Game::HandleWhenGameOver(){
    // //To do
    int ret_menu = SDLCommonFunc::ShowMenuGameOver(gRenderer, gFontMENU, "Restart", "Exit", "Sprites/background.jpg");
    if (ret_menu == 1) quit = true;
    
    else if (ret_menu == 0) {
        ResetStats();
    }
    SDL_RenderPresent(gRenderer);
}
void Game::HandleWhenPause(){
    BuildBackground_Base();
    ImplementThreat();
    // ImplementPipe();
    bird.render();          
    pipe.render();      
    collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,gRenderer,random_plant);
    collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,gRenderer,random_icicle,moveY);
                                                    //LOADING BASE
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
                            //OPTION_CONTROL_GAME
    if(bird.GetIsDie()){
        HandleWhenGameOver();
    }

    OptionInGame.render();                      
    ShowStats();

    SDL_RenderPresent( gRenderer );
    setIsPaused(false);

}
void Game::ShowStats(){
                                                    //SHOW MONEY
    std::string val_str_money = std::to_string(moneyCur);
    std::string count_money_str(" ");
    count_money_str += val_str_money;
    text_money_game_.SetText(count_money_str);
    text_money_game_.loadFromRenderedText(gFontText, gRenderer);
    text_money_game_.RenderText(gRenderer, SCREEN_WIDTH*0.03,25);
    MoneyFrame.LoadImageFile(Money_path,gRenderer);
    SDL_Rect rect_mn = {SCREEN_WIDTH/120,25,MONEY_SIZE/4*3,MONEY_SIZE/4*3};
    MoneyFrame.RenderImage(gRenderer,rect_mn);

                                                                //SHOW SCORE
    std::string val_str_mark = std::to_string(scoreCur);
    std::string count_str("Score: ");
    count_str += val_str_mark;
    text_count_.SetText(count_str);
    text_count_.loadFromRenderedText(gFontText, gRenderer);
    text_count_.RenderText(gRenderer, SCREEN_WIDTH*0.01, 2);
}
void Game::changeFPS(){
    int real_imp_time = fps_timer.get_ticks();          
    int time_one_frame = 1000/FRAME_PER_SECOND;         
    if (real_imp_time < time_one_frame){
        int delay_time  = time_one_frame-real_imp_time ;   
        if(delay_time >= 0) SDL_Delay(delay_time);
    }
}
void Game::BuildBackground_Base(){
    SDL_Rect* currentBackground = &gSpriteBackground[ frame /  BACKGROUND_FRAME]; 
    gBackgroundTexture.render((SCREEN_WIDTH - currentBackground->w) - picture,(SCREEN_HEIGHT - currentBackground->h), currentBackground );
    gBackgroundTexture.render((SCREEN_WIDTH*2 - currentBackground->w) - picture ,(SCREEN_HEIGHT - currentBackground->h), currentBackground );
    if(!getIsPaused()){
        if(++picture >= SCREEN_WIDTH ) picture = 0;
        if( ++frame / BACKGROUND_FRAME >= BACKGROUND_FRAME)frame = 0;
    }
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);	
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
}
void Game::setBulletForThreat(){
    for(int t = 0; t < NUM_THREAT; t++){                
        ThreatObject* p_init_threat = (p_threat_list + t);
        if(p_init_threat){
            p_init_threat->LoadImageFile(Creepy_path,gRenderer);
            // p_init_threat->LoadImageFile("Sprites/threatSprites.",gRenderer);
            // p_init_threat->set_clip_threat();
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_init_threat->SetRect(SCREEN_WIDTH + t*DISTANCE_BETWEEN_THREATS ,rand_y); 
            p_init_threat->set_x_val(THREAT_VELOCITY);           // SET VELOCITY_THREAT
            if(!getIsRestarted()){
                BulletObject* p_bullet = new BulletObject();  //INTIALIZE BULLET FOR THREAT
                p_init_threat->InitBullet(p_bullet); 
            }
        }
    }
}

void Game::ImplementMoney(){
    for(int m = 0; m < NUM_MONEY; m ++){
        MoneyObject* p_money = (p_money_list + m);
        if(p_money){
            p_money->LoadImageFile(Money_path,gRenderer);
            p_money->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            if(!getIsPaused())p_money->Render(gRenderer);
            // p_money->SetRect(SCREEN_WIDTH + m*SCREEN_WIDTH*0.7,SDLCommonFunc::MakeRandValue());
            bool ret_collision = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_money->GetRect());
            if(ret_collision){
                moneyCur++;
                p_money->Reset(SCREEN_WIDTH);
                Mix_PlayChannel(-1,gMoneyCol,0);
            }
        }

    }
}
void Game:: HandleInputAction(SDL_Event &e){
    //To do
}
#endif