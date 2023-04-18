#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <iostream>
#include <filesystem>
#include <iterator>

#include "please/logic/pathLogic.h"
#include "please/logic/inputLogic.h"
#include "please/logic/terminalLogic.h"


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
        actOnInputChar(inputCharacter, inputListener);
        continue;
        
        std::cout << inputCharacter << std::endl;
        if (inputCharacter == '\t') {
            break;
        }
        
        char asChar = static_cast<char>(inputCharacter);
        wholeInputText.push_back(asChar);
        std::cout << asChar;
    };

    std::cout << wholeInputText << std::endl;
    return 0;
};
