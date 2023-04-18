#include <iostream>

#include "inputLogic.h"


void actOnEscapeSequence(int (*inputListener)()) {
    int secondInput = inputListener();
    if (secondInput != 91) {
        return;
    };

    switch (inputListener())
    {
    case 65:
        std::cout << "up" << std::endl;
        break;
    case 66:
        std::cout << "down" << std::endl;
        break;
    default:
        break;
    }
}


void actOnInputChar(int inputChar, int (*inputListener)())
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
        // escape
        actOnEscapeSequence(inputListener);
        break;
    default:
        break;
    }
};
