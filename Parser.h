#ifndef PARSER_H
#define PARSER_H

#include <utility>
#include "Tokenizer.h"
#include "Commands/Create.h"
#include "Commands/Load.h"
#include "Commands/Drop.h"


class Parser{
private:
    Tokenizer __tkzr;
    void _proceed_token();
    std::pair<char, std::string> _curr_token;
    void _expect_next_token(std::pair<char, std::string> token);
    void _expect_next_token(char expected_token_type);    
    std::pair<char, void*> _parse_create();
    /*
    std::pair<char, void*> _parse_load();
    std::pair<char, void*> _parse_drop();
    std::pair<char, void*> _parse_select()
    */
public:
    Parser(Tokenizer& tkzr);
    std::pair<char, void*> Parse();

};



#endif