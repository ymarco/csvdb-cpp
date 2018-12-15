#include "Create.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h> // for folder creation, only works on linux
#include <cerrno> // sys/stat.h uses errno instead of exceptions
#include <cstring> // used to convert the errno to strings
#include <nlohmann/json.hpp>
#include "../utils.h"


Create::Create(std::string name,
    bool enable_ifnexists,
    std::pair<char, std::string>* args,
    size_t args_cnt)
    : _name(name), _enable_ifnexists(enable_ifnexists), _args(args), _args_cnt(args_cnt){};

void Create::execute(){
    // create directory _name
    char status;
    //create dir called _name with standard premssions
    status = mkdir(_name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    //check for errors
    if(status==-1){
        //check what error is it
        if(errno == EEXIST && !_enable_ifnexists){
            std::cout << "you attempted to create an existing folder without the \"if not exists\" option\n";
            throw std::strerror(errno);
        }
        throw std::strerror(errno);
    }
    _create_json();
}


void Create::_create_json(){
    nlohmann::json j_schema;   
    //pushing arguments name and type into the json
    for(size_t i = 0; i < _args_cnt; i++){

        j_schema["schema"].push_back({{"field", _args[i].second},
                                      {"type", utils::dbvcode2name(_args[i].first)}});
    }
    const std::string path = _name + "/table.json";
    std::ofstream file(path.c_str());
    if(!file.is_open()){
        throw "error in opening table.json file";
    }
    file << j_schema;    
}