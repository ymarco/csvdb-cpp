#ifndef CREATE_H
#define CREATE_H

#include <string>
#include <utility>

class Create{
private:
    const std::string _name;
    const bool _enable_ifnexists;
    std::pair<char, std::string>* _args; //represented as (type, name)
    size_t _args_cnt;
    void _create_json();
    
public:
    Create(std::string name,
        bool enable_ifnexists, 
        std::pair<char, std::string>* args,
        size_t args_cnt);
    void execute();
};

#endif