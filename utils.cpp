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