#include "deltaTimer.hpp"

void DeltaTimer::start() {
  startTime = std::chrono::high_resolution_clock::now();
}

void DeltaTimer::updateDeltaTime() {
  const auto stopTime = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(
                  stopTime - startTime)
                  .count();
}
