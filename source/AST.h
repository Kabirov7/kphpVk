//
// Created by Artur Kabirov on 26/3/22.
//

#ifndef KPHPVK_AST_H
#define KPHPVK_AST_H

#include "Token.h"

struct ASTNode {
    Token token;
    ASTNode *left, *right;

    ASTNode(const Token &token) : token(token) {}

    ASTNode(const Token &token, ASTNode *left, ASTNode *right)
    : token(token), left(left), right(right){}
};

class AST {
public:
    ASTNode *_head;
private:

};


#endif //KPHPVK_AST_H
