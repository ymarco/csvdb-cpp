#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <iostream>
// A set of functions and constants that dont belong to a specific class

enum dbvar: char{
    dbv_INT,
    dbv_FLOAT,
    dbv_VARCHAR,
    dbv_TIMESTAMP
};
union dbv{
    int64_t i;
    double f;
    uint64_t t;
};
const int64_t null_int = std::numeric_limits<int64_t>::min();
const double null_float = -0.0;
const uint64_t null_timestamp = std::numeric_limits<uint64_t>::min(); 

#define DEBUG

#ifdef DEBUG
    #define TEST(x)\
        std::cout << "TEST: Func " << __func__ << ", file " << __FILE__\
        << ", line " << __LINE__ <<": " << std::flush;\
        x;\
        std::cout << "seccessful.\n";
#else
    #define TEST(x) x;
#endif

#include <string>

namespace utils{

    bool is_in_str_array(std::string* a, unsigned short size, const std::string& s);
    bool is_alphabetic_or_underscore(char x);
    bool is_digit_or_dot_or_pm(char x);

    std::string dbvcode2name(char code);
    dbvar name2dbvar(std::string vname);
}

#endif