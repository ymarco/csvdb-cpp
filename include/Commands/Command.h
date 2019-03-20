#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <exception>

// base class for all command types
class Command{
public:
    const char* type = "empty";
    virtual void execute(){std::cout << "empty command executed\n";};
    virtual ~Command(){};

    enum CmdTypes: char{
        cmd_NONE,
        cmd_CREATE,
        cmd_LOAD,
        cmd_DROP,
        cmd_SELECT,
    };

};


class CmdError : public std::exception {
private:
    std::string _msg;
public:
    CmdError(std::string msg);
    const char * what() const throw ();
};


#endif