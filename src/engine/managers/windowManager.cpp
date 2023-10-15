#include "windowManager.hpp"
#include "../debuggers/logger.hpp"

bool WindowManager::init(WINDOWED_MODE mode) {
  SDL_WindowFlags windowFlag;

  if (mode == WINDOWED_MODE::BORDERLESS_WINDOW) {
    windowFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
  } else if (mode == WINDOWED_MODE::FULLSCREEN) {
    windowFlag = SDL_WINDOW_FULLSCREEN;
  } else {
    windowFlag = SDL_WINDOW_SHOWN;
  }

  setWindow(SDL_CreateWindow(getWindowTitle(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, getWindowWidth(),
                             getWindowHeight(), windowFlag));

  if (!window) {
    Logger::logMessage("Window not loaded", true);
    return false;
  }

  return true;
}

SDL_Window* WindowManager::getWindow() const {
  return window;
}

void WindowManager::setWindow(SDL_Window* window) {
  WindowManager::window = window;
}

const char* WindowManager::getWindowTitle() const {
  return windowTitle;
}

void WindowManager::setWindowTitle(const char* windowTitle) {
  WindowManager::windowTitle = windowTitle;
}

int WindowManager::getWindowWidth() const {
  return windowWidth;
}

void WindowManager::setWindowWidth(int windowWidth) {
  WindowManager::windowWidth = windowWidth;
}

int WindowManager::getWindowHeight() const {
  return windowHeight;
}

void WindowManager::setWindowHeight(int windowHeight) {
  WindowManager::windowHeight = windowHeight;
}

void WindowManager::setWindowMode(WINDOWED_MODE mode) {
  SDL_WindowFlags windowFlag;

  if (mode == WINDOWED_MODE::BORDERLESS_WINDOW) {
    windowFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
  } else if (mode == WINDOWED_MODE::FULLSCREEN) {
    windowFlag = SDL_WINDOW_FULLSCREEN;
  } else {
    windowFlag = SDL_WINDOW_SHOWN;
  }

  if (SDL_SetWindowFullscreen(window, windowFlag) < 0) {
    Logger::logMessage("Unable to go fullscreen", true);
  }
}
void WindowManager::destroyWindow() {
  SDL_DestroyWindow(window);
  window = nullptr;
}
