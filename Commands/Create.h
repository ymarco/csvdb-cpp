#ifndef CREATE_H
#define CREATE_H

#include "../filesys.h"
#include <string>
#include <utility>
#include <vector>
//#include "../Schema.h"
#include "Command.h"

//extern std::vector<Schema> Tables;

class Create: public Command{
private:
    const std::string _name;
    const bool _enable_ifnexists;
    std::vector<std::pair<char, std::string>> _args; //represented as (char type, std::string name)
    unsigned short _args_cnt;
    void _create_json();
    
public:
    Create(std::string name,
        bool enable_ifnexists, 
        std::vector<std::pair<char, std::string>>& args,
        unsigned short args_cnt
    );
    ~Create();
    const char *type = "create";
    void execute() override;
};

#endif