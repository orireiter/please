#pragma once

#include <set>
#include <string>

class TerminalManager {
 public:
  std::set<std::string> exitKeywords { "exit", "quit" };
  TerminalManager();
  void start();

  int inputListener();

  void appendCharactertoCurrentInputString(char character);
  void popLastCharacterInCurrentInputString();
  void clearCurrentInputString();
  void setIsExitAttempt(bool isExit);
  std::string getCurrentInputString();
  std::string getCompleteCurrentActiveLine();

 private:
  bool isExitAttempt;
  std::string currentInputString;

  void init();
  void listen();
  std::string getCurrentPathDetailString();
};
