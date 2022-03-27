#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <unordered_map>
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Token::Type &type) {
    static const char *const names[]{
            "Number", "Identifier", "LeftParen", "RightParen", "Equal", "Plus",
            "Minus", "Asterisk", "Slash", "Dot", "Comma", "Colon",
            "Semicolon", "SingleQuote", "DoubleQuote", "NewLine", "End", "Unexpected"
    };
    return os << names[static_cast<int>(type)];
}


int main() {
    char c[] = "1 + 2 + 3 + 4 + 5";
    vector<Token> * tokens = new vector<Token>();
    Lexer l = Lexer(c);
    for (auto token = l.next();
        not token.is_one_of(Token::Type::End, Token::Type::Unexpected);
        token = l.next())
        tokens->push_back(token);

    Token mul_token = Token(Token::Type::Asterisk, "*");
    Token plus_token = Token(Token::Type::Plus, "+");
    ASTNode *o1 = new ASTNode(Token(Token::Type::Number, "2"));
    ASTNode *o2 = new ASTNode(Token(Token::Type::Number, "7"));
    ASTNode *o3 = new ASTNode(Token(Token::Type::Number, "3"));
    ASTNode *mul_node = new ASTNode(mul_token, o1, o2);
    ASTNode *add_node = new ASTNode(plus_token, mul_node, o3);
    return 0;
}
