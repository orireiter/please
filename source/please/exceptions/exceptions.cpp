#include "exceptions.h"


std::string PleaseExceptions::PleaseException::getExceptionMessage(PleaseExceptionsEnum exceptionType)
{
    switch (exceptionType) {
        case PleaseExceptions::PleaseExceptionsEnum::BAD_COMMAND_INPUT:
            return "Invalid command";
        case PleaseExceptions::PleaseExceptionsEnum::NO_PIPE_FROM_POPEN:
            return "Failed to open pipe from popen";
        default:
            return "Unknown exception";
    }
}
