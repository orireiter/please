#pragma once

#include <set>
#include <string>

#include "logic/terminalLogic.h"

struct CompleteActiveLine {
  std::string prefix; 
  std::string textToIndex;
  std::string textAfterIndex; 
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
  CompleteActiveLine getCompleteCurrentActiveLine();

  terminalLogic::CursorPosition getCursorPosition();
  void setCursorPosition(terminalLogic::CursorPosition position);

  terminalLogic::CursorPosition getCommandInitPosition();
  void setCommandInitPosition();

 private:
  bool isExitAttempt;
  std::string currentInputString;
  terminalLogic::CursorPosition commandInitPosition;

  void init();
  void listen();
  std::string getCurrentPathDetailString();
};
