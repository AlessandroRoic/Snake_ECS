#ifndef SNAKE_ECS_RESOURCEMANAGER_HPP
#define SNAKE_ECS_RESOURCEMANAGER_HPP
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <nlohmann/json.hpp>
#include "../../game/components/sprite.hpp"
#include "../math/vector2.hpp"

class ResourceManager {
  TTF_Font* globalFont{};
  SDL_Color textColor = {255, 255, 255};

 public:
  SDL_Color getTextColor() const;
  void setTextColor(const SDL_Color& text_color);

  TTF_Font* getGlobalFont() const;
  void setGlobalFont(TTF_Font* font);
  void closeGlobalFont();
  static SDLSprite loadSDL2Renderable(SDL_Renderer* renderer, const char* path,
                                      Vector2 position);
  static SDL_Texture* loadSDLTexture(SDL_Renderer* renderer, const char* path);
  static nlohmann::json_abi_v3_11_2::basic_json<> loadJSON(const char* path);
  static TTF_Font* loadFont(const char* path, int fontSize);
};

#endif  //SNAKE_ECS_RESOURCEMANAGER_HPP
