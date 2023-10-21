#ifndef SNAKE_ECS_ENGINESTARTER_HPP
#define SNAKE_ECS_ENGINESTARTER_HPP

#include "ecs/ECSManager.hpp"
#include "engine.hpp"
#include "physics2DSystem.hpp"
#include "render2DSystem.hpp"

class EngineStarter : public Engine {
  std::shared_ptr<Physics2DSystem> physics2DSystem;
  std::shared_ptr<Render2DSystem> render2DSystem;
  std::shared_ptr<EcsManager> ecsManager;
  const std::array<Event, 5> lifecyleEvents{
      {Event(EventType::INIT), Event(EventType::UPDATE),
       Event(EventType::RENDER), Event(EventType::RENDER_STOP),
       Event(EventType::CLOSE)}};

  bool onInit() override;
  void onUpdate(float dt) override;
  void onRender() override;
  void onRenderStop() override;
  void onClose() override;

 public:
  int start();
};

#endif  //SNAKE_ECS_ENGINESTARTER_HPP
