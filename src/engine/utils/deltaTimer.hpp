#ifndef SNAKE_ECS_DELTATIMER_HPP
#define SNAKE_ECS_DELTATIMER_HPP

#include <chrono>
#include <cstdint>

class DeltaTimer {
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

 public:
  float deltaTime;
  DeltaTimer() : deltaTime{0.0f} {}
  void start();
  void updateDeltaTime();
};
#endif  //SNAKE_ECS_DELTATIMER_HPP
