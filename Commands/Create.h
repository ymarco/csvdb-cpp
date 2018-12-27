#ifndef CREATE_H
#define CREATE_H

#include <string>
#include <utility>
#include "Command.h"

class Create: public Command{
private:
    const std::string _name;
    const bool _enable_ifnexists;
    std::pair<char, std::string>* _args; //represented as (type, name)
    unsigned short _args_cnt;
    void _create_json();
    
public:
    Create(std::string name,
        bool enable_ifnexists, 
        std::pair<char, std::string>* args,
        unsigned short args_cnt
    );
    const char *type = "create";
    void execute() override;
};

#endif