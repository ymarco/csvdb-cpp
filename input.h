#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <ostream>
#include <fstream>
#include <vector>

namespace input{
    std::string get_terminal_cmd();
	std::vector<std::string> get_file_cmd(std::string file_path);
}
#endif