#ifndef LOAD_H
#define LOAD_H

#include <string>
#include "Command.h"

class Load: public Command{
private:
    std::string _src;
    std::string _dst;
    unsigned short _ignore_lines = 0;

public:
    Load(std::string src, std::string dst, unsigned short ignore_lines);
    void execute();
};



#endif