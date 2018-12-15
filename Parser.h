#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include "Commands/Create.h"

#include <utility>

class Parser{
    Parser(Tokenizer tkzr);
    std::pair<char, void*> Parse();

};



#endif