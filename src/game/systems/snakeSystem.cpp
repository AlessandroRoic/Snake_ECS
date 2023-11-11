#include "snakeSystem.hpp"
#include <SDL_render.h>
#include <map>
#include "../components/snake.hpp"
#include "../components/transform.hpp"

enum AXIS { VERTICAL, HORIZONTAL };

const std::map<SDL_Scancode, Vector2> scanCodeToDirection = {
    {SDL_SCANCODE_RIGHT, Vector2{1, 0}},
    {SDL_SCANCODE_LEFT, Vector2{-1, 0}},
    {SDL_SCANCODE_DOWN, Vector2{0, 1}},
    {SDL_SCANCODE_UP, Vector2{0, -1}},
};

const std::map<std::pair<SDL_Scancode, SDL_Scancode>, std::int16_t>
    changeDirectionAngles = {{{SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT}, 90},
                             {{SDL_SCANCODE_UP, SDL_SCANCODE_LEFT}, -90},

                             {{SDL_SCANCODE_DOWN, SDL_SCANCODE_RIGHT}, 90},
                             {{SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT}, -90},

                             {{SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP}, 0},
                             {{SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN}, 180},

                             {{SDL_SCANCODE_LEFT, SDL_SCANCODE_UP}, 0},
                             {{SDL_SCANCODE_LEFT, SDL_SCANCODE_DOWN}, 180}};

const std::map<std::pair<SDL_Scancode, SDL_Scancode>, SDL_RendererFlip>
    flipDirections = {
        {{SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT}, SDL_FLIP_HORIZONTAL},
        {{SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT}, SDL_FLIP_HORIZONTAL},
        {{SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN}, SDL_FLIP_HORIZONTAL},
        {{SDL_SCANCODE_LEFT, SDL_SCANCODE_UP}, SDL_FLIP_HORIZONTAL},
};

void SnakeSystem::init(const std::shared_ptr<EcsManager>& _ecsManager) {
  ecsManager = _ecsManager;
  Signature snakeSignature;
  snakeSignature.set(ecsManager->getComponentType<Snake>());
  snakeSignature.set(ecsManager->getComponentType<Transform2D>());
  ecsManager->setSystemSignature<SnakeSystem>(snakeSignature);
}

void updateSnakeDirection(Snake& snake,
                          const std::unordered_set<SDL_Scancode>& pressedKeys) {
  // If no keys are pressed skip update of velocity
  if (pressedKeys.begin() == pressedKeys.end())
    return;

  const auto direction = scanCodeToDirection.find(*pressedKeys.begin());

  if (const auto validMove = changeDirectionAngles.find(
          {snake.currentDirection, direction->first});
      direction == scanCodeToDirection.end() ||
      validMove == changeDirectionAngles.end() || snake.currentPart > 0)
    return;
  // If it is a mapped key, and it has changed direction update the velocity
  snake.newDirection = {direction->first, direction->second};
}

// TODO: move parts using dt
void moveSnakeParts(Snake& snake, const std::int16_t newAngle) {
  // update current part angle
  auto& [part, rect, angle] = snake.composition.at(snake.currentPart);
  angle = newAngle;

  const auto axis =
      newAngle == 90 || newAngle == -90 ? VERTICAL : HORIZONTAL;
  const auto angleDirection = newAngle > 0 ? 1.0f : -1.0f;

  // Move parts one block to the new direction until currentPart
  for (int i = 0; i <= snake.currentPart; i++) {
    auto& [part, rect, angle] = snake.composition.at(i);
    auto& partAxis = axis == VERTICAL ? rect.x : rect.y;
    partAxis += angleDirection * rect.w;
  }

  // Move other parts one block in the current direction
  if (part != TAIL) {
    const auto currentDirection =
        snake.currentDirection == SDL_SCANCODE_DOWN ||
                snake.currentDirection == SDL_SCANCODE_RIGHT
            ? 1.0f
            : -1.0f;
    for (int i = snake.currentPart + 1; i < snake.composition.size(); i++) {
      auto& [part, rect, angle] = snake.composition.at(i);
      auto& partAxis = axis == VERTICAL ? rect.y : rect.x;
      partAxis += currentDirection * rect.w;
    }
  }
}

void animateSnake(const float dt, Snake& snake, Transform2D& transform) {
  if (const auto validMove = changeDirectionAngles.find(
          {snake.currentDirection, snake.newDirection.first});
      validMove == changeDirectionAngles.end())
    return;
  snake.lastUpdate += dt;

  if (snake.lastUpdate <= snake.animateSpeed)
    return;
  snake.lastUpdate = 0;

  // if it's a valid move then update the part angle
  const auto angle = changeDirectionAngles.find(
      {snake.currentDirection, snake.newDirection.first});
  if (angle == changeDirectionAngles.end())
    return;
  moveSnakeParts(snake, angle->second);

  snake.currentPart++;
  // if all the parts have been moved to the new direction update current direction and stop animation
  if (snake.currentPart == snake.composition.size()) {
    snake.currentPart = 0;
    snake.currentDirection = snake.newDirection.first;
    transform.velocity = Vector2::normalize(snake.newDirection.second) *
                         transform.velocity.getMagnitude();
  }
}

void SnakeSystem::update(
    const float dt, const std::unordered_set<SDL_Scancode>& pressedKeys) const {
  auto const& entity = *entities.begin();
  auto& transform = ecsManager->getComponent<Transform2D>(entity);
  auto& snake = ecsManager->getComponent<Snake>(entity);

  // check if head hit border

  updateSnakeDirection(snake, pressedKeys);
  animateSnake(dt, snake, transform);

  if (snake.currentDirection != snake.newDirection.first)
    return;
  const auto movement = transform.velocity * dt;
  transform.position += movement;
  for (auto& [part, rect, angle] : snake.composition) {
    rect.x += movement.x;
    rect.y += movement.y;
  }
}

void SnakeSystem::render(SDL_Renderer* renderer) const {
  auto const& entity = *entities.begin();
  auto& snake = ecsManager->getComponent<Snake>(entity);
  for (int i = 0; i < snake.composition.size(); i++) {
    auto [part, positionRect, angle] = snake.composition.at(i);
    auto partRect = &snake.partsRect[part];
    auto flip = SDL_FLIP_NONE;
    if (snake.currentPart == i && (part == BODY || part == TAIL)) {
      partRect = &snake.partsRect[part == BODY ? BODY_ANGLED : TAIL_ANGLED];
      if (auto flipDirection = flipDirections.find(
              {snake.currentDirection, snake.newDirection.first});
          flipDirection != flipDirections.end())
        flip = flipDirection->second;
    }

    SDL_RenderCopyExF(renderer, snake.texture, partRect, &positionRect, angle,
                      nullptr, flip);
  }
}

void SnakeSystem::free() const {
  auto const& entity = *entities.begin();
  auto& snake = ecsManager->getComponent<Snake>(entity);
  SDL_DestroyTexture(snake.texture);
  snake.texture = nullptr;
}
