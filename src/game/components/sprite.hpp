#ifndef SNAKE_ECS_SPRITE_HPP
#define SNAKE_ECS_SPRITE_HPP

#include <SDL_render.h>

struct SDLSprite {
  SDL_Texture* texture{};
  SDL_FRect rect{};
};

#endif  //SNAKE_ECS_SPRITE_HPP
