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
    if(g_schema_name_to_ptr.find(_name) != g_schema_name_to_ptr.end()){ // existing table
        if(_enable_ifnexists){
            return;
        }else{
            throw CmdError("you tried to create an existing table without the ifnexists flag");
        }
    }

    filesys::path path(_name);
    filesys::create_directory(path);
    _create_json();
    // AND THE MOST IMPORTANT THING:
    Schema* s = new Schema(*_args);
    std::cout << "create line 28" << std::endl;
    TEST(auto y = s->columns[0]);
    std::cout << "create line 30" << std::endl;
    g_schema_name_to_ptr.insert({_name, s});   
    std::cout << "create line 32" << std::endl;
    TEST(auto x = g_schema_name_to_ptr.at(_name)->columns[0].type;);

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
    std::cout << "got json alright\n";
    file << j_schema;
};