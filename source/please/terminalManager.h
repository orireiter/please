#pragma once


class TerminalManager
{
public:
  TerminalManager();
  void start();

private: 
  void init();
  void listen();

  int inputListener();
};
