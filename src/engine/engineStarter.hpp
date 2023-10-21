#ifndef SNAKE_ECS_ENGINESTARTER_HPP
#define SNAKE_ECS_ENGINESTARTER_HPP

#include "ecs/ECSManager.hpp"
#include "engine.hpp"
#include "physics2DSystem.hpp"
#include "render2DSystem.hpp"

class EngineStarter : Engine {
  std::shared_ptr<Physics2DSystem> physics2DSystem;
  std::shared_ptr<Render2DSystem> render2DSystem;
  std::shared_ptr<EcsManager> ecsManager;

  bool onInit() override;
  void onUpdate(float dt) override;
  void onRender() override;
  void onRenderStop() override;
  void onClose() override;

 public:
  static int start();
};

#endif  //SNAKE_ECS_ENGINESTARTER_HPP
