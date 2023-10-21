#include <SDL_render.h>

class RenderManager {
  SDL_Renderer* renderer{};

 public:
  bool init(SDL_Window* window);
  SDL_Renderer* getRenderer() const;
  void updateScreen();
  void clearScreen();
  void destroyRenderer();
};
