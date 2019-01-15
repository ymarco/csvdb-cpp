#ifndef UTILS_H
#define UTILS_H

// A set of functions and constants that dont belong to a specific class

// t_ for tokenizer
//dbv_ for database variable 
enum dbvar: char{
    dbv_INT,
    dbv_FLOAT,
    dbv_VARCHAR,
    dbv_TIMESTAMP
};

#include <string>

namespace utils{

    bool is_in_str_array(std::string* a, unsigned short size, const std::string& s);
    bool is_alphabetic_or_underscore(char x);
    bool is_digit_or_dot_or_pm(char x);

    std::string dbvcode2name(char code);
    dbvar name2dbvar(std::string vname);
}

#endif