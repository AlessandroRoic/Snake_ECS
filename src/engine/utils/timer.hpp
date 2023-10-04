#ifndef SNAKE_ECS_TIMER_HPP
#define SNAKE_ECS_TIMER_HPP
#include <SDL_timer.h>
#include <functional>

class Timer {
 public:
  static SDL_TimerID setTimeout(Uint32 delay, std::function<void()> callback);
};

#endif  //SNAKE_ECS_TIMER_HPP
