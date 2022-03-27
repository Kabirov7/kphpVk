//
// Created by Artur Kabirov on 27/3/22.
//

#ifndef KPHPVK_PARSER_H
#define KPHPVK_PARSER_H


#include <map>
#include "Lexer.h"
#include "AST.h"


class Parser {
private:
    Lexer lexer;
    Token currentToken;
    const std::map<char, short> PRIORITIES = {
            { ')', 2 },
            { '(', 2 },
            { '^', 4 },
            { '*', 5 },
            { '/', 5 },
            { '%', 5 },
            { '-', 6 },
            { '+', 6 },
            { '=', 16 },
            { ',', 17 }
    };

    bool IsOperator(Token::Type);

    short getPriority(char);
public:
    Parser(const Lexer &lexer, const Token &currentToken);

    void parser();
};


#endif //KPHPVK_PARSER_H
