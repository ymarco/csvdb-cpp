#include "Tokenizer.h"
#include "Parser.h"
#include "Commands/Command.h"
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

        if(line == ";"){
            return res;
        }
        res += line;
        res += "\n";
        std::cout << "       ";  
    }
}


int main(){
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
            Command* cmd = parser.Parse();
            std::cout<<"executing!\n";
            cmd->execute();
            delete cmd;  
            
        }catch(ParseException &e){
            std::cout << "error cought\n";
            std::cout << e.what();
        }
        
    }
}
