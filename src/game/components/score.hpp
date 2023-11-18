#ifndef SCORE_HPP
#define SCORE_HPP

#include <SDL_surface.h>

struct ScoreComponent {
  SDL_Surface* textSurface{nullptr};
  int score = 0;
};
#endif //SCORE_HPP
