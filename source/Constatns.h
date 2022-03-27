//
// Created by Artur Kabirov on 26/3/22.
//

#ifndef KPHPVK_CONSTATNS_H
#define KPHPVK_CONSTATNS_H

#include <string>
#include <unordered_map>
#include <map>

const char PLUS = '+';
const char MINUS = '-';
const char DIVISION = '\\';
const char MULTIPLICATION = '*';
const char EQUAL = '=';
const char SPACE = ' ';
const char TAB = '\t';
const char SR = '\r';
const char NEW_LINE = '\n';
const char COMMA = ',';
const char DOT = '.';
const char SEMICOLON = ';';
const char O_BRACKET = '(';
const char C_BRACKET = ')';
const std::string CONST = "val";
const std::string VAR = "var";
const std::string SPACES = " \t\r";
std::map<char, short> PRIORITIES = {
        { ')', 2 },
        { '(', 2 },
        { '*', 5 },
        { '/', 5 },
        { '%', 5 },
        { '-', 6 },
        { '+', 6 },
        { '=', 16 },
        { ',', 17 }
};

#endif //KPHPVK_CONSTATNS_H
