#include "utils.h"
#include <iostream>


bool utils::is_in_str_array(std::string* a, unsigned short size, const std::string& s){
    for(unsigned short i=0; i<size; i++){
        if(a[i] == s)
            return true;
    }
    return false;
}
bool utils::is_alphabetic_or_underscore(char x){
    if(isalpha(x) || x==*"_")
        return true;
    return false;
}
bool utils::is_digit_or_dot_or_pm(char x){
    if(isdigit(x) || x==*"." || x==*"+" || x==*"-")
        return true;
    return false;
}

std::string utils::dbvcode2name(char code){
    std::cout << "type : " << code << "\n";
    switch(code){
        case dbv_INT:        return "int";
        case dbv_FLOAT:      return "float";
        case dbv_VARCHAR:    return "varchar";
        case dbv_TIMESTAMP:  return "timestamp";
        default: return "unknown" /* throw "dbvcode2name: invalid code given" */;
    }
}

std::string utils::tokentype2name(char type){
    switch(type){
        case t_EOF:         return "EOF";
        case t_IDENTIFIER:  return "IDENTIFIER";
        case t_KEYWORD:     return "KEYWORD";
        case t_LIT_NUM:     return "LIT_NUM";
        case t_LIT_STR:     return "LIT_STR";
        case t_OPERATOR:    return "OPERATOR";
    }
}

char utils::name2dbvar(std::string vcode){
    if(vcode == "int") return dbv_INT;
    if(vcode == "float") return dbv_FLOAT;
    if(vcode == "varchar") return dbv_VARCHAR;
    if(vcode == "timestamp") return dbv_TIMESTAMP;
    std::string errmsg = "utils::name2dbvar: invalid type given: " + vcode;
    throw errmsg;
}