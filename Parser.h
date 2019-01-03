#ifndef PARSER_H
#define PARSER_H

#include <utility>
#include "Tokenizer.h"
#include "Commands/Command.h"
#include "Commands/Create.h"
/*
#include "Commands/Load.h"s 
#include "Commands/Drop.h"
*/

class Parser{
private:
    Tokenizer __tkzr;
    void _proceed_token();
    std::pair<char, std::string> _curr_token;
    void _expect_next_token(std::pair<char, std::string> token);
    void _expect_next_token(char expected_token_type);    
    Command* _parse_create();
    /*
    Command* _parse_load();
    Command* _parse_drop();
    Command* _parse_select()
    */
public:
    Parser(Tokenizer& tkzr);
    Command* Parse();

};



#endif