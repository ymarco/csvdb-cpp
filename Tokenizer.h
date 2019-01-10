#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <utility>
#include "utils.h"
#include <vector>
#include <exception>

class ParseError : public std::exception {
private:
    std::string _msg;
public:
    ParseError(std::string msg);
    const char * what() const throw ();
};





class Tokenizer{
private:
    std::string _text;
    unsigned short _text_len; 
    unsigned short _curser = 0; // index to _text
    unsigned short _row = 0;
    unsigned short _column = 0;
    std::vector<std::string> __text_split_by_lines;

    char _cur();
    void _proceed_cur();
    std::string _err_info();
    std::pair<char, std::string> _get_identifier_or_keyword();
    std::pair<char, std::string> _get_lit_str();
    std::pair<char, std::string> _get_lit_num(); // note that this returns a STRING containing the num
    std::pair<char, std::string> _get_operator();
    void __skip_wspace();
    void __skip_comment();
    void __skip_till_eol();
    bool __eof();


public:
    Tokenizer(std::string text);
    std::pair<char, std::string> NextToken(); //returns token kind, token value
    void throw_err(std::string msg);
};

#endif