#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <memory>
#include "ecs/ECSManager.hpp"
#include "ecs/system.hpp"

class ScoreSystem : public System {
  std::shared_ptr<EcsManager> ecsManager;
  std::unordered_map<EntityId, EntityId> collidedEntities{};
  int prevScore{-1};

public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void render(SDL_Renderer* renderer,  TTF_Font* font, SDL_Color color);
  void free() const;
  void resetScore();
};

#endif //SCORESYSTEM_HPP
