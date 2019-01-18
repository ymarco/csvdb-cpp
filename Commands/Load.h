#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../Schema.h"
#include "Command.h"

extern std::unordered_map<std::string, Schema> g_table_name_to_schema;

class Load: public Command{
private:
    std::string _src; //from
    std::string _dst; //to
    unsigned short _ignore_lines = 0;
	void _split(const std::string& txt, std::string* res);

public:
    Load(std::string src, std::string dst, unsigned int ignore_lines);
    void execute() override;
};



#endif