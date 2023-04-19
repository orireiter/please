#pragma once


class TerminalManager
{
public:
  TerminalManager();
  void start();

  int inputListener();

private: 
  void init();
  void listen();
};
