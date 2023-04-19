#include "terminalManager.h"

#include <iostream>
#include <filesystem>

#include "logic/pathLogic.h"
#include "logic/inputLogic.h"
#include "logic/terminalLogic.h"


TerminalManager::TerminalManager()
{
};


void TerminalManager::start()
{
    this->init();
    this->listen();
    
};


void TerminalManager::init()
{
    pathLogic::initPath();
    terminalLogic::initTerminal();
};


void TerminalManager::listen()
{
    std::string wholeInputText;
    int inputCharacter;


    inputLogic::InputAction inputAction = inputLogic::InputAction(*this);

    std::cout << std::filesystem::current_path().string() << " > ";
    // todo need to know when to write the path again
    while ((inputCharacter = this->inputListener()) != EOF) {
        inputAction.actOnInputChar(inputCharacter);
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
};


int TerminalManager::inputListener()
{
    int (*inputListenerFromFactory)() = terminalLogic::getCharacterInputListener();
    return inputListenerFromFactory();
};
