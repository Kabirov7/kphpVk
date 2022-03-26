#include <iostream>
#include "Lexer.h"

int main() {
    Lexer l = Lexer();
    char c[100] = "val m = 3 + 3";
    l.parse(c);
    return 0;
}
