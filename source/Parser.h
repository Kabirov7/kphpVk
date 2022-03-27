//
// Created by Artur Kabirov on 27/3/22.
//

#ifndef KPHPVK_PARSER_H
#define KPHPVK_PARSER_H


#include <map>
#include "Lexer.h"
#include "AST.h"
#include <queue>


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

//    String + Int/Float число преобразуется в строку
//    "Hello" + "!" => "Hello!"
//    "Hello" + "43" => "Hello43"
//    String - Int/Float строка преобразуется в целое или дробное число, а если строка не является числовой (2) то будто бы она "0" .
//    "World" - 42 = -42
//    "134" - 42 = 92
//    "134" + 42 = 13442
//    Float (+, -) Int целое число преобразуется в дробное.

public:
    Parser(const Lexer &lexer, const Token &currentToken);

    queue<Token> parser();

    void calculating(queue<Token> tokens);
};


#endif //KPHPVK_PARSER_H

// 3 4 2 * 1 5 - 2 3 ^ ^ / +