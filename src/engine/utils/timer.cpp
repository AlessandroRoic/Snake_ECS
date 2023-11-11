#include "timer.hpp"
#include <memory>
#include <utility>

SDL_TimerID Timer::setTimeout(const Uint32 delay, std::function<void()> callback) {
  std::unique_ptr<std::function<void()>> callbackPtr =
      std::make_unique<std::function<void()>>(std::move(callback));

  const SDL_TimerID timerID = SDL_AddTimer(
      delay,
      [](Uint32, void* param) -> Uint32 {
        const std::function<void()>& timerCallback =
            *static_cast<std::function<void()>*>(param);
        timerCallback();
        return 0;
      },
      callbackPtr.get());

  callbackPtr = nullptr;

  return timerID;
}
