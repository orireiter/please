#include "terminalManager.h"

#include <filesystem>
#include <iostream>

#include "logic/inputLogic.h"
#include "logic/pathLogic.h"
#include "logic/terminalLogic.h"

TerminalManager::TerminalManager() {
  this->isExitAttempt = false;
  this->currentIndexInInputString = 0;
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

  inputLogic::InputAction inputAction = inputLogic::InputAction(this);
  CompleteActiveLine line = this->getCompleteCurrentActiveLine();

  this->setCommandInitPosition();
  std::cout << line.prefix << line.textToIndex << line.textAfterIndex;
  while (this->isExitAttempt == false && (inputCharacter = this->inputListener()) != EOF) {
    inputAction.actOnInputChar(inputCharacter);
  };
};

int TerminalManager::inputListener() {
  int (*inputListenerFromFactory)() =
      terminalLogic::getCharacterInputListener();
  return inputListenerFromFactory();
};

void TerminalManager::appendCharactertoCurrentInputString(char character) {
  this->currentInputString.insert(this->currentIndexInInputString, 1, character);
  this->currentIndexInInputString += 1;
};

void TerminalManager::popOneCharacterBeforeIndexInInput() {
  this->currentInputString.erase(this->currentIndexInInputString-1, 1);
  this->moveCurrentIndexXStepsBack(1);
};

void TerminalManager::moveCurrentIndexXStepsBack(int x){
  this->currentIndexInInputString -= x;
};

void TerminalManager::resetCurrentIndexToEnd() {
  this->currentIndexInInputString = this->currentInputString.size();
};

void TerminalManager::clearCurrentInputString() {
  this->currentInputString.clear();
  this->currentIndexInInputString = 0;
};

void TerminalManager::setIsExitAttempt(bool isExit){
  this->isExitAttempt = isExit;
  return;
};

std::string TerminalManager::getCurrentInputString() {
  return this->currentInputString;
};

std::string TerminalManager::getCurrentPathDetailString() {
  std::string fullPath = "";

  std::string path =  std::filesystem::current_path().string();

  fullPath += path;
  
  return fullPath + " \u279C  ";
};

CompleteActiveLine TerminalManager::getCompleteCurrentActiveLine()
{
  std::string currentInput = this->getCurrentInputString();
  
  CompleteActiveLine line{
    .prefix=this->getCurrentPathDetailString(), 
    .textToIndex=currentInput.substr(0, this->currentIndexInInputString),
    .textAfterIndex=currentInput.substr(this->currentIndexInInputString)};
  return line;
};

terminalLogic::CursorPosition TerminalManager::getCursorPosition(){
  return terminalLogic::getCursorPosition();
};

void TerminalManager::setCursorPosition(terminalLogic::CursorPosition position) {
  terminalLogic::setCursorPosition(position);
};

terminalLogic::CursorPosition TerminalManager::getCommandInitPosition() {
  return this->commandInitPosition;
};

void TerminalManager::setCommandInitPosition(){
  terminalLogic::CursorPosition position = terminalLogic::getCursorPosition();
  this->commandInitPosition = position;
};
