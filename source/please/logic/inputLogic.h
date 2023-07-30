#pragma once

#include "../terminalManager.h"

namespace inputLogic {
class CommandHistory {
 private:
  int currentCommandIndex;
  std::vector<std::string> cachedCommandHistory;

  void getCommandHistory();

 public:
  CommandHistory();
  std::string getLastCommandStartingWithPrefix(std::string commandPrefix);
  std::string getNextCommandStartingWithPrefix(std::string commandPrefix);
};
class InputAction {
 private:
  TerminalManager terminalManager;
  CommandHistory commandHistory;

  void actOnEscapeSequence();
  void actOnDeleteSequence();
  void actOnEnterSequence();

 public:
  InputAction(TerminalManager terminalManager);
  void actOnInputChar(int inputChar);
};
};  // namespace inputLogic
