//
// Created by Artur Kabirov on 27/3/22.
//

#include <iostream>
#include "Parser.h"
#include <queue>
#include <stack>


queue<Token> Parser::parser() {
    queue<Token> operators;
    queue<Token> operands;

    while (currentToken.getType() != Token::Type::End && currentToken.getType() != Token::Type::Unexpected) {
        Token::Type currentType = currentToken.getType();

        if (IsOperator(currentType)) {
            std::string_view lexeme = currentToken.getLexeme();

            if (operators.empty() ||
                getPriority(operators.front().getLexeme()[0]) > getPriority(currentToken.getLexeme()[0]) ||
                operators.front().getLexeme() == currentToken.getLexeme()) {
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

        } else {
            operands.push(currentToken);
        }
        currentToken = lexer.next();
    }

    int t = operators.size();
    for (int i = 0; i < t; ++i) {
        operands.push(operators.front());
        operators.pop();
    }
    calculating(operands);
    return operands;
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

void Parser::calculating(queue<Token> tokens) {
    stack<Token> counted;
    int t = tokens.size();
    for (int i = 0; i < t; ++i) {
        cout << tokens.front().getLexeme() << " ";
        tokens.pop();
    }
//    Token token = tokens.front();
    /*while (tokens.front().getType() != Token::Type::End && tokens.front().getType() != Token::Type::Unexpected){
        if (token.is(Token::Type::Number) ){
            counted.push(token);
        } else if (IsOperator(token.getType())){
            switch (token.getType()) {
                case Token::Type::Plus:

                case Token::Type::Minus:
                case Token::Type::Asterisk:
                case Token::Type::Slash:
                case Token::Type::Percent:
                case Token::Type::Pow:
                default:
                    break;
            }
            token = tokens.front();
            tokens.pop();

        }

    }*/
}
