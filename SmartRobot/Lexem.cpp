//
// Created by mi4r on 30.03.2021.
//

#include "Lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include "Lexem.h"
#include "Common.h"

void Lexem::Print(void)
{
    printf("lexem: %s\tline: %d\ttype: ",text,line);
    switch(type)
    {
        case separator:
            printf("separator\n");
            break;
        case assign:
            printf("assign\n");
            break;
        case digit:
            printf("digit\n");
            break;
        case string:
            printf("string\n");
            break;
        case varName:
            printf("varName\n");
            break;
        case label:
            printf("label\n");
            break;
        case function:
            printf("function\n");
            break;
        case keyWord:
            printf("key word\n");
            break;
        default:
            break;
    }
}

void Lexem::ErrorHandling(int save)
{
    printf("Wrong Input\n");
    switch(error)
    {
        case keyWord_number:
            fprintf(stderr, "Key word: latin letter expected,"
                            " but number received %c\n",save);
            break;
        case keyWord_unknown:
            fprintf(stderr, "Key word: unknown symbol %c\n",save);
            break;
        case id_unknown:
            fprintf(stderr, "Identificator:"
                            " unknown symbol %c\n",save);
            break;
        case digit_letter:
            fprintf(stderr, "Digit: number expected,"
                            " but latin letter received %c\n",save);
            break;
        case digit_unknown:
            fprintf(stderr, "Digit: unknown symbol %c\n",save);
            break;
        case start_unknown:
            fprintf(stderr, "Start state received"
                            " unknown symbol %c\n",save);
            break;
        default:
            break;
    }
}

