#include "Command.h"

CmdError::CmdError(std::string msg): _msg(msg){};

const char* CmdError::what() const throw() {
    return _msg.c_str();
}
