#ifndef UTILS_H
#define UTILS_H

// A set of functions and constants that dont belong to a specific class

// t_ for tokenizer
#define t_ERROR        -1
#define t_EOF           0
#define t_KEYWORD 	    1
#define t_IDENTIFIER    2
#define t_LIT_STR   	3
#define t_LIT_NUM 	    4
#define t_OPERATOR 	    5

//dbv_ for database variable 
#define dbv_INT         1
#define dbv_FLOAT       2
#define dbv_VARCHAR     3
#define dbv_TIMESTAMP   4


#include <string>

namespace utils{
    bool is_in_str_array(std::string* a,size_t size, std::string& s);
    bool is_alphabetic_or_underscore(char x);
    bool is_digit_or_dot_or_pm(char x);

    std::string dbvcode2name(char code);
}

#endif