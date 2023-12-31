#include "logger.hpp"
#include <SDL_error.h>
#include <SDL_log.h>
#include <format>

void Logger::logMessage(const std::string& message, const bool isError) {
  if (isError) {
    const std::string msg = std::format("({}): {}", message, SDL_GetError());
    SDL_Log("%s", msg.c_str());
    return;
  }
  std::printf("%s \n", message.c_str());
}
