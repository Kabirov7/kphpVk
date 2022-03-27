//
// Created by Artur Kabirov on 26/3/22.
//

#ifndef KPHPVK_LEXER_H
#define KPHPVK_LEXER_H
#include <vector>
#include "Token.h"
using namespace std;
class Lexer {
public:
    Lexer(const char * beg) : m_beg(beg){};

    Token next() noexcept;
private:
    Token identifier() noexcept;
    Token number() noexcept;
    Token atom(Token::Type) noexcept;

    char peek() const noexcept;
    char get() noexcept;

    const char *m_beg = nullptr;

};


#endif //KPHPVK_LEXER_H
