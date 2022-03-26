#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "Lexer.h"

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
    char c[] = "val m = 3 + 3\n";
    vector<Token> * tokens = new vector<Token>();
    Lexer l = Lexer(c);
    for (auto token = l.next();
        not token.is_one_of(Token::Type::End, Token::Type::Unexpected);
        token = l.next())
        tokens->push_back(token);

    for(Token i : *tokens)
        cout << i.getType() << "| " << i.getLexeme() << endl;
    return 0;
}
