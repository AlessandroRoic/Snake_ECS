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

public:
  void init(const std::shared_ptr<EcsManager>& _ecsManager);
  void render(SDL_Renderer* renderer,  TTF_Font* font, SDL_Color color) const;
  void free() const;
};

#endif //SCORESYSTEM_HPP
