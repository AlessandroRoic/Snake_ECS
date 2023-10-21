#include "engineStarter.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "ecs/entity.hpp"
#include "resourceManager.hpp"

int EngineStarter::start() {
  EngineStarter game;
  if (!game.init()) {
    game.close();
    return 1;
  }

  while (game.getIsRunning()) {
    game.update();
    game.render();
  }

  game.close();

  return 0;
}

bool EngineStarter::onInit() {
  ecsManager = std::make_shared<EcsManager>();
  ecsManager->registerComponent<Transform2D>();
  ecsManager->registerComponent<SDL2Renderable>();

  physics2DSystem = ecsManager->registerSystem<Physics2DSystem>();
  physics2DSystem->init(ecsManager);
  render2DSystem = ecsManager->registerSystem<Render2DSystem>();
  render2DSystem->init(ecsManager);

  Entity entity{ecsManager};

  const auto position = Vector2(windowManager.getWindowWidth() / 2.0f,
                                windowManager.getWindowHeight() / 2.0f);

  entity.addComponent<Transform2D>(Transform2D{
      position,
  });

  entity.addComponent<SDL2Renderable>(ResourceManager::loadSDL2Renderable(
      renderManager.getRenderer(), "./assets/mock.png", position));

  return true;
}

void EngineStarter::onUpdate(float dt) {
  physics2DSystem->update(dt);
}

void EngineStarter::onRender() {
  render2DSystem->render(renderManager.getRenderer());
}

void EngineStarter::onRenderStop() {}

void EngineStarter::onClose() {
  render2DSystem->free();
}
