
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
#include "declaration.h"

class ImpTimer{
public:
  ImpTimer();
  void start();
  void stop();
  void pause();
  void unpause();
  int get_ticks();
  bool is_started();
  bool is_paused();

private:
  int start_tick_; //time at started
  int paused_ticks_; //The ticks stored when the timer was pause
  bool is_paused_;
  bool is_started_;
};


ImpTimer::ImpTimer(){
  start_tick_ = 0;
  paused_ticks_ = 0;
  is_paused_ = false;
  is_started_ = false;
}

void ImpTimer::start(){
  is_started_ = true;
  is_paused_ = false;
  start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop(){
  is_started_ = false;
  is_paused_ = false;
}

void ImpTimer::pause(){
  if( ( is_started_ == true ) && ( is_paused_ == false ) ){
    is_paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_tick_;
  }
}

void ImpTimer::unpause(){
  if( is_paused_ == true ){
    is_paused_ = false; //Reset the starting ticks
    start_tick_ = SDL_GetTicks() - paused_ticks_;   //Reset the paused ticks
    paused_ticks_ = 0;
  }
}

int ImpTimer::get_ticks(){
  if( is_started_ == true ){
    //If the timer is paused
    if( is_paused_ == true )  return paused_ticks_;
    else return SDL_GetTicks() - start_tick_;
  }
  //If the timer isn't running
  return 0;
}

bool ImpTimer::is_started() {return is_started_;}

bool ImpTimer::is_paused()  {return is_paused_;}

#endif