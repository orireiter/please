#include <iostream>
#include <cstdio>

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


void inputLogic::InputAction::actOnDeleteSequence()
{
    this->terminalManager.popLastCharacterInCurrentInputString();
    std::cout << '\b';
    std::cout << " ";
    std::cout << '\b';
};


void inputLogic::InputAction::actOnEnterSequence()
{
    std::cout << std::endl;
    try {
        const int buffer_size = 256;
        char buffer[buffer_size];

        // Open the command as a pipe and check for errors
        FILE* pipe = popen(this->terminalManager.getCurrentInputString().c_str(), "r");
        if (!pipe) {
            std::cerr << "Error: could not open pipe for command." << std::endl;
            return;
        }

        // Read the command output in chunks of buffer_size bytes and append them to the result string
        std::vector<char> result;
        while (fgets(buffer, buffer_size, pipe) != nullptr) {
            result.insert(result.end(), buffer, buffer + std::strlen(buffer));
        };

        pclose(pipe);
        std::cout << result.data();

        this->terminalManager.clearCurrentInputString();
    }
    catch (const std::exception) {
        std::cerr << "Error: could not open pipe for command." << std::endl;
        std::cout << this->terminalManager.getCurrentInputString();
    }
    
};

void inputLogic::InputAction::actOnInputChar(int inputChar)
{
    switch (inputChar)
    {
    case 10:
        this->actOnEnterSequence();
        break;
    case 9:
        // run completion for input
        std::cout << "tab" << std::endl;
        break;
    case 27:
        this->actOnEscapeSequence();
        break;
    case 127:
        this->actOnDeleteSequence();
        break;
    default:
        char asChar = static_cast<char>(inputChar);
        this->terminalManager.appendCharactertoCurrentInputString(asChar);

        std::cout << asChar;
        break;
    };
};
