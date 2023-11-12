#include "gameManager.hpp"
#include "components/snake.hpp"
#include "components/transform.hpp"
#include "player/playerController.hpp"

void GameManager::onInit() {
  TTF_Font* font = ResourceManager::loadFont("./assets/gameFont.ttf", 42);
  engine.resourceManager.setGlobalFont(font);
  engine.ecsManager->registerComponent<Snake>();
  engine.ecsManager->registerComponent<Transform2D>();
  snakeSystem = engine.ecsManager->registerSystem<SnakeSystem>();
  snakeSystem->init(engine.ecsManager, &engine.eventManager,
                    engine.windowManager.getWindowWidth(),
                    engine.windowManager.getWindowHeight());
  snake = PlayerController::spawn(engine);
}

void GameManager::onUpdate(const Event* event) const {
  //TODO: this is a bottleneck, needs improvement -> data should be a general pointer
  const auto dt = std::any_cast<float>(event->data);
  snakeSystem->update(dt, engine.inputManager.pressedKeys);
}

void GameManager::onRender() const {
  snakeSystem->render(engine.renderManager.getRenderer());
}

void GameManager::onRenderStop() const {
  auto* renderer = engine.renderManager.getRenderer();
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(engine.resourceManager.getGlobalFont(), "Game Over",
                           engine.resourceManager.getTextColor());
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
      engine.renderManager.getRenderer(), textSurface);
  const SDL_Rect textRect = {
      engine.windowManager.getWindowWidth() / 2 - textSurface->w / 2,
      engine.windowManager.getWindowHeight() / 2 - textSurface->h / 2,
      textSurface->w, textSurface->h};
  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
  SDL_FreeSurface(textSurface);
}

void GameManager::onClose() const {
  snakeSystem->free();
}

void GameManager::onGameEnd() {
  engine.setIsStopped(true);
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
      [this](const Event*) { onRenderStop(); });
  const auto onClosePtr =
      std::make_shared<CallbackFunction>([this](const Event*) { onClose(); });
  const auto onGameEndPtr =
      std::make_shared<CallbackFunction>([this](const Event*) { onGameEnd(); });

  // TODO: batch subscribe to event manager
  engine.eventManager.subscribe(INIT, onInitPtr);
  engine.eventManager.subscribe(UPDATE, onUpdatePtr);
  engine.eventManager.subscribe(RENDER, onRenderPtr);
  engine.eventManager.subscribe(RENDER_STOP, onRenderStopPtr);
  engine.eventManager.subscribe(CLOSE, onClosePtr);
  engine.eventManager.subscribe(GAME_END, onGameEndPtr);

  return engine.start();
}
