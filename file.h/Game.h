#ifndef Game_h
#define Game_h
#include "Pause.h"
#include "impTimer.h"
#include "Collision_With_Obstacles.h"
#include "MoneyObject.h"
#include "ShieldObject.h"
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
BaseObject GameOverMenu;
class Game : public BaseObject{
private:    
    unsigned int bullet_type_ = 50;
    unsigned long long scoreCur = 0;
    unsigned long long moneyCur = 0;
    unsigned long long money = 0;
    unsigned long long highestScore = 0;
    int moveY = 0;

    bool isPaused = false;
    bool isTapped = false;
    bool isRestarted = false;
    bool isPlayed = true;
    bool quit = false;
    bool isDyingBird = false;
    bool isAgain = false;

    bool checkBirdAndPlant = false;
    bool checkBirdAndIcicle = false;

    int ret_menu = 0;
    int ret_menu_over = 0;
    int ret_menu_tutorial = 0;
    int ret_menu_pause = 0;
    int ret_highestScore_window = 0;
    
    int random_plant = 0;
    int random_icicle = 0;
    int random_threat = 0;
    int time_shield = 0;
    int fps_manual = 0;

    BulletObject* p_bullet_threat = NULL;
    BulletObject* p_bullet_bird = NULL;
    std::vector<BulletObject*> bullet_list;
    std::vector<BulletObject*> bullet_arr;

    Bird bird;
    Pipe pipe;
    Pause OptionInGame;
    ImpTimer fps_timer;
    ExplosionObject explosion_Collision;
    ExplosionObject bullet_explosion;
    ThreatObject p_threat_frame;
    ShieldObject shield;
    IcicleObject icicle;
    PlantObject plant;
    TextObject text_count_;  
    TextObject text_money_game_;
    TextObject text_item_game_;
    TextObject text_guide_;

    Collision collision;

    BaseObject TappingFrame;
    BaseObject GameOverMenu;
    BaseObject Tutorial;
    BaseObject Statswd;
        
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

    std::vector<ThreatObject*> MakeThreatList();
    std::vector<ThreatObject*> threats_list;
    void ImplementThreat();

    std::vector<MoneyObject*> MakeMoneyList();
    std::vector<MoneyObject*> money_list;
    void ImplementMoney();

    void ImplementShield();

    void setIsTapped(const bool isTapped_) {isTapped = isTapped_;}
    bool getIsTapped() const {return isTapped;}
    void setIsPaused(const bool isPaused_) {isPaused = isPaused_;}
    bool getIsPaused() const {return isPaused;}
    void setIsPlayed(const bool isPlayed_) {isPlayed = isPlayed_;}
    bool getIsPlayed() const {return isPlayed;}
    void setIsRestarted(const bool isRestarted_) {isRestarted = isRestarted_;}
    bool getIsRestarted() const {return isRestarted;}

    void showHighestScoreWindow();
    void showTutorialWindow();

    int getHighestScore() const {return highestScore;}
    int getMoney() const {return money;}

    void InitStats();
    void ShowStats();
    void ResetStats();
    void changeFPS();
    void BuildBackground_Base();
    void RenderGame();

    void FreeBird();
    void FreeObjectPointer();
    
    void FreeThreat();
    void FreeMoney();
    void FreeBulletList();
    void FreeBulletArr();

};

Game::Game(){
    //To do
}
Game::~Game(){

    unsigned int bullet_type_ = 50;
    unsigned long long scoreCur = 0;
    unsigned long long moneyCur = 0;
    unsigned long long money = 0;
    unsigned long long highestScore = 0;
    int moveY = 0;

    bool isPaused = false;
    bool isTapped = false;
    bool isRestarted = false;
    bool isPlayed = true;
    bool quit = false;
    bool isDyingBird = false;
    bool isAgain = false;

    bool checkBirdAndPlant = false;
    bool checkBirdAndIcicle = false;

    int ret_menu = 0;
    int ret_menu_over = 0;
    int ret_menu_tutorial = 0;
    int ret_menu_pause = 0;
    int ret_highestScore_window = 0;
    
    int random_plant = 0;
    int random_icicle = 0;
    int random_threat = 0;
    int time_shield = 0;
    int fps_manual = 0;

    FreeBird();

}

