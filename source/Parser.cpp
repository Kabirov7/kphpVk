//
// Created by Artur Kabirov on 27/3/22.
//

#include <iostream>
#include "Parser.h"
#include <queue>
#include <stack>


#include <stack>


stack<Token> Parser::parser() {
    stack<Token> operators;
    stack<Token> operands;

    while (currentToken.getType() != Token::Type::End && currentToken.getType() != Token::Type::Unexpected) {
        Token::Type currentType = currentToken.getType();

        if (IsOperator(currentType)) {
            std::string_view lexeme = currentToken.getLexeme();

            if (operators.empty() ||
                getPriority(operators.top().getLexeme()[0]) > getPriority(currentToken.getLexeme()[0]) ||
                operators.top().getLexeme() == currentToken.getLexeme()) {
                if (currentType == Token::Type::RightParen) {
                    while (operators.top().getType() != Token::Type::LeftParen) {
                        operands.push(operators.top());
                        operators.pop();
                    }
                    operators.pop();
                } else {
                    operators.push(currentToken);
                }

            } else {
                if (operators.top().getType() != Token::Type::LeftParen) {
                    operands.push(operators.top());
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
        operands.push(operators.top());
        operators.pop();
    }

    t = operands.size();
    for (int i = 0; i < t; ++i) {
        operators.push(operands.top());
        operands.pop();
    }

    calculating(operators);
    return operators;
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

void Parser::calculating(stack<Token> tokens) {
    stack<Token> counted;

    while (tokens.size() > 0) {
        Token currentToken = tokens.top();
        if (IsOperator(currentToken.getType())) {
            tokens.pop();
            switch (currentToken.getType()) {
                case Token::Type::Plus: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsStrAndStr(leftToken, rightToken)) {
                        cout << "str + str" << endl;
                    } else if (IsStrAndNum(leftToken, rightToken) || IsStrAndFloat(leftToken, rightToken)) {
                        cout << "str + int/float" << endl;
                    } else if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                               IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        leftToken = IntOrFloatPlusIntOrFloat(leftToken, rightToken);
                        cout << "int/float + int/float" << endl;
                    } else {
                        cout << "ERROR PLUS" << endl;
                    }
                    counted.push(leftToken);
                    break;
                }
                case Token::Type::Minus: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsStrAndNum(leftToken, rightToken) || IsStrAndFloat(leftToken, rightToken)) {
                        cout << "str - int/float" << endl;
                        leftToken = StrMinusIntOrFloat(leftToken, rightToken);
                    } else if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                               IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        cout << "int/float - int/float" << endl;
                        leftToken = IntOrFloatMinusIntOrFloat(leftToken, rightToken);
                    } else {
                        cout << "ERROR MINUS" << endl;
                    }
                    counted.push(leftToken);
                    break;
                }
                case Token::Type::Slash: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                        IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        cout << "int/float / int/float" << endl;
                        leftToken = IntOrFloatDivIntOrFloat(leftToken, rightToken);
                    } else {
                        cout << "ERROR MINUS" << endl;
                    }
                    counted.push(leftToken);
                    break;
                }
                case Token::Type::Asterisk: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                        IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        cout << "int/float * int/float" << endl;
                        leftToken = IntOrFloatMultIntOrFloat(leftToken, rightToken);
                    } else {
                        cout << "ERROR ASTERISK" << endl;
                    }
                    break;
                }
                case Token::Type::Percent: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                        IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        cout << "int/float % int/float" << endl;
                        leftToken = IntOrFloatPercIntOrFloat(leftToken, rightToken);
                    } else {
                        cout << "ERROR PERCENT" << endl;
                    }
                    counted.push(leftToken);
                    break;
                }
                case Token::Type::Pow: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                        IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        cout << "int/float ^ int/float" << endl;
                        leftToken = IntOrFloatPowIntOrFloat(leftToken, rightToken);
                    } else {
                        cout << "ERROR POW" << endl;
                    }
                    counted.push(leftToken);
                    break;
                }
                case Token::Type::Equal: {
                    Token rightToken = counted.top();
                    counted.pop();
                    Token leftToken = counted.top();
                    counted.pop();
                    leftToken = Assignee(leftToken, rightToken);
                    break;
                }
                default:
                    cout << "ERROR" << endl;
                    break;
            }
        } else {
            counted.push(currentToken);
            tokens.pop();
        }
    }
}
