//
// Created by Artur Kabirov on 26/3/22.
//

#include <cstring>
#include "iostream"
#include "Lexer.h"
#include "Constatns.h"

bool isSpace(char c) {
    return SPACES.find(c) != string::npos;
}

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isIdentifierChar(char c) noexcept {
    if ('a' <= c && c <= 'z' ||
        'A' <= c && c <= 'Z' ||
        isDigit(c) || c == '_'
            )
        return true;
    return false;
}

char Lexer::peek() const noexcept {
    return *m_beg;
}

char Lexer::get() noexcept {
    return *m_beg++;
}

Token Lexer::atom(Token::Type type) noexcept {
    return Token(type, m_beg++, 1);
}

Token Lexer::next() noexcept {
    while (isSpace(peek())) get();

    char pik = peek();
    if (pik == '\0') {
        return Token(Token::Type::End, m_beg, 1);
    } else if (isIdentifierChar(pik)) {
        return identifier();
    } else if (isDigit(pik)) {
        return number();
    } else {
        switch (pik) {
            case '(':
                return atom(Token::Type::LeftParen);
            case ')':
                return atom(Token::Type::RightParen);
            case '=':
                return atom(Token::Type::Equal);
            case '+':
                return atom(Token::Type::Plus);
            case '-':
                return atom(Token::Type::Minus);
            case '*':
                return atom(Token::Type::Asterisk);
            case '/':
                return atom(Token::Type::Slash);
            case '.':
                return atom(Token::Type::Dot);
            case ',':
                return atom(Token::Type::Comma);
            case ':':
                return atom(Token::Type::Colon);
            case ';':
                return atom(Token::Type::Semicolon);
            case '\'':
                return atom(Token::Type::SingleQuote);
            case '"':
                return atom(Token::Type::DoubleQuote);
            case '\n':
                return atom(Token::Type::NewLine);
            default:
                return atom(Token::Type::Unexpected);

        }
    }
}

Token Lexer::identifier() noexcept {
    const char *start = m_beg;
    get();
    while (isIdentifierChar(peek()))get();
    return Token(Token::Type::Identifier, start, m_beg);
}

Token Lexer::number() noexcept {
    const char *start = m_beg;
    get();
    while (isDigit(peek())) get();
    return Token(Token::Type::Number, start, m_beg);
}


