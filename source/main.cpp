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
            "Semicolon", "SingleQuote", "DoubleQuote", "NewLine", "Percent",
            "Pow", "String", "Variable", "Const", "End", "Unexpected"
    };
    return os << names[static_cast<int>(type)];
}


int main() {
    char c[] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    vector<Token> *tokens = new vector<Token>();
    Lexer l = Lexer(c);
//    for (auto token = l.next();
//         not token.is_one_of(Token::Type::End, Token::Type::Unexpected);
//         token = l.next())
//        cout << token.getType() << "|" << token.getLexeme() << "|" << endl;
//        tokens->push_back(token);

    Parser p = Parser(l, l.next());
    p.parser();
    return 0;
}
