#include "pathLogic.h"

#include <filesystem>
#include <iostream>
#include <string>

std::optional<std::string> getHomePath() {
#ifdef _WIN32
  char *homePath = nullptr;
  size_t sz = 0;
  _dupenv_s(&homePath, &sz, "USERPROFILE");
#else
  const char *homePath = getenv("HOME");
#endif
  return (homePath && homePath != nullptr) ? std::make_optional<std::string>(homePath) : std::nullopt;
};

std::string getInitPath() {
  std::optional<std::string> homePath = getHomePath();
  return homePath.value_or(std::filesystem::current_path().string());
};

void pathLogic::initPath() {
  std::string initPath = getInitPath();
  std::filesystem::current_path(initPath);
};
