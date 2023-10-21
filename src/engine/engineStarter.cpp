#include "engineStarter.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "ecs/entity.hpp"

int EngineStarter::start() {
  if (!init()) {
    close();
    return 1;
  }

  while (getIsRunning()) {
    update();
    render();
  }

  close();

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

  eventManager.fire(&lifecyleEvents[EventType::INIT]);
  return true;
}

void EngineStarter::onUpdate(float dt) {
  physics2DSystem->update(dt);
  eventManager.fire(&lifecyleEvents[EventType::UPDATE]);
}

void EngineStarter::onRender() {
  render2DSystem->render(renderManager.getRenderer());
  eventManager.fire(&lifecyleEvents[EventType::RENDER]);
}

void EngineStarter::onRenderStop() {
  eventManager.fire(&lifecyleEvents[EventType::RENDER_STOP]);
}

void EngineStarter::onClose() {
  render2DSystem->free();
  eventManager.fire(&lifecyleEvents[EventType::CLOSE]);
}
