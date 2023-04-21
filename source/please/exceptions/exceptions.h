#pragma once

#include <stdexcept>
#include <string>

namespace PleaseExceptions {
enum class PleaseExceptionsEnum { BAD_COMMAND_INPUT, NO_PIPE_FROM_POPEN };

class PleaseException : public std::runtime_error {
 public:
  PleaseException(PleaseExceptionsEnum exceptionType)
      : std::runtime_error(getExceptionMessage(exceptionType)),
        type(exceptionType){};

  const PleaseExceptionsEnum type;

 private:
  static std::string getExceptionMessage(PleaseExceptionsEnum exceptionType);
};
};  // namespace PleaseExceptions
