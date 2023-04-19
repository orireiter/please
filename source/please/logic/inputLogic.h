#pragma once

#include "../terminalManager.h"

namespace inputLogic {
    class InputAction
    {
        private:
            TerminalManager terminalManager;

            void actOnEscapeSequence();

        public:
            InputAction(TerminalManager terminalManager);
            void actOnInputChar(int inputChar);
    };
};
