// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <iterator>

#include "please/data_access/models.h"
#include "please/logic/pathLogic.h"


std::optional<std::string> getHomePath() {
    const char *homePathEnvName = "USERPROFILE";
    const char *homePath = getenv(homePathEnvName);
    return (homePath) ? std::make_optional<std::string>(homePath) : std::nullopt;
}

std::string getPath() {
    std::optional<std::string> homePath = getHomePath();
    return homePath.value_or(std::filesystem::current_path().string());
}


int main()
{   
    Path pathManager;
    std::cout << pathManager.getCurrentPath();
    std::string pathString = getPath();
    std::cout << pathString;
    
    char* input = std::find(std::begin(specialKeyboardEvents), std::end(specialKeyboardEvents), '\n');
    if (input != std::end(specialKeyboardEvents)) {
        SpecialKeyboardEvent ori = static_cast<SpecialKeyboardEvent>(*input);
        std::cerr << "Found at position " << static_cast<char>(ori);
    }
    else {
        std::cerr << "Not found" << std::endl;
    };

    return 0;
}


/*
#include <iostream>
#include <cstdio>

int main() {
    std::string input;
    int c;

    std::cout << "Enter input (press tab to end): ";

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            break;
        }
        input.push_back(static_cast<char>(c));
    }

    std::cout << "Input was: " << input << std::endl;

    return 0;
}

*/