#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

#include <utility>

#define t_ERROR        -1
#define t_EOF           0
#define t_KEYWORD 	    1
#define t_IDENTIFIER    2
#define t_LIT_STR   	3
#define t_LIT_NUM 	    4
#define t_OPERATOR 	    5

bool is_in_str_array(std::string* a,size_t size, std::string& s);
bool is_alphabetic_or_underscore(char x);
bool is_digit_or_dot_or_pm(char x);



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