#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include <SDL_render.h>

class RenderManager {
  SDL_Renderer* renderer{};

 public:
  bool init(SDL_Window* window);
  SDL_Renderer* getRenderer() const;
  void updateScreen() const;
  void clearScreen() const;
  void destroyRenderer();
};

#endif  // RENDERMANAGER_HPP
