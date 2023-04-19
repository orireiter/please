#include <string>
#include <filesystem>
#include <iostream>

#include "pathLogic.h"


std::optional<std::string> getHomePath() {
	#ifdef _WIN32
    	const char *homePathEnvName = "USERPROFILE";
	#else
		const char *homePathEnvName = "HOME";
	#endif

    const char *homePath = getenv(homePathEnvName);
    return (homePath) ? std::make_optional<std::string>(homePath) : std::nullopt;
};

std::string getInitPath() {
    std::optional<std::string> homePath = getHomePath();
    return homePath.value_or(std::filesystem::current_path().string());
};


void pathLogic::initPath() {
	std::string initPath = getInitPath();
	std::filesystem::current_path(initPath);
};
