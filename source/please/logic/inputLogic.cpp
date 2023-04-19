#include <iostream>

#include "inputLogic.h"
#include "../terminalManager.h"


inputLogic::InputAction::InputAction(TerminalManager terminalManager)
{
    this->terminalManager = terminalManager;
};


void inputLogic::InputAction::actOnEscapeSequence()
{
    int secondInput = this->terminalManager.inputListener();
    if (secondInput != 91) {
        this->actOnInputChar(secondInput);
        return;
    };

    switch (this->terminalManager.inputListener())
    {
    case 65:
        std::cout << "up" << std::endl;
        break;
    case 66:
        std::cout << "down" << std::endl;
        break;
    default:
        this->actOnInputChar(secondInput);
        break;
    };
};




void inputLogic::InputAction::actOnInputChar(int inputChar)
{
    switch (inputChar)
    {
    case 10:
        std::cout << "enter" << std::endl;
        // run operation for whole input
        break;
    case 9:
        // run completion for input
        std::cout << "tab" << std::endl;
        break;
    case 27:
        std::cout << "escape" << std::endl;
        // escape
        actOnEscapeSequence();
        break;
    default:
        break;
    };
};
