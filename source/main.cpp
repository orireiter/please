#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "please/terminalManager.h"


int main()
{   
    TerminalManager pleaseTerminal = TerminalManager();
    pleaseTerminal.start();
    return 0;
};
