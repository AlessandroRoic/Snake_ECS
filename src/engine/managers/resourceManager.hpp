#ifndef SNAKE_ECS_RESOURCEMANAGER_HPP
#define SNAKE_ECS_RESOURCEMANAGER_HPP
#include <SDL_render.h>
#include "../components/renderable.hpp"
#include "../math/vector2.hpp"

class ResourceManager {
 public:
  static SDL2Renderable loadSDL2Renderable(SDL_Renderer* renderer,
                                           const char* path, Vector2 position);
};

#endif  //SNAKE_ECS_RESOURCEMANAGER_HPP
