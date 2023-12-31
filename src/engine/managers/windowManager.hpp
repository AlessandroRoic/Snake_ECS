#ifndef SNAKE_ECS_WINDOWMANAGER_HPP
#define SNAKE_ECS_WINDOWMANAGER_HPP
#include <SDL_system.h>

enum WINDOWED_MODE{
  WINDOW,
  FULLSCREEN,
  BORDERLESS_WINDOW,
};

class WindowManager {
  SDL_Window* window{};
  const char* windowTitle = "";
  int windowWidth = 1920;
  int windowHeight = 1080;

 public:
  bool init(WINDOWED_MODE mode);
  SDL_Window* getWindow() const;
  void setWindow(SDL_Window* window);
  const char* getWindowTitle() const;
  void setWindowTitle(const char* windowTitle);
  int getWindowWidth() const;
  void setWindowWidth(int windowWidth);
  int getWindowHeight() const;
  std::pair<int, int> getWindowDimensions();
  void setWindowHeight(int windowHeight);
  void setWindowMode(WINDOWED_MODE mode) const;
  void destroyWindow();
};

#endif  //SNAKE_ECS_WINDOWMANAGER_HPP
