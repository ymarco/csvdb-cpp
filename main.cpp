#include "Tokenizer.h"
#include "Commands/Create.h" //only for testing
#include "Parser.h"
#include <utility> // temp
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
        std::cout << "       ";  
    }
}


int main(){
    
    std::cout << "hello world\n";
    /*
    std::string name("movies");
    std::pair<char,std::string> args[] = {{1, "id"}, {3, "title"}};
    Create create(name, true, args, 2);
    //create.execute();
    */
    
    std::string cmd;
    while(1){
        cmd = get_usr_cmd();
        Tokenizer tkzr(cmd);
        try{
            Parser parser(tkzr);
            auto cmd = parser.Parse();
            std::cout << cmd.first;
        }catch(ParseException &e){
            std::cout << "error cought\n";
            std::cout << e.what();
        }
        
    }
}
