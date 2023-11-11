#ifndef SNAKE_ECS_INPUTMANAGER_HPP
#define SNAKE_ECS_INPUTMANAGER_HPP
#include <SDL_events.h>
#include <unordered_set>
#include <vector>

class InputManager {
 public:
  //TODO: could be improved and also might need to change how to manage key presses
  std::unordered_set<SDL_Scancode> pressedKeys;
  void handleEvent(SDL_Event event);
};
#endif  //SNAKE_ECS_INPUTMANAGER_HPP
