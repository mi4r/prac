//
// Created by mi4r on 30.03.2021.
//

#include "Lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include "Lexem.h"
#include "Common.h"

Lexem::Lexem()
: readiness(unready), ending(false)
{
}

void Lexem::Print(void)
{
    if (readiness != unready)
    {
        if (readiness == err)
            ErrorHandling();
        else if (readiness != eof)
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
    }
}

void Lexem::ErrorHandling()
{
    fprintf(stderr, "Wrong Input\n");
    switch(errStatus)
    {
        case keyWord_number:
            fprintf(stderr, "Key word: latin letter expected,"
                            " but number received\n");
            break;
        case keyWord_unknown:
            fprintf(stderr, "Key word: unknown symbol\n");
            break;
        case id_unknown:
            fprintf(stderr, "Identifier:"
                            " unknown symbol\n");
            break;
        case digit_letter:
            fprintf(stderr, "Digit: number expected,"
                            " but latin letter received\n");
            break;
        case digit_unknown:
            fprintf(stderr, "Digit: unknown symbol\n");
            break;
        case start_unknown:
            fprintf(stderr, "Start state received"
                            " unknown symbol\n");
            break;
        default:
            break;
    }
}

