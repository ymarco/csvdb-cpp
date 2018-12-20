#include "Parser.h"
#include <string>
#include "utils.h"
#include <vector>
#include <iostream>

std::string _types[4] = {
    "int",
    "varchar",
    "float",
    "timestamp"
};

void Parser::_expect_next_token(std::pair<char, std::string> expexted_token){
    _proceed_token();
    if(_curr_token != expexted_token){
        std::string errmsg = "unxpected token: expecting '" + expexted_token.second + "'"; 
        __tkzr.throw_err(errmsg);
    }
}

void Parser::_expect_next_token(char expected_token_type){
    _proceed_token();
    if(_curr_token.first != expected_token_type){
        std::string errmsg = "unxpected token: expecting token of type " + utils::tokentype2name(expected_token_type); 
        __tkzr.throw_err(errmsg);
    }  
}

Parser::Parser(Tokenizer& tkzr)
    :__tkzr(tkzr){}


void Parser::_proceed_token(){
    _curr_token = __tkzr.NextToken();
    std::cout << "token: " <<  (int)_curr_token.first << ", " << _curr_token.second << "\n";
}

std::pair<char, void*> Parser::Parse(){
    _proceed_token();
    if(_curr_token.first == t_EOF){
        return {cmd_NONE, nullptr};
    }
    if(_curr_token.first != t_KEYWORD){
        std::string errmsg = "first token was not of type keyword, token: " + _curr_token.second;
        throw errmsg;
    }
    // now determining what kind of command it is
    if(_curr_token.second == "create")      return _parse_create();
    //else if(toke.second = ...){...
}

std::pair<char, void*> Parser::_parse_create(){
    std::string name;
    bool enable_ifnexists = false;
    std::vector<std::pair<char, std::string>> args_vec; // array of (TYPE, name)
    std::string arg_name;
    char arg_type;
    // check for TABLE kw
    _expect_next_token({t_KEYWORD, "table"});
    std::cout << "\tgot table kw\n";
    // check for [IF NOT EXISTS]
    _proceed_token();
    if(_curr_token == std::pair<char, std::string>(t_KEYWORD, "if")){
        std::cout << "\t now in if not exists\n";
        _expect_next_token({t_KEYWORD, "not"});
        _expect_next_token({t_KEYWORD, "exists"});
        _proceed_token();
        enable_ifnexists = true;
    }
    //check for table_name
    if(_curr_token.first == t_IDENTIFIER){
    name = _curr_token.second;
    } else __tkzr.throw_err("KEYWORD _table_name not found");

    //check for "(" operator
    _expect_next_token({t_OPERATOR, "("});

    while(true){ // now reading arguments consisting of IDENTIFIER (name), KEYWORD (type), OPERATOR
        std::cout << "  getting name\n";
        _expect_next_token(t_IDENTIFIER); // argument name
        arg_name = _curr_token.second;
        std::cout << "  getting type\n";
        _expect_next_token(t_KEYWORD); // argument type
        if(utils::is_in_str_array(_types, 4, _curr_token.second)){
            char arg_type = utils::name2dbvar(_curr_token.second);
            args_vec.push_back({arg_type, arg_name});
        }else __tkzr.throw_err("parse error: invalid database type");
        std::cout << "  getting oper\n";
        _expect_next_token(t_OPERATOR);
        if(_curr_token.second == ","){ // more arguments
            continue;
        }
        if(_curr_token.second == ")"){ // end of arguments
            _proceed_token();
            break;
        }
        __tkzr.throw_err("unxpected token: expecting ',' or ')'");    
    }
    _expect_next_token(t_EOF);
    Create* res = new Create(name, enable_ifnexists, &args_vec[0], args_vec.size());
    return {cmd_CREATE, res};
}