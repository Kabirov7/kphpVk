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

    switch (peek()) {
        case '\0':
            return Token(Token::Type::End, m_beg, 1);
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return identifier();
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return number();
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
        case '"': {
            const char *start = m_beg;
            get();
            while (peek()!='"')get();
            return Token(Token::Type::String, start+1, m_beg++);
        }
        case '\n':
            return atom(Token::Type::NewLine);
        case '^':
            return atom(Token::Type::Pow);
        case '%':
            return atom(Token::Type::Percent);
        default:
            return atom(Token::Type::Unexpected);

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


