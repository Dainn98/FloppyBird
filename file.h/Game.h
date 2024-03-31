#ifndef Game_h
#define Game_h
#include "declaration.h"
#include "Bird.h"
#include "Pipe.h"
#include "LTexture.h"
#include "Pause.h"
#include "impTimer.h"
#include "Explosion.h"
#include "BaseObject.h"
#include "ThreatObject.h"
#include "TextObject.h"
#include "PlantObject.h"
#include "Collision_With_Obstacles.h"

class Game : public BaseObject{
private:    
    unsigned int bullet_type_ = 50;
    unsigned int money = 0;
    unsigned int  score = 0;
    int moveY = 0;
    int NUM_THREAT_CURRENT = 1;
    
    bool isPaused = false;
    bool isRestarted = false;
    bool isPlayed = true;
    bool quit = false;
    bool isDyingBird = false;
    
    int random_plant;
    int random_icicle;
    
    ThreatObject* p_threat_list = new ThreatObject[NUM_THREAT];
    
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

    void setIsPaused(const bool isPaused_) {isPaused = isPaused_;}
    bool getIsPaused() const {return isPaused;}
    void setIsPlayed(const bool isPlayed_) {isPlayed = isPlayed_;}
    bool getIsPlayed() const {return isPlayed;}
    void setIsRestarted(const bool isRestarted_) {isRestarted = isRestarted_;}
    bool getIsRestarted() const {return isRestarted;}
    
    void ShowStats();
    void BuildBackground_Base();
    void ImplementThreat();
    void ResetStats();
    void changeFPS();
};

Game::Game(){
    //To do
}
Game::~Game(){
    //To do 
    delete[] p_threat_list;
    bullet_arr.clear();
    bullet_list.clear();
    p_bullet_bird = NULL;
    p_bullet_threat = NULL;
}
#endif