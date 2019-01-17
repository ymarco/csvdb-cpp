#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "../Schema.h"
#include "Command.h"

extern std::unordered_map<std::string, Schema> g_table_name_to_schema;

class Load: public Command{
private:
    std::string _src; //from
    std::string _dst; //to
    unsigned short _ignore_lines = 0;
	std::vector<std::string> split(std::string txt);

public:
    Load(std::string src, std::string dst, unsigned int ignore_lines);
    void execute() override;
};



#endif