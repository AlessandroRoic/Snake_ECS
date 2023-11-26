#include "snakeSystem.hpp"
#include <SDL_render.h>
#include <eventManager.hpp>
#include <map>
#include "../components/snake.hpp"
#include "../components/transform.hpp"

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

void SnakeSystem::init(const std::shared_ptr<EcsManager>& _ecsManager,
                       EventManager* _eventManager, const int _screenWidth,
                       const int _screenHeight) {
  ecsManager = _ecsManager;
  eventManager = _eventManager;
  screenWidth = _screenWidth;
  screenHeight = _screenHeight;
  Signature snakeSignature;
  snakeSignature.set(ecsManager->getComponentType<Snake>());
  ecsManager->setSystemSignature<SnakeSystem>(snakeSignature);
}

bool isRectOutOfBounds(const SDL_FRect* rect, const int screenWidth,
                       const int screenHeight) {
  return rect->x + rect->w <= rect->w || rect->x >= static_cast<float>(screenWidth) - rect->w ||
         rect->y + rect->h <= rect->w || rect->y >= static_cast<float>(screenHeight) - rect->w;
}

void updateSnakeDirection(Snake& snake,
                          const std::unordered_set<SDL_Scancode>& pressedKeys) {
  // If no keys are pressed skip update of velocity
  if (pressedKeys.begin() == pressedKeys.end())
    return;

  const auto direction = scanCodeToDirection.find(*pressedKeys.begin());

  auto& head = snake.composition.at(0);
  const auto validMove =
      changeDirectionAngles.find({head.currentDirection, direction->first});

  if (direction == scanCodeToDirection.end() ||
      validMove == changeDirectionAngles.end())
    return;

  // If it is a mapped key, and it has changed direction update the velocity
  head.newDirection = direction->first;
}

void animateSnake(const float dt, Snake& snake) {
  for (int i = 0; i < snake.composition.size(); i++) {
    auto& [part, positionRect, angle, currentDirection, newDirection, isAngled,
           animationCounter] = snake.composition.at(i);
    auto& partAxis = currentDirection == SDL_SCANCODE_UP ||
                             currentDirection == SDL_SCANCODE_DOWN
                         ? positionRect.y
                         : positionRect.x;
    const auto partDirection = currentDirection == SDL_SCANCODE_DOWN ||
                                       currentDirection == SDL_SCANCODE_RIGHT
                                   ? 1.0f
                                   : -1.0f;
    if (currentDirection == newDirection) {
      partAxis += dt * partDirection * snake.speed;
      // if animation done pass to next
      if (animationCounter >= 0) {
        animationCounter += dt * 1 * snake.speed;
      }
      if (animationCounter >= positionRect.w) {
        if (i + 1 < snake.composition.size())
          snake.composition.at(i + 1).newDirection = currentDirection;
        animationCounter = -1;
      }
    } else {
      if (isAngled)
        isAngled = false;
      angle =
          changeDirectionAngles.find({currentDirection, newDirection})->second;
      currentDirection = newDirection;
      animationCounter = 0;
      if (i + 1 < snake.composition.size())
        snake.composition.at(i + 1).isAngled = true;
    }
  }
}

void SnakeSystem::update(
    const float dt, const std::unordered_set<SDL_Scancode>& pressedKeys) const {
  auto const& entity = *entities.begin();
  auto& snake = ecsManager->getComponent<Snake>(entity);

  if (isRectOutOfBounds(&snake.composition.at(0).positionRect, screenWidth,
                        screenHeight)) {
    const Event event{GAME_END};
    eventManager->fire(&event);
    return;
  }

  updateSnakeDirection(snake, pressedKeys);
  animateSnake(dt, snake);
}

void SnakeSystem::render(SDL_Renderer* renderer) const {
  auto const& entity = *entities.begin();
  auto& snake = ecsManager->getComponent<Snake>(entity);
  for (auto& [part, positionRect, angle, currentDirection, newDirection,
              isAngled, _] : snake.composition) {
    auto partRect = &snake.partsClip[part];
    auto flip = SDL_FLIP_NONE;
    if (isAngled && (part == BODY || part == TAIL)) {
      partRect = &snake.partsClip[part == BODY ? BODY_ANGLED : TAIL_ANGLED];
      auto flipDirection =
          flipDirections.find({currentDirection, newDirection});
      if (flipDirection != flipDirections.end()) {
        flip = flipDirection->second;
      }
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
