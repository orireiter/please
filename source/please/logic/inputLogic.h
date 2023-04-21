#pragma once

#include "../terminalManager.h"

namespace inputLogic {
class InputAction {
 private:
  TerminalManager terminalManager;

  void actOnEscapeSequence();
  void actOnDeleteSequence();
  void actOnEnterSequence();

 public:
  InputAction(TerminalManager terminalManager);
  void actOnInputChar(int inputChar);
};
};  // namespace inputLogic
