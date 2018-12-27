#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
// base class for all command types
class Command{
public:
    const char* type = "empty";
    virtual void execute(){std::cout << "empty command executed\n";};
    virtual ~Command(){};
};


#endif