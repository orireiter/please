#pragma once

#include <set>
#include <string>

#include "logic/terminalLogic.h"

struct InputSuffix {
  std::string text; 
  std::string backspaces; 
}; 

class TerminalManager {
 public:
  std::set<std::string> exitKeywords { "exit", "quit" };
  int currentIndexInInputString;
  
  TerminalManager();
  void start();

  int inputListener();

  void appendCharactertoCurrentInputString(char character);
  void popOneCharacterBeforeIndexInInput();
  void moveCurrentIndexXStepsBack(int x);
  void resetCurrentIndexToEnd();
  void clearCurrentInputString();
  void setIsExitAttempt(bool isExit);
  std::string getCurrentInputString();
  std::string getCompleteCurrentActiveLine(bool isAddInputAfterIndex = true);
  InputSuffix getInputSuffix();
  terminalLogic::CursorPosition getCursorPosition();

 private:
  bool isExitAttempt;
  std::string currentInputString;

  void init();
  void listen();
  std::string getCurrentPathDetailString();
};
