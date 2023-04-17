#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <iterator>

#include "please/logic/pathLogic.h"
#include "please/logic/terminalLogic.h"
#include "please/data_access/models.h"


void init()
{
    setInitPath();
    initTerminal();
};


int main()
{   
    init();

    int (*inputListener)() = getCharacterInputListener();

    std::cout << inputListener() << std::endl;
    std::cout << std::filesystem::current_path().string() << std::endl;

    char* input = std::find(std::begin(specialKeyboardEvents), std::end(specialKeyboardEvents), '\n');
    if (input != std::end(specialKeyboardEvents)) {
        SpecialKeyboardEvent ori = static_cast<SpecialKeyboardEvent>(*input);
        std::cerr << "Found at position " << static_cast<char>(ori);
    }
    else {
        std::cerr << "Not found" << std::endl;
    };

    return 0;
};


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