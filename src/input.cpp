#include "input.h"
#include <iostream>


std::string input::get_terminal_cmd(){
    std::string res;
    std::string line;
    std::cout << "\ncsvdb> ";

    while(1){
        std::getline(std::cin, line);

        if(line == ";"){
            return res;
        }else if(line == "exit" || line == "exit()"){
			return "exit";
		}
        res += line;
        res += "\n";
        std::cout << "       ";  
    }
}

std::vector<std::string> input::get_file_cmd(const std::string& file_path)
{
	std::vector<std::string> res;
	std::ifstream file;
	file.open(file_path);
	std::string text;
	text.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	std::string command;
	bool comment_mod = false;
	for (size_t i = 0; i < text.size(); i++){
		if (text[i] == '\n'){
			comment_mod = false;
			continue;
		}
		if (comment_mod)
			continue;
		if (text[i] == '-' && text[i + 1] == '-'){
			comment_mod = true;
			continue;
		}
		if (text[i] == ';'){
			res.push_back(command);
			command = "";
			continue;
		}
		command += text[i];
	}
	return res;
}