void Game::Play(){
    InitStats();
    Mix_PlayMusic( gMusic, -1 );
    again_label:
    ResetStats();
    ret_menu = SDLCommonFunc::ShowMenuStart(gRenderer, gFontMENU, "Start Game", "Exit","Tutorial","Highest Score", StartGame_path);
    if (ret_menu == 1) {
        FreeBird();        
        quit = true;
        return;
    }
    if (ret_menu == 3){
        ret_highestScore_window = SDLCommonFunc::ShowMenuGameOver2(gRenderer,
                                                    gFontMENU,
                                                    "Got it!",
                                                    "HOME",
                                                    "Exit game",
                                                    std::to_string(money),
                                                    std::to_string(highestScore),
                                                    Statswd);
        if (ret_highestScore_window == 0 || ret_highestScore_window == 1) goto again_label;
        else {
            FreeBird();
            quit = true;
            return;
        }
    }
    else if (ret_menu == 2) {
        ret_menu_tutorial = SDLCommonFunc::ShowTutorialWindow(gRenderer,
                                                    gFontText,
                                                    "",
                                                    "Got it!",
                                                    Tutorial);
        if(ret_menu_tutorial == 1) goto again_label;
    }
    SDL_Event e;

while (!quit) {
    fps_timer.start();
    
    while (SDL_PollEvent(&e) != 0){                                                          
        if(e.type == SDL_MOUSEBUTTONDOWN)
        if(e.button.button == SDL_BUTTON_LEFT ){
            bird.LoadBullet();
            Mix_PlayChannel(-1,gSwoosh,0);
        }
                                                                                //KEY
        if (e.type == SDL_QUIT) {
            FreeBird();
            quit = true;
            return;
        }
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
                    break;
                                                                                //PLAY THE MUSIC
                case SDLK_o:
                    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 ); 
                    else{
                        if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();           //RESUME THE MUSIC 
                        else  Mix_PauseMusic();                                 //PAUSE THE MUSIC                       
                    }
                    break;
                                                                                //STOP THE MUSIC
                case SDLK_m:    
                    Mix_HaltMusic();   
                    break;
            }
    
        }         
                                        //OPTION_CONTROL_GAME LOGIC
        OptionInGame.handleEvent( &e );
        if (OptionInGame.mPresentState[EXIT]) {
            // FreeBullet();
            FreeBird();
            quit = true;
            return;}
        
    }
        

        if(OptionInGame.mPresentState[REPLAY]){  
            OptionInGame.mPresentState[PAUSE] = false;
            OptionInGame.mPresentState[REPLAY] = false;
            setIsRestarted(true);
            isRestarted = true;
            // ResetStats();
            HandleWhenReplay();
            continue;
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

        if(bird.GetIsDie()) {
            HandleWhenGameOver();
            ret_menu_over = SDLCommonFunc::ShowMenuGameOver2(gRenderer,
                                                            gFontMENU,
                                                            "Restart",
                                                            "HOME",
                                                            "Exit game",
                                                            std::to_string(money),
                                                            std::to_string(highestScore),
                                                            GameOverMenu);
            if (ret_menu_over == 0) HandleWhenReplay();
            else if (ret_menu_over == 1){
                goto again_label;
            }
            else {
                quit = true;
                FreeBird();
                return;}
        }
        else HandleWhenPlay();
        if(Mix_PausedMusic())   Mix_ResumeMusic();
        CheckCollision();
        changeFPS();
        SDL_RenderPresent(gRenderer);
    } 

}
std::vector<ThreatObject*> Game::MakeThreatList(){
    std::vector<ThreatObject*> list_threats;
    ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
    for(int th = 0; th < NUM_THREAT; th++){
        ThreatObject* p_threat = (p_threats + th);
        if(p_threat){
            // p_threat->LoadImageFile(Creepy_path,gRenderer);
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_threat->SetRect(SCREEN_WIDTH + th*DISTANCE_BETWEEN_THREATS ,rand_y);
            p_threat->set_x_val(THREAT_VELOCITY);
            // if(!getIsRestarted()){
                BulletObject* p_bullet = new BulletObject();
                p_threat->InitBullet(p_bullet);
            // }
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}
                                                                                                //IMPLEMENT THREAT
void Game::ImplementThreat(){
    for(int it = 0; it < NUM_THREAT; it++){
        ThreatObject* p_threat = threats_list.at(it);
        if(p_threat!=NULL){
            if(!getIsPaused()){
                random_threat = getRandomNumber(NUM_THREAT_FRAME)-1;
                p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            }
            collision.CollisionBirdAndThreat(pipe,p_threat_frame,bird,explosion_Collision,p_threat,random_threat);
            p_threat->MakeBullet(gRenderer,p_threat->GetRect().x,SCREEN_HEIGHT,pipe,getIsPaused(),getIsRestarted());
            bullet_arr = p_threat->GetBulletList();
            for(int am = 0; am  < bullet_arr.size();am++){
                p_bullet_threat = bullet_arr.at(am);
                if(p_bullet_threat!=NULL){
                    bool Collision_Bird_BulletOfThreat = SDLCommonFunc::CheckCollision(p_bullet_threat->GetRect(), bird.strikeObstacle());
                    if(Collision_Bird_BulletOfThreat){
                        if(!shield.getIsShield()){
                            collision.ExploringBird(pipe,bird,explosion_Collision);
                            bird.SetIsDie(true);
                            break;
                        }
                        else{
                            Mix_PlayChannel(-1,gBubblePow,0);
                            shield.setIsShield(false);
                            time_shield = 0;
                            bird.SetIsDie(false);
                            p_threat->ResetBullet(p_bullet_threat);
                            break;
                        }
                    }
                }
            }
            bool Collision_Bird_Threat = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_threat->GetRect());
            if(Collision_Bird_Threat){
                collision.ExploringBird(pipe,bird,explosion_Collision);
                bird.SetIsDie(true);
            }
            bullet_list = bird.get_bullet_list();
            for(int ib = 0 ; ib < bullet_list.size();ib++){
                p_bullet_bird = bullet_list.at(ib);
                if(p_bullet_bird!=NULL){
                    collision.CollisionBulletBirdandBulletThreat(p_bullet_bird,p_bullet_threat,p_threat);
                    bool ret_collision = SDLCommonFunc::CheckCollision(p_bullet_bird->GetRect(),p_threat->GetRect());
                    if(ret_collision){
                        moneyCur++;
                        for(int ex = 0; ex < 4; ex++){
                            int xPos = p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - BUL_WIDTH * 0.5 ;
                            int yPos = p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - BUL_HEIGHT * 0.5;
                            bullet_explosion.set_frame(ex);
                            bullet_explosion.SetRect(xPos,yPos);
                            bullet_explosion.ShowBul(gRenderer);
                            Mix_PlayChannel( -1, gExplosion, 0 );
                        }
                        if(!isPaused)p_threat->Reset(SCREEN_WIDTH + getRandomNumber(SCREEN_WIDTH*2));  //RESET POSI THREAT
                        bird.RemoveBullet(ib);                                          //REMOVE BULLET BIRD
                        Mix_PlayChannel(-1,gMoneyCol,0);
                    }
                }
            }
        }
    }
}
void Game::InitStats(){
    bird.SetIsDie(false);
    setIsTapped(false);
    shield.setIsShield(true);

        std::ifstream inputFile(Statistics_path);
    while(!inputFile.eof()){
        inputFile >> highestScore;
        inputFile >> money;
    }
    cout << highestScore << " " << money << endl;

    FreeObjectPointer();

    text_count_.SetColor(TextObject::BLACK_TEXT);
    text_money_game_.SetColor(TextObject::WHITE_TEXT);  

    std::string str("Press M to mute the music");
    text_guide_.SetColor(TextObject::BLACK_TEXT);
    text_guide_.SetText(str);
    text_guide_.loadFromRenderedText(gFontText,gRenderer);
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

    TappingFrame.LoadImageFile(Intro_path,gRenderer);
    shield.LoadImageFile(Shield_path,gRenderer);
    GameOverMenu.LoadImageFile(GameOverMenu_path,gRenderer);
    Tutorial.LoadImageFile(Tutorial_path,gRenderer);
    Statswd.LoadImageFile(Stastic_path,gRenderer);

}
void Game::ResetStats(){
    FreeObjectPointer();
    SDL_SetRenderDrawColor(gRenderer,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B,0xFF);         //CLEAR SCREEN   
	SDL_RenderClear(gRenderer);
    pipe.init_pipe();
    bird.resetPositon();
    shield.InitShield();
    bird.SetIsDie(false);
    setIsTapped(false);
    shield.setIsShield(true);
    time_shield = 69;
    scoreCur = 0;
    moneyCur = 0;
    moveY = 0;
    fps_manual = 0;
    ret_menu = 0;
    ret_menu_over = 0;
    ret_menu_tutorial = 0;
    ret_highestScore_window = 0;
  
    std::ifstream inputFile(Statistics_path);

        while(!inputFile.eof()){
            inputFile >> highestScore;
            inputFile >> money;
        }
        cout << highestScore << " " << money << endl;
    threats_list = MakeThreatList();
    money_list = MakeMoneyList();
    setIsRestarted(false);
}
void Game::CheckCollision(){
     if( bird.strikeObstacle().y +  bird.strikeObstacle().h >= SCREEN_HEIGHT - BASE_HEIGHT ||  bird.strikeObstacle().y < - PIPE_HEIGHT) {
        bird.SetIsDie(true);
        Mix_PlayChannel(-1,gDie,0);
    }     
    if(abs( bird.strikeObstacle().x - pipe.strikeUpperObstacle().x) <= 10 || 
       abs( bird.strikeObstacle().x - pipe.strikeLowerObstacle().x) <= 10 ) {
        ++scoreCur;
        Mix_PlayChannel(-1,gScoreIncrement,0);
    }

    if( SDLCommonFunc::CheckCollision (pipe.strikeLowerObstacle(),bird.strikeObstacle())||
        SDLCommonFunc::CheckCollision (bird.strikeObstacle(),pipe.strikeUpperObstacle()))
    {
        collision.ExploringBird(pipe,bird,explosion_Collision);
        bird.SetIsDie(true);
        Mix_PlayChannel(-1,gDie,0);
    }
}
void Game::HandleWhenReplay(){ ResetStats();}

void Game::HandleWhenPlay(){
                            //RENDER BACKGROUND
    BuildBackground_Base();   
                     
                                    //BIRD & BULLET_BIRD => UPDATE POSITION AND RENDER 
    bird.HandleBullet(gRenderer,pipe);                      
    bird.render();  
    if(getIsTapped()== false){
        // TappingFrame.LoadImageFile(Intro_path,gRenderer);
        SDL_Rect TapFrame = {SCREEN_WIDTH/2,SCREEN_HEIGHT/5,250,300};
        TappingFrame.RenderImage(gRenderer,TapFrame);
        return;
    }else{
    if(++fps_manual % 3 == 0){
        random_threat = getRandomNumber(NUM_THREAT_FRAME)-1;
        random_plant = getRandomNumber(NUM_PLANT)-1;
        random_icicle = getRandomNumber(NUM_ICICLE)-1;
    }
                        //IMPLEMENT THREAT & COLLISION
    ImplementThreat();
    ImplementMoney();
    ImplementShield();   
    checkBirdAndPlant = collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,random_plant,shield);
    checkBirdAndIcicle = collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,random_icicle,moveY,shield);
    
    if(checkBirdAndPlant || checkBirdAndIcicle){
        bird.SetIsDie(true);
        Mix_PlayChannel(-1,gDie,0);
    }
    bird.update();
                                    //PIPE
    pipe.update();      pipe.render();    
                                                    //LOADING BASE
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
                            //OPTION_CONTROL_GAME
    OptionInGame.render();                      
    ShowStats();
    setIsPlayed(false);
    }

    text_guide_.RenderText(gRenderer,SCREEN_WIDTH*0.01,SCREEN_HEIGHT*0.95);
}
void Game::HandleWhenGameOver(){
    std::ofstream outputFile("Stats/stats.txt");
    highestScore = max(highestScore,scoreCur);
    money += moneyCur;
    outputFile << highestScore << " " << money;

    BuildBackground_Base();
    ImplementThreat();
    ImplementMoney();
    ImplementShield();
    bird.render();          
    pipe.render();      
    checkBirdAndPlant = collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,random_plant,shield);
    checkBirdAndIcicle = collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,random_icicle,moveY,shield);
                                                    //LOADING BASE
    gBaseSurface.render(0,SCREEN_HEIGHT-BASE_HEIGHT);
    gBaseSurface.render(BASE_WIDTH,SCREEN_HEIGHT-BASE_HEIGHT);
    OptionInGame.render();   
    ShowStats();

    FreeObjectPointer();
    SDL_RenderPresent(gRenderer);
}
void Game::HandleWhenPause(){
    BuildBackground_Base();
    ImplementThreat();
    ImplementMoney();
    ImplementShield();
    bird.render();          
    pipe.render();      
    checkBirdAndPlant = collision.CollisionBirdAndPlant(pipe,plant,bird,explosion_Collision,random_plant,shield);
    checkBirdAndIcicle = collision.CollisionBirdAndIcicle(pipe,bird,icicle,explosion_Collision,random_icicle,moveY,shield);
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
    SDL_Rect rect_mn = {SCREEN_WIDTH/120,25,MONEY_SIZE/4*3,MONEY_SIZE/4*3};
    SDLCommonFunc::showInfo(" ", std::to_string(moneyCur), SCREEN_WIDTH*0.03, 25,1,rect_mn,Money_path,gFontText);
                                                                
    SDLCommonFunc:: showInfo("Score: ", std::to_string(scoreCur), SCREEN_WIDTH*0.01, 2,2,emptyObstacle,None_path,gFontText);//SHOW SCORE
        
    if( time_shield <= 0 ) time_shield = 0;
    SDL_Rect rect_item = {SCREEN_WIDTH/110,55,SHIELD_WIDTH/2,SHIELD_HEIGHT/2};//SHOW ITEM   
    SDLCommonFunc::showInfo(" ", std::to_string(time_shield), SCREEN_WIDTH*0.03, 50,1,rect_item,Shield_path,gFontText);
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

std::vector<MoneyObject*> Game::MakeMoneyList(){
    std::vector<MoneyObject*> list_money;
    MoneyObject* p_moneys = new MoneyObject[NUM_MONEY];
    for(int mo = 0; mo < NUM_MONEY; mo++){
        MoneyObject* p_money = (p_moneys + mo);
        if(p_money){
            p_money->LoadImageFile(Money_path,gRenderer);
            int rand_y = SDLCommonFunc::MakeRandValue();
            p_money->SetRect(SCREEN_WIDTH + mo*SCREEN_WIDTH*0.9,rand_y);
            p_money->set_x_val(THREAT_VELOCITY);// SET VELOCITY_MONEY
            list_money.push_back(p_money);
        }
    }
    return list_money;
}
void Game::ImplementMoney(){
    for(int m = 0; m < NUM_MONEY; m ++){
        MoneyObject* p_money = money_list.at(m);
        if(p_money!=NULL){
            // p_money->LoadImageFile(Money_path,gRenderer);
            if(!getIsPaused())p_money->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_money->Render(gRenderer);
            // p_money->SetRect(SCREEN_WIDTH + m*SCREEN_WIDTH*0.7,SDLCommonFunc::MakeRandValue());
            bool ret_collision = SDLCommonFunc::CheckCollision(bird.strikeObstacle(),p_money->GetRect());
            if(ret_collision){
                moneyCur++;
                p_money->Reset(SCREEN_WIDTH + getRandomNumber(SCREEN_WIDTH*1.5));
                Mix_PlayChannel(-1,gMoneyCol,0);
            }
        }

    }
}
void Game:: ImplementShield(){
    int cnt = 0;
    if(!getIsPaused())shield.HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
    shield.Render(gRenderer);
    if(SDLCommonFunc::CheckCollision(bird.strikeObstacle(),shield.GetRect())){
        shield.setIsShield(true);
        Mix_PlayChannel(-1,gBubbleAdd,0);
        shield.Reset();
        time_shield = 500;
    }
    if(!getIsPaused()){
        if(time_shield-- <= 0|| 
            checkBirdAndPlant||
            checkBirdAndIcicle){
        shield.setIsShield(false);
        }
        if(time_shield == 0) cnt = 1;
    }
    bird.renderShield(shield);
    if(cnt == 1){
        Mix_PlayChannel(-1,gBubblePow,0);
        cnt--;
    }

}
void Game:: FreeBird(){
    
    FreeObjectPointer();
    bird.FreeBullet();
    bird.Free();
    pipe.Free();
    OptionInGame.Free();
    fps_timer.Free();
    explosion_Collision.Free();
    bullet_explosion.Free();
    p_threat_frame.Free();
    shield.Free();
    icicle.Free();
    plant.Free();
    text_count_.Free();
    text_money_game_.Free();
    text_item_game_.Free();
    text_guide_.Free();
    TappingFrame.Free();
    GameOverMenu.Free();
    Tutorial.Free();
    Statswd.Free();
    collision.Free();

}
void Game:: FreeBulletList(){
    for(int i = 0; i < bullet_list.size(); i++){
        p_bullet_bird = bullet_list.at(i);
        if(p_bullet_bird){
            p_bullet_bird = NULL;
            delete[] p_bullet_bird;
        }
    }
    bullet_list.clear();
}
void Game:: FreeBulletArr(){
    for(int amfree = 0; amfree < bullet_arr.size(); amfree++){ //Maybe Error if too long
        p_bullet_threat = bullet_arr.at(amfree);
        if(p_bullet_threat){
            p_bullet_threat = NULL;
            delete[] p_bullet_threat;
        }
    }
    bullet_arr.clear();
}

void Game:: FreeMoney(){         ///Error
    for(int i = 0; i < money_list.size(); i++){
        MoneyObject* p_money = money_list.at(i);
        if(p_money){
            p_money ->Free();
            p_money = NULL;
        }
    }
    money_list.clear();
}
void Game:: FreeThreat(){
    for(int i = 0; i < threats_list.size(); i++){
        ThreatObject* p_threat = threats_list.at(i);
        if(p_threat){
            p_threat ->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();
}


void Game:: FreeObjectPointer(){
    FreeBulletArr();
    FreeBulletList();
    FreeThreat();
    FreeMoney();
}
void Game:: HandleInputAction(SDL_Event &e){
    //To do
}
#endif