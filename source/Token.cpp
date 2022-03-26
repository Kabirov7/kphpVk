//
// Created by Artur Kabirov on 26/3/22.
//

#include "Token.h"

Token::Token(Token::Type type) noexcept: type(type) {}

Token::Token(Token::Type type, std::string_view m_lexeme) noexcept:
        type(type), lexeme(m_lexeme) {}

Token::Token(Token::Type type, const char *beg, std::size_t len) noexcept:
        type(type), lexeme(beg, len) {}

Token::Token(Token::Type type, const char *beg, const char *end) noexcept
        : type{type}, lexeme(beg, std::distance(beg, end)) {}

Token::Type Token::getType() const noexcept {
    return type;
}

void Token::setType(Token::Type t) noexcept {
    type = t;
}

bool Token::is(Token::Type toCompare) const noexcept {
    return type == toCompare;
}

bool Token::isNot(Type toCompare) const noexcept {
    return type != toCompare;
}

bool Token::is_one_of(Token::Type t1, Token::Type t2) const noexcept {
    return is(t1) || is(t2);
}

std::string_view Token::getLexeme() const noexcept {
    return lexeme;
}

void Token::setLexeme(std::string_view lex) noexcept {
    lexeme = std::move(lex);
}



