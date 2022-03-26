//
// Created by Artur Kabirov on 26/3/22.
//

#ifndef KPHPVK_LEXER_H
#define KPHPVK_LEXER_H

#include <iostream>
#include "Constatns.h"

class Lexer {
    bool isPunctuator(char ch)                    //check if the given character is a punctuator or not
    {
        if (ch == SPACE || ch == PLUS || ch == MINUS ||
            ch == MULTIPLICATION || ch == DIVISION ||
            ch == COMMA || ch == SEMICOLON ||
            ch == EQUAL || ch == O_BRACKET || ch == C_BRACKET) {
            return true;
        }
        return false;
    }

    bool validIdentifier(char* str)						//check if the given identifier is valid or not
    {
        if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
            str[0] == '3' || str[0] == '4' || str[0] == '5' ||
            str[0] == '6' || str[0] == '7' || str[0] == '8' ||
            str[0] == '9' || isPunctuator(str[0]) == true)
        {
            return false;
        }									//if first character of string is a digit or a special character, identifier is not valid
        int i,len = strlen(str);
        if (len == 1)
        {
            return true;
        }										//if length is one, validation is already completed, hence return true
        else
        {
            for (i = 1 ; i < len ; i++)						//identifier cannot contain special characters
            {
                if (isPunctuator(str[i]) == true)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isOperator(char ch)							//check if the given character is an operator or not
    {
        if (ch == PLUS || ch == MINUS || ch == MULTIPLICATION ||
            ch == DIVISION || ch == EQUAL)
        {
            return true;
        }
        return false;
    }


    bool isKeyword(char *str)						//check if the given substring is a keyword or not
    {
        if (!strcmp(str, "val") || !strcmp(str, "var") ||
            !strcmp(str, "print") || !strcmp(str, "input"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isNumber(char* str)							//check if the given substring is a number or not
    {
        int i, len = strlen(str),numOfDecimal = 0;
        if (len == 0)
        {
            return false;
        }
        for (i = 0 ; i < len ; i++)
        {
            if (numOfDecimal > 1 && str[i] == '.')
            {
                return false;
            } else if (numOfDecimal <= 1)
            {
                numOfDecimal++;
            }
            if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                && str[i] != '3' && str[i] != '4' && str[i] != '5'
                && str[i] != '6' && str[i] != '7' && str[i] != '8'
                && str[i] != '9' || (str[i] == '-' && i > 0))
            {
                return false;
            }
        }
        return true;
    }

    char* subString(char* realStr, int l, int r)				//extract the required substring from the main string
    {
        int i;

        char* str = (char*) malloc(sizeof(char) * (r - l + 2));

        for (i = l; i <= r; i++)
        {
            str[i - l] = realStr[i];
            str[r - l + 1] = '\0';
        }
        return str;
    }

public:
    void parse(char* str)						//parse the expression
    {
        int left = 0, right = 0;
        int len = strlen(str);
        while (right <= len && left <= right) {
            if (isPunctuator(str[right]) == false)			//if character is a digit or an alphabet
            {
                right++;
            }

            if (isPunctuator(str[right]) == true && left == right)		//if character is a punctuator
            {
                if (isOperator(str[right]) == true)
                {
                    std::cout<< str[right] <<" IS AN OPERATOR\n";
                }
                right++;
                left = right;
            } else if (isPunctuator(str[right]) == true && left != right
                       || (right == len && left != right)) 			//check if parsed substring is a keyword or identifier or number
            {
                char* sub = subString(str, left, right - 1);   //extract substring

                if (isKeyword(sub) == true)
                {
                    std::cout<< sub <<" IS A KEYWORD\n";
                }
                else if (isNumber(sub) == true)
                {
                    std::cout<< sub <<" IS A NUMBER\n";
                }
                else if (validIdentifier(sub) == true
                         && isPunctuator(str[right - 1]) == false)
                {
                    std::cout<< sub <<" IS A VALID IDENTIFIER\n";
                }
                else if (validIdentifier(sub) == false
                         && isPunctuator(str[right - 1]) == false)
                {
                    std::cout<< sub <<" IS NOT A VALID IDENTIFIER\n";
                }

                left = right;
            }
        }
        return;
    }

};


#endif //KPHPVK_LEXER_H
