#include <iostream>
#include <string>

#include "Tokenizer.h"
#include "Parser.h"
#include "input.h"
#include "Commands/Command.h"
//#include "Schema.h"

//std::vector<Schema> Tables;


int main(){
    /*
    std::string name("movies");
    std::pair<char,std::string> args[] = {{1, "id"}, {3, "title"}};
    Create create(name, true, args, 2);
    //create.execute();
    */
    
    std::string cmd;
    while(1){
        cmd = input::get_terminal_cmd();
        Tokenizer tkzr(cmd);
        try{
            Parser parser(tkzr); // creating parser
            Command* cmd = parser.Parse(); // parsing
            std::cout<<"executing!\n";
            cmd->execute();
            delete cmd;  
            
        }catch(ParseError &e){
            std::cout << "error cought\n";
            std::cout << e.what();
        }
        
    }
}