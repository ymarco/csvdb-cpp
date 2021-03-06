#ifndef CREATE_H
#define CREATE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Command.h"
#include "../Schema.h"
#include "../filesys.h"
#include "../utils.h"

extern std::unordered_map<std::string, Schema*> g_schema_name_to_ptr;

class Create: public Command{
private:
    const std::string _name;
    const bool _enable_ifnexists;
    std::shared_ptr<std::vector<std::pair<dbvar, std::string>>> _args; //represented as (type, std::string name)
    void _create_json();
    
public:
    Create(const std::string& name,
        bool enable_ifnexists, 
        std::shared_ptr<std::vector<std::pair<dbvar, std::string>>> args
    );
    const char *type = "create";
    void execute() override;
};

#endif