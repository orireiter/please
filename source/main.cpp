#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <iterator>

#include "please/data_access/models.h"
#include "please/logic/pathLogic.h"





int main()
{   
    setInitPath();
    std::cout << std::filesystem::current_path().string();

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