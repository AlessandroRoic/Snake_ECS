#include "gameManager.hpp"
#include "components/collider.hpp"
#include "components/score.hpp"
#include "components/snake.hpp"
#include "components/transform.hpp"
#include "spawners/appleSpawner.hpp"
#include "spawners/playerSpawner.hpp"
#include "spawners/scoreSpawner.hpp"
#include "systems/scoreSystem.hpp"

void GameManager::onInit() {
  TTF_Font* font = ResourceManager::loadFont("./assets/gameFont.ttf", 42);
  engine.resourceManager.setGlobalFont(font);
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(engine.resourceManager.getGlobalFont(), "Game Over",
                           engine.resourceManager.getTextColor());
  gameOverScreen.textTexture = SDL_CreateTextureFromSurface(
      engine.renderManager.getRenderer(), textSurface);
  gameOverScreen.rect = {
      engine.windowManager.getWindowWidth() / 2 - textSurface->w / 2,
      engine.windowManager.getWindowHeight() / 2 - textSurface->h / 2,
      textSurface->w, textSurface->h};
  SDL_FreeSurface(textSurface);

  engine.ecsManager->registerComponent<Snake>();
  engine.ecsManager->registerComponent<Transform2D>();
  engine.ecsManager->registerComponent<Collider>();
  engine.ecsManager->registerComponent<SDLSprite>();
  engine.ecsManager->registerComponent<ScoreComponent>();

  snakeSystem = engine.ecsManager->registerSystem<SnakeSystem>();
  renderSystem = engine.ecsManager->registerSystem<Render2DSystem>();
  collisionSystem = engine.ecsManager->registerSystem<CollisionSystem>();
  scoreSystem = engine.ecsManager->registerSystem<ScoreSystem>();

  snakeSystem->init(engine.ecsManager, &engine.eventManager,
                    engine.windowManager.getWindowWidth(),
                    engine.windowManager.getWindowHeight());
  renderSystem->init(engine.ecsManager);
  collisionSystem->init(engine.ecsManager);
  scoreSystem->init(engine.ecsManager);

  score = ScoreSpawner::spawn(engine);
  snake = PlayerSpawner::spawn(engine);

  const SDLSprite sprite = ResourceManager::loadSDL2Renderable(
      engine.renderManager.getRenderer(), "./assets/field.png", {0, 0});
  engine.ecsManager->addComponent<SDLSprite>(engine.ecsManager->createEntity(),
                                             sprite);
  AppleSpawner::spawn(engine);
}

void GameManager::onUpdate(const Event* event) {
  if (gameOverTimerID != 0) {
    SDL_RemoveTimer(gameOverTimerID);
    gameOverTimerID = 0;
    engine.ecsManager->destroyEntity(snake);
    snake = PlayerSpawner::spawn(engine);
  }

  collisionSystem->update(snake, score);

  //TODO: this is a bottleneck, needs improvement -> data should be a void pointer
  const auto dt = std::any_cast<float>(event->data);
  snakeSystem->update(dt, engine.inputManager.pressedKeys);
}

void GameManager::onRender() const {
  const auto renderer = engine.renderManager.getRenderer();
  renderSystem->render(renderer);
  snakeSystem->render(renderer);
  scoreSystem->render(renderer, engine.resourceManager.getGlobalFont(),
                      engine.resourceManager.getTextColor());
}

void GameManager::onRenderStop() {
  SDL_RenderCopy(engine.renderManager.getRenderer(), gameOverScreen.textTexture,
                 nullptr, &gameOverScreen.rect);
  if (gameOverTimerID != 0)
    return;
  gameOverTimerID = SDL_AddTimer(
      500,
      [](Uint32, void* param) -> Uint32 {
        const auto engine = static_cast<Engine*>(param);
        engine->setIsStopped(false);
        return 0;
      },
      &engine);
}

void GameManager::onClose() const {
  SDL_DestroyTexture(gameOverScreen.textTexture);
  scoreSystem->free();
  snakeSystem->free();
  renderSystem->free();
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
