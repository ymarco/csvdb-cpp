//#include "Parser.h"
#include "Tokenizer.h"
#include <string>
#include <iostream>

bool debug_mode = true;

std::string get_usr_cmd(){
    std::string res;
    std::string line;
    std::cout << "\ncsvdb> ";

    while(1){
        std::getline(std::cin, line);
        size_t endpos = line.find(";");

        if(endpos!=std::string::npos){
            res += line.substr(0, endpos);
            return res;
        }
        res += line;
        res += "\n";
        
    }
}


int main(){
    std::cout << "hello world\n";
    
    std::string cmd;
    while(1){
        cmd = get_usr_cmd();
        Tokenizer tkzr(cmd);
        while(1){
            auto token = tkzr.NextToken();
            std::cout << (int)token.first << ", " << token.second << "\n";
            if(token.first == t_EOF){
                break;
            }
        }
    }
}
