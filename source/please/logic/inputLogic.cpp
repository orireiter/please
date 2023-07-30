#include "inputLogic.h"

#include <cstdio>
#include <iostream>
#include <sstream>

#include "../exceptions/exceptions.h"
#include "../terminalManager.h"

#ifdef _WIN32
  #include <vector>
  #define popen _popen
  #define pclose _pclose
#endif

#ifdef _WIN32
enum class KeyboardButtonEnum {
  ENTER = 13,
  TAB = 9,
  ESCAPE = 27,
  DELETE_BACKSPACE = 8,
  CHAR_224 = 224
};

void inputLogic::InputAction::actOnEscapeSequence() {
  // todo implement if needed
  return;
};

void inputLogic::InputAction::actOnChar224Sequence() {
  int secondInput = this->terminalManagerPtr->inputListener();
  switch (secondInput) {
    case 72:
      std::cout << "up" << std::endl;
      break;
    case 75:
      this->actOnLeftArrow();
      break;
    case 77:
      std::cout << "right" << std::endl;
      break;
    case 80:
      std::cout << "down" << std::endl;
      break;
    default:
      this->actOnInputChar(secondInput);
      break;
  };
};
#else
enum class KeyboardButtonEnum {
  ENTER = 10,
  TAB = 9,
  ESCAPE = 27,
  DELETE_BACKSPACE = 127,
  CHAR_224 = 224
};

void inputLogic::InputAction::actOnEscapeSequence() {
  int secondInput = this->terminalManagerPtr->inputListener();
  if (secondInput != 91) {
    this->actOnInputChar(secondInput);
    return;
  };

  switch (this->terminalManagerPtr->inputListener()) {
    case 65:
      std::cout << "up" << std::endl;
      break;
    case 66:
      std::cout << "down" << std::endl;
      break;
    case 67:
      std::cout << "right" << std::endl;
      break;
    case 68:
      this->actOnLeftArrow();
    default:
      this->actOnInputChar(secondInput);
      break;
  };
};

void inputLogic::InputAction::actOnChar224Sequence() {
  this->actOnNormalKeyPress(224);
  return;
};

#endif

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

  if (result.back() != '\n') {
    result.insert(result.end(), '\n');
  };

  std::string asString(result.begin(), result.end());
  return asString;
};

inputLogic::InputAction::InputAction(TerminalManager* terminalManagerPtr) {
  this->terminalManagerPtr = terminalManagerPtr;
};

void inputLogic::InputAction::actOnDeleteBackspaceSequence() {
  if (this->terminalManagerPtr->currentIndexInInputString == 0 || this->terminalManagerPtr->getCurrentInputString().empty()) {
    return;
  };

  this->terminalManagerPtr->popOneCharacterBeforeIndexInInput();

  InputSuffix suffix = this->terminalManagerPtr->getInputSuffix();
  std::cout << '\b' << suffix.text << " \b" << suffix.backspaces;
};

void inputLogic::InputAction::actOnEnterSequence() {
  std::cout << std::endl;

  std::string currentInput = this->terminalManagerPtr->getCurrentInputString();

  if (this->terminalManagerPtr->exitKeywords.contains(currentInput)) {
    this->terminalManagerPtr->setIsExitAttempt(true);
    return;
  };

  try {
    std::string commandOutput = runCommand(currentInput);
    std::cout << commandOutput;
    this->terminalManagerPtr->clearCurrentInputString();
  } catch (const PleaseExceptions::PleaseException& e) {
    this->terminalManagerPtr->resetCurrentIndexToEnd();
    // todo rewrite path (and current command?) + in case of posix we need to show this error, mac shows it even when there's nothing here
  };
  std::cout << this->terminalManagerPtr->getCompleteCurrentActiveLine();
};

void inputLogic::InputAction::actOnNormalKeyPress(int inputCharAsInt){
  char asChar = static_cast<char>(inputCharAsInt);
  this->terminalManagerPtr->appendCharactertoCurrentInputString(asChar);

  InputSuffix suffix = this->terminalManagerPtr->getInputSuffix();
  std::cout << asChar << suffix.text << suffix.backspaces;
};

void inputLogic::InputAction::actOnLeftArrow(){
  if (this->terminalManagerPtr->currentIndexInInputString == 0 || this->terminalManagerPtr->getCurrentInputString().empty()) {
    return;
  };

  std::cout << '\b';
  this->terminalManagerPtr->moveCurrentIndexXStepsBack(1);
};

void inputLogic::InputAction::actOnInputChar(int inputChar) {
  KeyboardButtonEnum keyboardButton{inputChar};
  switch (keyboardButton) {
    case KeyboardButtonEnum::ENTER:
      this->actOnEnterSequence();
      break;
    case KeyboardButtonEnum::TAB:
      // todo run completion for input
      std::cout << "tab" << std::endl;
      break;
    case KeyboardButtonEnum::ESCAPE:
      this->actOnEscapeSequence();
      break;
    case KeyboardButtonEnum::DELETE_BACKSPACE:
      this->actOnDeleteBackspaceSequence();
      break;
    case KeyboardButtonEnum::CHAR_224:
      this->actOnChar224Sequence();
      break;
    default:
      this->actOnNormalKeyPress(inputChar);
      break;
  };
};
