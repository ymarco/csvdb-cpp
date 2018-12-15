#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

#include <utility>
#include "utils.h"

class Tokenizer{
private:
    std::string _text;
    size_t _text_len; 
    size_t _curser; // index to _text
    /* implement later:
    size_t _cur_line_start_index;
    size_t _line_number;
    */
    

    inline char _cur(){return _text[_curser];};
    std::pair<char, std::string> _get_identifier_or_keyword();
    std::pair<char, std::string> _get_lit_str();
    std::pair<char, std::string> _get_lit_num(); // note that this returns a string containing the num
    std::pair<char, std::string> _get_operator();
    void __skip_wspace();
    void __skip_comment();
    void __skip_till_eol();
    bool __eof();


public:
    Tokenizer(std::string& text);
    std::pair<char, std::string> NextToken(); //returns token kind, token value

};

#endif