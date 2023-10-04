#ifndef SNAKE_ECS_KEYBOARDMANAGER_HPP
#define SNAKE_ECS_KEYBOARDMANAGER_HPP
#include <SDL_events.h>
#include <unordered_set>
#include <vector>

class KeyboardManager {
 public:
  std::unordered_set<SDL_Scancode> pressedKeys;
  void handleEvent(SDL_Event event);
};
#endif  //SNAKE_ECS_KEYBOARDMANAGER_HPP
