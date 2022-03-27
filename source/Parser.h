//
// Created by Artur Kabirov on 27/3/22.
//

#ifndef KPHPVK_PARSER_H
#define KPHPVK_PARSER_H


#include "Lexer.h"
#include "AST.h"

class Parser {
    Lexer lexer;
    Token currentToken;
};


#endif //KPHPVK_PARSER_H
