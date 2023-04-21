#include "inputLogic.h"

#include <cstdio>
#include <iostream>
#include <sstream>

#include "../exceptions/exceptions.h"
#include "../terminalManager.h"

std::string runCommand(std::string commandString) {
  const int buffer_size = 256;
  char buffer[buffer_size];

  FILE* pipe = popen(commandString.c_str(), "r");
  if (!pipe) {
    std::cerr << "Error: could not open pipe for command." << std::endl;
    throw PleaseExceptions::PleaseException(
        PleaseExceptions::PleaseExceptionsEnum::NO_PIPE_FROM_POPEN);
  };

  std::vector<char> result;
  while (fgets(buffer, buffer_size, pipe) != nullptr) {
    result.insert(result.end(), buffer, buffer + std::strlen(buffer));
  };

  pclose(pipe);

  if (result.empty()) {
    throw PleaseExceptions::PleaseException(
        PleaseExceptions::PleaseExceptionsEnum::BAD_COMMAND_INPUT);
  };

  return result.data();
};

inputLogic::InputAction::InputAction(TerminalManager terminalManager) {
  this->terminalManager = terminalManager;
};

void inputLogic::InputAction::actOnEscapeSequence() {
  int secondInput = this->terminalManager.inputListener();
  if (secondInput != 91) {
    this->actOnInputChar(secondInput);
    return;
  };

  switch (this->terminalManager.inputListener()) {
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

void inputLogic::InputAction::actOnDeleteSequence() {
  this->terminalManager.popLastCharacterInCurrentInputString();
  std::cout << '\b';
  std::cout << " ";
  std::cout << '\b';
};

void inputLogic::InputAction::actOnEnterSequence() {
  std::cout << std::endl;

  try {
    std::string commandOutput =
        runCommand(this->terminalManager.getCurrentInputString());
    std::cout << commandOutput.data();
    this->terminalManager.clearCurrentInputString();
  } catch (const PleaseExceptions::PleaseException& e) {
    // rewrite path (and current command?)
  };
};

void inputLogic::InputAction::actOnInputChar(int inputChar) {
  switch (inputChar) {
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
