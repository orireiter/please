#include "inputLogic.h"

#include <cstdio>
#include <iostream>

#include "../exceptions/exceptions.h"
#include "../terminalManager.h"

// todo make this function a generator so i could then print each line
// individually
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

void inputLogic::CommandHistory::getCommandHistory() {
  try {
    std::string historyCommandString = "fc -l -1";
    std::string commandHistory = runCommand(historyCommandString);
    std::cout << commandHistory;
  } catch (const PleaseExceptions::PleaseException& e) {
    std::cout << e.what();
  };
};

inputLogic::CommandHistory::CommandHistory(){};

std::string inputLogic::CommandHistory::getLastCommandStartingWithPrefix(
    std::string commandPrefix) {
  this->getCommandHistory();
  return "";
};

std::string inputLogic::CommandHistory::getNextCommandStartingWithPrefix(
    std::string commandPrefix) {
  return "";
};

inputLogic::InputAction::InputAction(TerminalManager terminalManager) {
  this->terminalManager = terminalManager;
  this->commandHistory = CommandHistory();
};

void inputLogic::InputAction::actOnEscapeSequence() {
  int secondInput = this->terminalManager.inputListener();
  if (secondInput != 91) {
    this->actOnInputChar(secondInput);
    return;
  };

  this->commandHistory.getLastCommandStartingWithPrefix("");

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
  if (this->terminalManager.getCurrentInputString().empty()) {
    return;
  };

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
  std::cout << this->terminalManager.getCompleteCurrentActiveLine();
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
