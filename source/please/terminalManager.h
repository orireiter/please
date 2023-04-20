#pragma once

#include <string>


class TerminalManager
{
public:
  TerminalManager();
  void start();

  int inputListener();
  
  void appendCharactertoCurrentInputString(char character);
  void popLastCharacterInCurrentInputString();
  std::string getCurrentInputString();


private: 
  std::string currentInputString;

  void init();
  void listen();
};