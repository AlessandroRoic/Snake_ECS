#include "placeholder.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "ecs/ecsPlaceholder.hpp"
#include "resourceManager.hpp"
#include "systems/physics2DSystem.hpp"

int PlaceHolder::start() {
  PlaceHolder game;
  if (!game.init()) {
    game.close();
    return 1;
  }

  while (game.isRunning) {
    game.update();
    game.render();
  }

  game.close();

  return 0;
}

bool PlaceHolder::onInit() {
  auto& ecsPlaceholder = EcsPlaceholder::getInstance();

  ecsPlaceholder.init();

  ecsPlaceholder.registerComponent<Transform2D>();
  ecsPlaceholder.registerComponent<SDL2Renderable>();

  //TODO: move to init?
  physics2DSystem = ecsPlaceholder.registerSystem<Physics2DSystem>();
  Signature signature;
  signature.set(ecsPlaceholder.getComponentType<Transform2D>());
  ecsPlaceholder.setSystemSignature<Physics2DSystem>(signature);

  render2DSystem = ecsPlaceholder.registerSystem<Render2DSystem>();
  Signature render2DSignature;
  render2DSignature.set(ecsPlaceholder.getComponentType<SDL2Renderable>());
  ecsPlaceholder.setSystemSignature<Render2DSystem>(render2DSignature);

  EntityId entity = ecsPlaceholder.createEntity();

  const auto position = Vector2(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
  ecsPlaceholder.addComponent(entity, Transform2D{
                                          position,
                                      });
  ecsPlaceholder.addComponent(
      entity, ResourceManager::loadSDL2Renderable(renderer, "./assets/mock.png",
                                                  position));
  return true;
}

void PlaceHolder::onUpdate(float dt) {
  physics2DSystem->update(dt);
}

void PlaceHolder::onRender() {
  render2DSystem->render(renderer);
}

void PlaceHolder::onRenderStop() {}

void PlaceHolder::onClose() {
  render2DSystem->free();
}
