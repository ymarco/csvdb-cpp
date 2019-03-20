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


enum TokenType: char{
    t_EOF,
    t_KEYWORD,
    t_IDENTIFIER,
    t_LIT_STR,
    t_LIT_NUM,
    t_OPERATOR
};


class Tokenizer{
private:
    std::string _text;
    unsigned short _text_len; 
    unsigned short _curser = 0; // index to _text
    unsigned short _row = 0;
    unsigned short _column = 0;
    std::vector<std::string> __text_split_by_lines;

    char _cur() const{ return _text[_curser];};
    void _proceed_cur();
    std::string _err_info() const;
    std::pair<TokenType, std::string> _get_identifier_or_keyword();
    std::pair<TokenType, std::string> _get_lit_str();
    std::pair<TokenType, std::string> _get_lit_num(); // note that this returns a STRING containing the num, e.g. "34" and NOT 34
    std::pair<TokenType, std::string> _get_operator();
    void __skip_wspace();
    void __skip_comment();
    void __skip_till_eol();
    bool __eof();

public:
    Tokenizer(std::string text);
    std::pair<TokenType, std::string> NextToken(); //returns token kind, token value
    void throw_err(const std::string& msg) const;
    static std::string tokentype2name(TokenType type); 
};


#endif