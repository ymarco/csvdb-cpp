#include "utils.h"

bool utils::is_in_str_array(std::string* a, size_t size, std::string& s){
    for(size_t i=0; i<size; i++){
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
    switch(code){
        case 1: return "int";
        case 2: return "float";
        case 3: return "varchar";
        case 4: return "timestamp";
        default: throw "dbvcode2name: invalid code given";
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