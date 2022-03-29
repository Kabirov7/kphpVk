//
// Created by Artur Kabirov on 27/3/22.
//

#ifndef KPHPVK_PARSER_H
#define KPHPVK_PARSER_H


#include <map>
#include "Lexer.h"
#include "AST.h"
#include <queue>
#include <stack>


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

    bool IsStrAndStr(Token left, Token right){
        return left.is(Token::Type::String) && right.is(Token::Type::String);
    }
    bool IsStrAndNum(Token left, Token right){
        return left.is(Token::Type::String) && right.is(Token::Type::Number);
    }
    bool IsStrAndFloat(Token left, Token right){
        return left.is(Token::Type::String) && right.is(Token::Type::Float);
    }

    bool IsNumAndNum(Token left, Token right){
        return left.is(Token::Type::Number) && right.is(Token::Type::Number);
    }
    bool IsNumAndFloat(Token left, Token right){
        return left.is(Token::Type::Number) && right.is(Token::Type::Float);
    }

    bool IsFloatAndFloat(Token left, Token right){
        return left.is(Token::Type::Float) && right.is(Token::Type::Float);
    }


//    String + Int/Float число преобразуется в строку
//    "Hello" + "!" => "Hello!"
//    "Hello" + "43" => "Hello43"
//    String - Int/Float строка преобразуется в целое или дробное число, а если строка не является числовой (2) то будто бы она "0" .
//    "World" - 42 = -42
//    "134" - 42 = 92
//    "134" + 42 = 13442
//    Float (+, -) Int целое число преобразуется в дробное.
    Token StrPlusIntOrFloat(Token l, Token r){
        string str = "";
        str +=l.getLexeme();
        str += r.getLexeme();
        return Token(Token::Type::String, str);
    }

    Token StrPlusStr(Token l, Token r);

    Token StrMinusIntOrFloat(Token l, Token r);

    Token IntOrFloatOPIntOrFloat(Token l, Token r, Token::Type);

    Token Assignee(Token l, Token r);

public:
    Parser(const Lexer &lexer, const Token &currentToken);

    stack<Token> parser();

    void calculating(stack<Token> tokens);
};


#endif //KPHPVK_PARSER_H

// 3 4 2 * 1 5 - 2 3 ^ ^ / +