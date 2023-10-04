#ifndef SNAKE_ECS_RENDERABLE_HPP
#define SNAKE_ECS_RENDERABLE_HPP

#include <SDL_render.h>

struct SDL2Renderable {
  SDL_Texture* texture{};
  SDL_FRect rect{};
};

#endif  //SNAKE_ECS_RENDERABLE_HPP
