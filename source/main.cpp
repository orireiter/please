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
    initPath();
    initTerminal();
};


int main()
{   
    init();
    int (*inputListener)() = getCharacterInputListener();

    std::string wholeInputText;
    int inputCharacter;


    std::cout << std::filesystem::current_path().string() << " > ";
    while ((inputCharacter = inputListener()) != EOF) {
        if (inputCharacter == '\t') {
            break;
        }
        
        char asChar = static_cast<char>(inputCharacter);
        wholeInputText.push_back(asChar);
        std::cout << asChar;
    };

    std::cout << wholeInputText << std::endl;
    // std::cout << inputListener() << std::endl;
    // std::cout << std::filesystem::current_path().string() << std::endl;

    // char* input = std::find(std::begin(specialKeyboardEvents), std::end(specialKeyboardEvents), '\n');
    // if (input != std::end(specialKeyboardEvents)) {
    //     SpecialKeyboardEvent ori = static_cast<SpecialKeyboardEvent>(*input);
    //     std::cerr << "Found at position " << static_cast<char>(ori);
    // }
    // else {
    //     std::cerr << "Not found" << std::endl;
    // };

    return 0;
};
