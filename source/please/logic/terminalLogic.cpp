#include <conio.h>

#include "terminalLogic.h"


int (*getCharacterInputListener())() {
    #ifdef _WIN32
    	return &getch;
	#else
		return &getchar;
	#endif
};
