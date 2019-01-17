#include "Create.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../utils.h"




Create::Create(const std::string& name,
    bool enable_ifnexists, 
    std::shared_ptr<std::vector<std::pair<dbvar, std::string>>> args)
: _name(name), _enable_ifnexists(enable_ifnexists), _args(args){};

void Create::execute(){
    // create directory _name
    if(g_table_name_to_schema.find(_name) != g_table_name_to_schema.end()){ // existing table
        if(_enable_ifnexists){
            return;
        }else{
            throw /* CmdError */ "you tried to create an existing table without the ifnexists flag";
        }
    }
    
    filesys::path path(_name);
    filesys::create_directory(path);
    _create_json();
    // AND THE MOST IMPORTANT THING:
    g_table_name_to_schema.insert({_name, Schema(*_args)});
}


void Create::_create_json(){
    using json = nlohmann::json;
    json j_schema;
    j_schema["schema"] = json::array();
    //pushing arguments name and type into the json
    for(unsigned short i = 0, size = _args->size(); i < size; i++){
        j_schema["schema"][i]["field"] = /* "lol" */(*_args)[i].second;
        j_schema["schema"][i]["type"] = utils::dbvcode2name((*_args)[i].first);
    }
    const std::string path = _name + "/table.json";
    std::ofstream file(path.c_str());
    std::cout << "got json alright";
    if(!file.is_open()){
        throw "error in opening table.json file";
    }   
    file << j_schema;
};