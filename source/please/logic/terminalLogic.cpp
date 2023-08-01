#include "terminalLogic.h"

#include <stdio.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

void makeTerminalSupportUTF8() {
  int utf8CodePageIdentifier = 65001;
  SetConsoleOutputCP(utf8CodePageIdentifier);
};

void terminalLogic::initTerminal() { 
  makeTerminalSupportUTF8();
  system("cls"); 
};

int (*terminalLogic::getCharacterInputListener())() { return &_getch; };
#else
#include <termios.h>
#include <unistd.h>

#include <iostream>

void terminalLogic::initTerminal() {
  // clear the terminal
  std::cout << "\033[H\033[2J\033[3J";

  // save current terminal settings
  struct termios terminalSettings;
  tcgetattr(STDIN_FILENO, &terminalSettings);
  terminalSettings.c_lflag &=
      ~(ICANON | ECHO);  // disable canonical mode and echoing
  tcsetattr(STDIN_FILENO, TCSANOW, &terminalSettings);
};

int (*terminalLogic::getCharacterInputListener())() { return &getchar; };
#endif


terminalLogic::CursorPosition terminalLogic::getCursorPosition(){
  std::cout << "\033[6n";
  int input, column, row;

  std::string output = "";

  int (*inputListenerFromFactory)() = terminalLogic::getCharacterInputListener();
  while ((input = inputListenerFromFactory()) != 'R') {
    output.push_back(static_cast<char>(input));
  };

  sscanf_s(output.c_str(), "\033[%d;%d", &row, &column);
  return terminalLogic::CursorPosition{.column=column, .row=row};
};