#include "terminalManager.h"

#include <filesystem>
#include <iostream>

#include "logic/inputLogic.h"
#include "logic/pathLogic.h"
#include "logic/terminalLogic.h"

TerminalManager::TerminalManager() {
  this->currentInputString = std::string();
};

void TerminalManager::start() {
  this->init();
  this->listen();
};

void TerminalManager::init() {
  pathLogic::initPath();
  terminalLogic::initTerminal();
};

void TerminalManager::listen() {
  int inputCharacter;

  inputLogic::InputAction inputAction = inputLogic::InputAction(*this);

  std::cout << this->getCompleteCurrentActiveLine();
  while ((inputCharacter = this->inputListener()) != EOF) {
    inputAction.actOnInputChar(inputCharacter);
  };
};

int TerminalManager::inputListener() {
  int (*inputListenerFromFactory)() =
      terminalLogic::getCharacterInputListener();
  return inputListenerFromFactory();
};

void TerminalManager::appendCharactertoCurrentInputString(char character) {
  this->currentInputString.push_back(character);
};

void TerminalManager::popLastCharacterInCurrentInputString() {
  this->currentInputString.pop_back();
};

void TerminalManager::clearCurrentInputString() {
  this->currentInputString.clear();
};

std::string TerminalManager::getCurrentInputString() {
  return this->currentInputString;
};

std::string TerminalManager::getCurrentPathDetailString() {
  std::string fullPath = "";

  std::string path =  std::filesystem::current_path().string();

  fullPath += path;
  
  return fullPath + " \u279C ";
};

std::string TerminalManager::getCompleteCurrentActiveLine()
{
  std::string activeLine;
  activeLine += this->getCurrentPathDetailString();
  
  std::string currentInput = this->getCurrentInputString();
  if (currentInput.empty() == false) {
      activeLine += currentInput;
  };
  
  return activeLine;
};