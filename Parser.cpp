#include <string>
#include <vector>
#include <iostream>
#include "Parser.h"
#include "utils.h"
#include <memory>

std::string _types[4] = {
    "int",
    "varchar",
    "float",
    "timestamp"
};

void Parser::_expect_next_token(std::pair<TokenType, std::string> expexted_token){
    _proceed_token();
    if(_curr_token != expexted_token){
        std::string errmsg = "unxpected token: expecting '" + expexted_token.second + "'"; 
        __tkzr.throw_err(errmsg);
    }
}

void Parser::_expect_next_token(TokenType expected_token_type){
    _proceed_token();
    if(_curr_token.first != expected_token_type){
        std::string errmsg = "unxpected token: expecting token of type " + Tokenizer::tokentype2name(expected_token_type); 
        __tkzr.throw_err(errmsg);
    }  
}

Parser::Parser(Tokenizer& tkzr)
    :__tkzr(tkzr){}


void Parser::_proceed_token(){
    _curr_token = __tkzr.NextToken();
    //std::cout << _curr_token.first << "," << _curr_token.second << "\n";
}

Command* Parser::Parse(){
    _proceed_token();
    if(_curr_token.first == t_EOF){
        Command* nullcmd = new Command;
        return nullcmd;
    }
    if(_curr_token.first != t_KEYWORD){
        __tkzr.throw_err("first token was not a keyword");
    }
    // now determining what kind of command it is
    std::string cmd = _curr_token.second;
    if(cmd == "create")     return _parse_create();
    if(cmd == "drop")       return _parse_drop();
    // if(cmd = ...) ...
    Command* nullcmd = new Command;
    return nullcmd;
}

Command* Parser::_parse_create(){
    std::string name;
    bool enable_ifnexists = false;
    auto args_vec_ptr = std::make_shared<std::vector<std::pair<dbvar, std::string>>>(); // array of (TYPE, name)
    // check for TABLE kw
    _expect_next_token({t_KEYWORD, "table"});
    // check for [IF NOT EXISTS]
    _proceed_token();
    if(_curr_token == std::pair<TokenType, std::string>({t_KEYWORD, "if"})){
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
        _expect_next_token(t_IDENTIFIER); // argument name
        std::string arg_name = _curr_token.second;
        _expect_next_token(t_KEYWORD); // argument type
        if(!utils::is_in_str_array(_types, 4, _curr_token.second)){ // not a valid type
            __tkzr.throw_err("parse error: insecondid database type");
        }
        dbvar arg_type = utils::name2dbvar(_curr_token.second);
        std::cout << "type generated: " << (int)arg_type << "\n";
        args_vec_ptr->emplace_back(arg_type, arg_name);
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
    Create* res = new Create(name, enable_ifnexists, args_vec_ptr);
    return res;
}

Command* Parser::_parse_drop(){
    bool enable_ifexists = false;
    std::string name;
    // check for table kw
    _expect_next_token({t_KEYWORD, "table"});
    // check for [IF EXISTS]
    _proceed_token();
    if(_curr_token == std::pair<TokenType, std::string>({t_KEYWORD, "if"})){
        _expect_next_token({t_KEYWORD, "exists"});
        enable_ifexists = true;
        _proceed_token();
    }
    //check for table_name
    if(_curr_token.first == t_IDENTIFIER){
    name = _curr_token.second;
    } else __tkzr.throw_err("KEYWORD _table_name not found");

    _expect_next_token(t_EOF);
    Drop* res = new Drop(name, enable_ifexists);
    return res;

}