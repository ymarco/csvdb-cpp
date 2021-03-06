#include "Tokenizer.h"
#include <algorithm> //used for lowercasing
#include <sstream>
#include <iostream>


std::string t_keywords[34] = {
        "select",
        "from",
        "where",
        "avg",
        "sum",
        "min",
        "max",
        "load",
        "drop",
        "order",
        "by",
        "group",
        "into",
        "outfile",
        "as",
        "having",
        "data",
        "infile",
        "table",
        "ignore",
        "lines",
        "null",
        "int",
        "float",
        "varchar",
        "timestamp",
        "desc",
        "asc",
        "and",
        "or",
        "not",
        "create",
        "if",
        "exists",
    };

std::string t_operators[11] = {
        ",",
        "(",
        ")",
        "<",
        "<=",
        "<>",
        "=",
        ">=",
        ">",
        ";",
        "*",
};

Tokenizer::Tokenizer(std::string text)
: _text_len(text.size()), _text(text){
    std::stringstream st_text(_text);
    std::string segment;
    while(std::getline(st_text, segment)){
        __text_split_by_lines.push_back(segment);
    }
}

std::pair<TokenType, std::string> Tokenizer::NextToken(){
    std::string token_val;

    __skip_wspace();
    __skip_comment();
    __skip_wspace();
    // token checking
    if(__eof()){
        return {t_EOF, ""};
    }

    if(utils::is_alphabetic_or_underscore(_cur())){
        return _get_identifier_or_keyword();
    }

    if(_cur() == *"\""){
        return _get_lit_str();
    }

    if( utils::is_digit_or_dot_or_pm(_cur()) ){
        return _get_lit_num();
    }
    // if we got here, it means that our current token is not
    // an end-of-file, keyword, identifier, or literal
    // so it must be an operator (or an error)
    
    return _get_operator();    
}

// returns the identifier or keyword in current text position
std::pair<TokenType, std::string> Tokenizer::_get_identifier_or_keyword(){
    std::string token_val;
    while( !__eof() && ( utils::is_alphabetic_or_underscore(_cur()) || isdigit(_cur()) ) ){
        token_val.push_back(_cur());
        _proceed_cur();
    }
    std::string token_val_lower = token_val;
    std::transform(token_val_lower.begin(), token_val_lower.end(), token_val_lower.begin(), ::tolower);
    //std::cout << "lower: "<<token_val_lower << ", normal: " << token_val <<"\n";
    if(utils::is_in_str_array(t_keywords, 34, token_val_lower))
        return {t_KEYWORD, token_val_lower};
    return {t_IDENTIFIER, token_val};
}

std::pair<TokenType, std::string> Tokenizer::_get_lit_str(){
    std::string token_val;
    if(_cur()!=*"\"")
       throw_err("Tokenizer: _get_lit_str was called, but there wasnt a \" in the _cur");
    _proceed_cur(); // now we are inside the str lit
    while(!__eof()){
        if(_cur()==*"\""){ // found the closing "
            _proceed_cur(); // going past the " and exiting the str lit
            return {t_LIT_STR, token_val};
        }
        token_val.push_back(_cur());
        _proceed_cur();
    }
    //if we got here it means that we reached eof without finding the closing "
    throw_err("Tokenizer: did not find the closing \"");
}

std::pair<TokenType, std::string> Tokenizer::_get_lit_num(){
    unsigned short start_pos = _curser; //used for error printing
    std::string token_val;
    if(!utils::is_digit_or_dot_or_pm(_cur()))
       throw_err("Tokenizer: _get_lit_num was called, but the \"number\" didnt start with digit,.,+,- in the _cur");
    bool is_dotted = false;
    while(!__eof()){
        if( isdigit(_cur()) ){
            token_val.push_back(_cur());
        }else if(_cur() == *"."){
            if(is_dotted){              
               throw_err("Tokenizer: _get_lit_num found 2 dots without exponent");
            }else{
                is_dotted = true;
                token_val.push_back(_cur());
            }
        }else if(isspace(_cur())){ // end of number
            return {t_LIT_NUM, token_val};
        }else{
           throw_err("Tokenizer: a thing started with a number and than changed into somethng else invalid");
        }
        _proceed_cur();
    }
    // if we got here it means we reached eof and the numbe hasnt ended
    return {t_LIT_NUM, token_val};
}

std::pair<TokenType, std::string> Tokenizer::_get_operator(){
    std::string token_val(1, _cur());
    _curser++;
    if(!__eof()){
        std::string double_token_val = token_val + _cur();
        if(utils::is_in_str_array(t_operators, 11, token_val+_cur())){ // double digit operator like >=
            return {t_OPERATOR, double_token_val};
        }
    }
    // not a double digit op
    _curser--;
    _proceed_cur();
    if(utils::is_in_str_array(t_operators, 11, token_val)){
        return {t_OPERATOR, token_val};
    }
    if(_text_len = (_curser+1)){//file ends on next char, meaning theres no place for a second operator char
       throw_err("Tokenizer: type not found");
    }
    //now we know that there IS one more char, and the combination could
    token_val.push_back(_cur());
    _proceed_cur();
    if(utils::is_in_str_array(t_operators, 11, token_val)){
        return {t_OPERATOR, token_val};
    }
    // we ran out of options... 
   throw_err("Tokenizer: type not found");
}


void Tokenizer::_proceed_cur(){
    if(_cur()==*"\n"){
        _row++;
        _column = 0;
    }else{
        _column ++;
    }
    _curser++;
    //std::cout << "_row: " << _row << ", _column: " << _column << std::endl;

}

void Tokenizer::__skip_wspace(){
    while(!__eof() && isspace(_cur())){
        _proceed_cur();
    };
}

void Tokenizer::__skip_comment(){
    if((_curser+1)==_text_len){
        //there is 1 char left before eof, so there is no chance for a comment
        return; 
    }
    if(_text.substr(_curser, 2)=="--"){
        __skip_till_eol();
    }
}

void Tokenizer::__skip_till_eol(){
    while(!(__eof())){
        if(_cur() == *"\n"){
            _proceed_cur(); // going past the \n
            return;
        }
        _proceed_cur();
    }

}

bool Tokenizer::__eof(){
    if(_text_len == _curser)
        return true;
    return false;
}

void Tokenizer::throw_err(const std::string& msg) const{
    //std::cout << "throw_err: column is " << _column << "\n";
    std::string info_and_msg = _err_info() + msg + "\n";
    throw ParseError(info_and_msg);
}

std::string Tokenizer::_err_info() const{
    std::string res(__text_split_by_lines[_row]);
    std::string spaces_indent(_column-1, *"_");
    //std::cout << spaces_indent << " <these were spaces indent\n";
    std::string indent = spaces_indent + "^^^";
    //std::cout << "coluns: "<< _column << "\n";
    res += "\n" + indent + "\n";
    return res;
}

ParseError::ParseError(std::string msg): _msg(msg){}

const char* ParseError::what() const throw() {
    return _msg.c_str();
}


std::string Tokenizer::tokentype2name(TokenType type){
    switch(type){
        case t_EOF:         return "EOF";
        case t_IDENTIFIER:  return "IDENTIFIER";
        case t_KEYWORD:     return "KEYWORD";
        case t_LIT_NUM:     return "LIT_NUM";
        case t_LIT_STR:     return "LIT_STR";
        case t_OPERATOR:    return "OPERATOR";
    }
}
