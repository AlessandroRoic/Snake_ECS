#include "playerController.hpp"
#include "../components/snake.hpp"
#include "../components/transform.hpp"

SDL_Rect mapJsonToRect(nlohmann::json json, const std::string& key) {
  const SDL_Rect rect{json[key]["x"], json[key]["y"], json[key]["w"], json[key]["h"]};
  return rect;
}

Snake generateSnake(SDL_Renderer* renderer, const Vector2 position) {
  SDL_Texture* snakeSpreadsheet =
      ResourceManager::loadSDLTexture(renderer, "./assets/snake.png");

  const nlohmann::json partRectJson =
      ResourceManager::loadJSON("./assets/snake.json");

  const std::array partsRect{
      mapJsonToRect(partRectJson, "head"), mapJsonToRect(partRectJson, "body"),
      mapJsonToRect(partRectJson, "body_angled"),
      mapJsonToRect(partRectJson, "tail"),
      mapJsonToRect(partRectJson, "tail_angled")};
  const auto dimension = static_cast<float>(partsRect[0].w);

  const std::vector<SnakeUnit> composition{
      {HEAD, {position.x, position.y, dimension, dimension}, 0},
      {BODY,
       {position.x, position.y + dimension, dimension, dimension},
       0},
      {TAIL,
       {position.x, position.y + dimension * 2, dimension, dimension},
       0}};

  return {snakeSpreadsheet, partsRect, composition, SDL_SCANCODE_UP};
}

EntityId PlayerController::spawn(const Engine& engine) {
  auto& ecsManager = engine.ecsManager;
  auto& windowManager = engine.windowManager;
  auto& renderManager = engine.renderManager;

  const EntityId entity = ecsManager->createEntity();

  const auto position = Vector2(windowManager.getWindowWidth() / 2.0f,
                                windowManager.getWindowHeight() / 2.0f);

  ecsManager->addComponent<Transform2D>(
      entity, Transform2D{position, Vector2(0, -0.5)});
  ecsManager->addComponent<Snake>(
      entity, generateSnake(renderManager.getRenderer(), position));

  return entity;
}
