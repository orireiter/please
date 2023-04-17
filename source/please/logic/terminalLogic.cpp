#include <stdio.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
#endif

#include "terminalLogic.h"


void initTerminal()
{

}


int (*getCharacterInputListener())()
{
#ifdef _WIN32
    return &getch;
#else
    return &getchar;
#endif
};
