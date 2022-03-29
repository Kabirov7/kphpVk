//
// Created by Artur Kabirov on 27/3/22.
//

#include <iostream>
#include "Parser.h"
#include <queue>
#include <stack>
#include <math.h>

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
                        leftToken = StrPlusStr(leftToken, rightToken);
                    } else if (IsStrAndNum(leftToken, rightToken) || IsStrAndFloat(leftToken, rightToken)) {
                        cout << "str + int/float" << endl;
                    } else if (IsNumAndNum(leftToken, rightToken) || IsFloatAndFloat(leftToken, rightToken) ||
                               IsNumAndFloat(leftToken, rightToken) || IsNumAndFloat(rightToken, leftToken)) {
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());
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
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());
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
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());

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
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());
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
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());
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
                        leftToken = IntOrFloatOPIntOrFloat(leftToken, rightToken, currentToken.getType());
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

Token Parser::StrPlusStr(Token l, Token r) {
    string left = string(l.getLexeme());
    string right = string(r.getLexeme());
    return Token(Token::Type::String, string_view(left + right));

}

Token Parser::StrMinusIntOrFloat(Token l, Token r) {
    string leftStr;
    char currentChar;
    for (int i = 0; i < l.getLexeme().length(); ++i) {
        currentChar = l.getLexeme()[i];
        if ('0' <= currentChar && currentChar <= '9' || currentChar == '.') {
            leftStr += currentChar;
        }
    }

    if (r.is(Token::Type::Number)) {
        try {
            int left = std::stoi(leftStr);
            int right = std::stoi(string(r.getLexeme()));
            return Token(Token::Type::Number, string_view(to_string(left - right)));
        }
        catch (std::invalid_argument const &e) {
            std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
        }
    } else if (r.is(Token::Type::Float)) {
        try {
            float left = std::stof(leftStr);
            float right = std::stof(string(r.getLexeme()));
            return Token(Token::Type::Float, string_view(to_string(left - right)));
        }
        catch (std::invalid_argument const &e) {
            std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
        }
    }

    cout << leftStr << endl;


    return Token(Token::Type::DoubleQuote);
}

Token Parser::IntOrFloatOPIntOrFloat(Token l, Token r, Token::Type operation) {
    float left;
    float right;
    float result;
    try {
        left = std::stof(string(l.getLexeme()));
        right = std::stof(string(r.getLexeme()));
    }
    catch (std::invalid_argument const &e) {
        throw std::invalid_argument("Operands are invalid");
    }
    switch (operation) {
        case Token::Type::Plus:
            result = left + right;
            break;
        case Token::Type::Minus:
            result = left - right;
            break;
        case Token::Type::Slash:
            result = left / right;
            break;
        case Token::Type::Asterisk:
            result = left * right;
            break;
        case Token::Type::Percent:
            result = ((int) left % (int) right);
            break;
        case Token::Type::Pow:
            result = pow(left, right);
            break;
        default:
            break;
    }
    if (IsNumAndNum(l, r)) {
        return Token(Token::Type::Number, to_string((int) result));
    }

    return Token(Token::Type::Number, to_string(result));
}

Token Parser::Assignee(Token l, Token r) {
    return Token(Token::Type::DoubleQuote);
}
