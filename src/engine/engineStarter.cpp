#include "engineStarter.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "ecs/ecsPlaceholder.hpp"
#include "resourceManager.hpp"
#include "systems/physics2DSystem.hpp"

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
  auto& ecsPlaceholder = EcsPlaceholder::getInstance();

  ecsPlaceholder.init();

  ecsPlaceholder.registerComponent<Transform2D>();
  ecsPlaceholder.registerComponent<SDL2Renderable>();

  physics2DSystem = Physics2DSystem::init();
  render2DSystem = Render2DSystem::init();

  EntityId entity = ecsPlaceholder.createEntity();

  const auto position = Vector2(windowManager.getWindowWidth() / 2.0f,
                                windowManager.getWindowHeight() / 2.0f);
  ecsPlaceholder.addComponent(entity, Transform2D{
                                          position,
                                      });
  ecsPlaceholder.addComponent(
      entity, ResourceManager::loadSDL2Renderable(renderer, "./assets/mock.png",
                                                  position));

  return true;
}

void EngineStarter::onUpdate(float dt) {
  physics2DSystem->update(dt);
}

void EngineStarter::onRender() {
  render2DSystem->render(renderer);
}

void EngineStarter::onRenderStop() {}

void EngineStarter::onClose() {
  render2DSystem->free();
}
