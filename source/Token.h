//
// Created by Artur Kabirov on 26/3/22.
//

#ifndef KPHPVK_TOKEN_H
#define KPHPVK_TOKEN_H


#include <string_view>

class Token {
public:
    enum class Type {
        Number,
        Identifier,
        LeftParen,
        RightParen,
        Equal,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Dot,
        Comma,
        Colon,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        NewLine,
        Percent,
        Pow,
        String,
        End,
        Unexpected,
    };

    Token(Type type) noexcept;

    Token(Type type, std::string_view m_lexeme) noexcept;

    Token(Type type, const char *beg, std::size_t len) noexcept;

    Token(Type type, const char *beg, const char *end) noexcept;

    Type getType() const noexcept;

    void setType(Type t) noexcept;

    bool is(Type toCompare) const noexcept;

    bool isNot(Type toCompare) const noexcept;

    bool is_one_of(Type t1, Type t2) const noexcept;

    template <typename... Ts>
    bool is_one_of(Type t1, Type t2, Ts... ks) const noexcept {
        return is(t1) || is_one_of(t2, ks...);
    }

    std::string_view getLexeme() const noexcept;

    void setLexeme(std::string_view lex) noexcept;

private:
    Type type{};
    std::string_view lexeme{};
};


#endif //KPHPVK_TOKEN_H
