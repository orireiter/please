#pragma once

#include "../terminalManager.h"

namespace inputLogic {
class InputAction {
 private:
  TerminalManager* terminalManagerPtr;

  void actOnEscapeSequence();
  void actOnDeleteBackspaceSequence();
  void actOnEnterSequence();
  void actOnChar224Sequence();
  void actOnNormalKeyPress(int inputCharAsInt);
  void actOnLeftArrow();
  void actOnRightArrow();

  void reWriteActiveLine();

 public:
  InputAction(TerminalManager* terminalManagerPtr);
  void actOnInputChar(int inputChar);
};
};  // namespace inputLogic
