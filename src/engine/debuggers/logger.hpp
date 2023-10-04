#ifndef SNAKE_ECS_LOGGER_HPP
#define SNAKE_ECS_LOGGER_HPP

#include <string>
namespace Logger {
void logMessage(const std::string& message, bool isError = false);
}

#endif  //SNAKE_ECS_LOGGER_HPP
