#ifndef SNAKE_ECS_RENDER2DSYSTEM_HPP
#define SNAKE_ECS_RENDER2DSYSTEM_HPP

#include <SDL_render.h>
#include "../ecs/system.hpp"

class Render2DSystem : public System {
 public:
  void render(SDL_Renderer *renderer);
  void free();
};

#endif  //SNAKE_ECS_RENDER2DSYSTEM_HPP
