#include "playerSpawner.hpp"
#include "../components/collider.hpp"
#include "../components/snake.hpp"

SDL_Rect mapJsonToRect(nlohmann::json json, const std::string& key) {
  const SDL_Rect rect{json[key]["x"], json[key]["y"], json[key]["w"],
                      json[key]["h"]};
  return rect;
}

Snake generateSnake(SDL_Renderer* renderer, const Vector2 position) {
  SDL_Texture* snakeSpreadsheet =
      ResourceManager::loadSDLTexture(renderer, "./assets/snake.png");

  const nlohmann::json partRectJson =
      ResourceManager::loadJSON("./assets/snake.json");

  const std::array partsRect{mapJsonToRect(partRectJson, "head"),
                             mapJsonToRect(partRectJson, "body"),
                             mapJsonToRect(partRectJson, "body_angled"),
                             mapJsonToRect(partRectJson, "tail"),
                             mapJsonToRect(partRectJson, "tail_angled")};
  const auto dimension = static_cast<float>(partsRect[0].w);

  const std::vector<SnakeUnit> composition{
      {HEAD, {position.x, position.y, dimension, dimension}, 0},
      {BODY, {position.x, position.y + dimension, dimension, dimension}, 0},
      {TAIL,
       {position.x, position.y + dimension * 2, dimension, dimension},
       0}};

  return {snakeSpreadsheet, partsRect, composition};
}

void addBodyPart(Snake& snake) {
  auto& tail = snake.composition.back();
  const auto currentDirection =
      tail.currentDirection == SDL_SCANCODE_DOWN ||
              tail.currentDirection == SDL_SCANCODE_RIGHT
          ? -1.0f
          : 1.0f;
  auto newPart = tail;
  newPart.part = BODY;
  const auto axis =
      tail.angle == 90 || tail.angle == -90 ? VERTICAL : HORIZONTAL;
  auto& partAxis = axis == VERTICAL ? tail.positionRect.x : tail.positionRect.y;
  partAxis += currentDirection * tail.positionRect.w;
  snake.composition.push_back(newPart);
  std::swap(snake.composition.back(),
            snake.composition.at(snake.composition.size() - 2));
}

void onSnakeCollision(Engine& engine, const EntityId self,
                      const EntityId other) {
  if (self == other) {
    const Event event{GAME_END};
    engine.eventManager.fire(&event);
  } else {
    addBodyPart(engine.ecsManager->getComponent<Snake>(self));
  }
}

EntityId PlayerSpawner::spawn(Engine& engine) {
  const auto& ecsManager = engine.ecsManager;
  const auto& windowManager = engine.windowManager;
  const auto& renderManager = engine.renderManager;

  const EntityId entity = ecsManager->createEntity();

  const auto position = Vector2(windowManager.getWindowWidth() / 2.0f,
                                windowManager.getWindowHeight() / 2.0f);

  ecsManager->addComponent<Snake>(
      entity, generateSnake(renderManager.getRenderer(), position));
  ecsManager->addComponent<Collider>(
      entity, {[&engine](const EntityId self, const EntityId other) {
        onSnakeCollision(engine, self, other);
      }});
  return entity;
}
