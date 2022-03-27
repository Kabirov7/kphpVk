//
// Created by Artur Kabirov on 27/3/22.
//

#include <iostream>
#include "Parser.h"
#include <queue>


void Parser::parser() {
    queue<Token> operators;
    queue<Token> operands;

    while (currentToken.getType() != Token::Type::End && currentToken.getType() != Token::Type::Unexpected) {
        Token::Type currentType = currentToken.getType();

        if (IsOperator(currentType)) {
            std::string_view lexeme = currentToken.getLexeme();

            if (operators.empty() ||
                getPriority(operators.front().getLexeme()[0]) > getPriority(currentToken.getLexeme()[0]) || operators.front().getLexeme() == currentToken.getLexeme() ) {
                if (currentType == Token::Type::RightParen) {
                    while (operators.front().getType() != Token::Type::LeftParen) {
                        operands.push(operators.front());
                        operators.pop();
                    }
                    operators.pop();
                } else {
                    operators.push(currentToken);
                }

            } else {
                if (operators.front().getType() != Token::Type::LeftParen) {
                    operands.push(operators.front());
                    operators.pop();
                    operators.push(currentToken);
                } else {
                    operators.push(currentToken);
                }

            }

        } else if (currentType == Token::Type::Number) {
            operands.push(currentToken);
        }
        currentToken = lexer.next();
    }

    int t = operators.size();
    for (int i = 0; i < t; ++i) {
        operands.push(operators.front());
        operators.pop();
    }

    t = operands.size();
    for (int i = 0; i < t; ++i) {
        cout<<operands.front().getLexeme()<< " " ;
        operands.pop();
    }

    cout << endl << "DONE" << endl;
}

bool Parser::IsOperator(Token::Type t) {
    if (t == Token::Type::Plus || t == Token::Type::Minus || t == Token::Type::Slash ||
        t == Token::Type::Asterisk || t == Token::Type::Pow || t == Token::Type::Percent ||
        t == Token::Type::LeftParen || t == Token::Type::RightParen) {
        return true;
    }
    return false;
}

Parser::Parser(const Lexer &lexer, const Token &currentToken) : lexer(lexer), currentToken(currentToken) {}

short Parser::getPriority(char c) {
    return PRIORITIES.find(c)->second;
}
