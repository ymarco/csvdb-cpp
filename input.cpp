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
        }
        res += line;
        res += "\n";
        std::cout << "       ";  
    }
}
