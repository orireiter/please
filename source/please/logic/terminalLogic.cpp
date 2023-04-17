#include "terminalLogic.h"

#ifdef _WIN32
    #include <conio.h>

    void initTerminal()
    {
        clrscr();
    };

    int (*getCharacterInputListener())()
    {
        return &getch;
    };
#else
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>
    #include <iostream>

    void initTerminal()
    {
        std::cout << "\033[H\033[2J\033[3J" ;
        // save current terminal settings
        struct termios terminalSettings;
        tcgetattr(STDIN_FILENO, &terminalSettings);
        terminalSettings.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echoing
        tcsetattr(STDIN_FILENO, TCSANOW, &terminalSettings);

    };

    int (*getCharacterInputListener())()
    {
        return &getchar;
    };
#endif
