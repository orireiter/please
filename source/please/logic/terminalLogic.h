#pragma once

namespace terminalLogic {

struct CursorPosition {
    int column;
    int row;
};

void initTerminal();

CursorPosition getCursorPosition();
void setCursorPosition(CursorPosition position);
int (*getCharacterInputListener())();
};  // namespace terminalLogic
