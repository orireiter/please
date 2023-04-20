#include "terminalManager.h"

#include <iostream>
#include <filesystem>

#include "logic/pathLogic.h"
#include "logic/inputLogic.h"
#include "logic/terminalLogic.h"


TerminalManager::TerminalManager()
{
    this->currentInputString = std::string();
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
    int inputCharacter;

    inputLogic::InputAction inputAction = inputLogic::InputAction(*this);

    std::cout << std::filesystem::current_path().string() << " > ";
    // todo need to know when to write the path again
    while ((inputCharacter = this->inputListener()) != EOF) {
        inputAction.actOnInputChar(inputCharacter);
    };
};


int TerminalManager::inputListener()
{
    int (*inputListenerFromFactory)() = terminalLogic::getCharacterInputListener();
    return inputListenerFromFactory();
};


void TerminalManager::appendCharactertoCurrentInputString(char character)
{
    this->currentInputString.push_back(character);
};

void TerminalManager::popLastCharacterInCurrentInputString()
{
    this->currentInputString.pop_back();
};

std::string TerminalManager::getCurrentInputString()
{
    return this->currentInputString;
};
