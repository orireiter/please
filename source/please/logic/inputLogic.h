#pragma once

#include "../terminalManager.h"

namespace inputLogic {
class InputAction {
 private:
  TerminalManager terminalManager;

  void actOnEscapeSequence();
  void actOnDeleteBackspaceSequence();
  void actOnEnterSequence();
  void actOnChar224Sequence();
  void actOnNormalKeyPress(int inputCharAsInt);

 public:
  InputAction(TerminalManager terminalManager);
  void actOnInputChar(int inputChar);
};
};  // namespace inputLogic
