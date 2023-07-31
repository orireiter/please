#pragma once

namespace terminalLogic {

struct CursorPosition {
    int column;
    int row;
};

void initTerminal();

CursorPosition getCursorPosition();
int (*getCharacterInputListener())();
};  // namespace terminalLogic
