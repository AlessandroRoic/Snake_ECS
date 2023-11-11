#include "gameManager.hpp"
#include "components/snake.hpp"
#include "components/transform.hpp"
#include "player/playerController.hpp"

void GameManager::onInit() {
  engine.ecsManager->registerComponent<Snake>();
  engine.ecsManager->registerComponent<Transform2D>();

  snakeSystem = engine.ecsManager->registerSystem<SnakeSystem>();
  snakeSystem->init(engine.ecsManager);

  auto snake = PlayerController::spawn(engine);
}

void GameManager::onUpdate(const Event* event) const {
  //TODO: this is a bottleneck, needs improvement -> data should be a general pointer
  const auto dt = std::any_cast<float>(event->data);
  snakeSystem->update(dt, engine.inputManager.pressedKeys);
}

void GameManager::onRender() {
  snakeSystem->render(engine.renderManager.getRenderer());
}

void GameManager::onRenderStop(const Event* event) {}

void GameManager::onClose() {
  snakeSystem->free();
}

int GameManager::start() {
  // TODO: find a way to improve this
  const auto onInitPtr =
      std::make_shared<CallbackFunction>([this](const Event*) { onInit(); });
  const auto onUpdatePtr = std::make_shared<CallbackFunction>(
      [this](const Event* event) { onUpdate(event); });
  const auto onRenderPtr =
      std::make_shared<CallbackFunction>([this](const Event*) { onRender(); });
  const auto onRenderStopPtr = std::make_shared<CallbackFunction>(
      [this](const Event* event) { onRenderStop(event); });
  const auto onClosePtr =
      std::make_shared<CallbackFunction>([this](const Event*) { onClose(); });

  // TODO: batch subscribe to event manager
  engine.eventManager.subscribe(INIT, onInitPtr);
  engine.eventManager.subscribe(UPDATE, onUpdatePtr);
  engine.eventManager.subscribe(RENDER, onRenderPtr);
  engine.eventManager.subscribe(RENDER_STOP, onRenderStopPtr);
  engine.eventManager.subscribe(CLOSE, onClosePtr);

  return engine.start();
}
