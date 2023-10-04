#ifndef SNAKE_ECS_PLACEHOLDER_HPP
#define SNAKE_ECS_PLACEHOLDER_HPP

#include "ecs/ecsPlaceholder.hpp"
#include "engine.hpp"
#include "physics2DSystem.hpp"
#include "render2DSystem.hpp"

class PlaceHolder : Engine {
  std::shared_ptr<Physics2DSystem> physics2DSystem = nullptr;
  std::shared_ptr<Render2DSystem> render2DSystem{};

  bool onInit() override;
  void onUpdate(float dt) override;
  void onRender() override;
  void onRenderStop() override;
  void onClose() override;

 public:
  static int start();
};

#endif  //SNAKE_ECS_PLACEHOLDER_HPP
