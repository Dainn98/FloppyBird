
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
// #include "declaration.h"

class ImpTimer : public BaseObject{
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
  int start_tick_; //TIME IS STARTESD
  int paused_ticks_; //THE TICKS WHEN TIMER WAS PAUSED
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
    is_paused_ = false;                                               //RESET THE STARTING TICKS
    start_tick_ = SDL_GetTicks() - paused_ticks_;                    //TRESET THE PAUSED TICKS
    paused_ticks_ = 0;
  }
}

int ImpTimer::get_ticks(){
  if( is_started_ == true ){                                         //WHEN THE TIMER IS PAUSED
    if( is_paused_ == true )  return paused_ticks_;
    else return SDL_GetTicks() - start_tick_;
  }                        
  return 0;                                                          //IF THE TIMER IS NOT STARTED YET, RETURN ZERO
}

bool ImpTimer::is_started() {return is_started_;}

bool ImpTimer::is_paused()  {return is_paused_;}

#endif