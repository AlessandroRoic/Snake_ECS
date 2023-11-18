#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP
#include <SDL_render.h>

struct GameOverScreen {
  SDL_Texture* textTexture = nullptr;
  SDL_Rect rect{};
};

#endif //GAMEOVERSCREEN_HPP
