#include <iostream>
#include <unordered_map>
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Token::Type &type) {
    static const char *const names[]{
            "Number", "Float", "Identifier", "LeftParen", "RightParen", "Equal", "Plus",
            "Minus", "Asterisk", "Slash", "Dot", "Comma", "Colon",
            "Semicolon", "SingleQuote", "DoubleQuote", "NewLine", "Percent",
            "Pow", "String", "Variable", "Const", "End", "Unexpected"
    };
    return os << names[static_cast<int>(type)];
}


int main() {
    char c[] = "32 - 324.3 - 12 - 32";
    vector<Token> *tokens = new vector<Token>();
    Lexer l = Lexer(c);

    Parser p = Parser(l, l.next());
    p.parser();
    return 0;
}
