#include "Create.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../utils.h"




Create::Create(std::string name,
    bool enable_ifnexists, 
    std::vector<std::pair<char, std::string>>& args,
    unsigned short args_cnt
): _name(name), _enable_ifnexists(enable_ifnexists), _args(args), _args_cnt(args_cnt){};

void Create::execute(){
    std::cout << "executing create cmd\n";
    // create directory _name
    filesys::path path(_name);
    filesys::create_directory(path);
    std::cout << "createing json\n";
    _create_json();
}

Create::~Create(){
    delete &(_args[0]);
}


void Create::_create_json(){
    using json = nlohmann::json;
    json j_schema;
    j_schema["schema"] = json::array();
    std::cout << "created empty array\n";
    //pushing arguments name and type into the json
    for(unsigned short i = 0; i < _args_cnt; i++){
        std::cout << "pushing argument field #" << i << "\n";
        j_schema["schema"][i]["field"] = /* "lol" */_args[i].second;
        std::cout << "pushing argument type #" << i << "\n";
        std::cout << "type: " << (int)_args[i].first << "\n";
        j_schema["schema"][i]["type"] = utils::dbvcode2name(_args[i].first);

    }
    std::cout << "finished loading thibgs to json\n";
    const std::string path = _name + "/table.json";
    std::ofstream file(path.c_str());
    std::cout << "got json alright";
    if(!file.is_open()){
        throw "error in opening table.json file";
    }   
    file << j_schema;    
};