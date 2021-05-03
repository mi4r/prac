#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Lexer.h"
#include "Lexem.h"
#include "Common.h"

void analysis()
{
    Lexem * lexeme;
    Lexer lexer;
    int c;
    while (!lexeme->ending)
    {
        c = getchar();
        lexeme = lexer.analysisStart(c);
        lexeme->Print();
    }
}

int main()
{
    int fd = -1;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        printf("ERROR: can not open this file\n");
    else
    {
        dup2(fd, STDIN_FILENO);
        analysis();
        close(fd);
    }

    return 0;
}










/*
class ListItem
{
public:
    ListItem * next;

public:
    // Load
    Lexem * lex;
};

int main()
{
    ListItem * list = NULL;
    Lexer lexer;
    Lexem * lexeme;
    int c;
    int flag = 1;
    int fd = -1;
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        printf("ERROR: can not open this file\n");
    else
    {
        dup2(fd, STDIN_FILENO);
        while (true)
        {
            c = getchar();
            if (c == EOF && flag > 0)
            {
                c = ' ';
                flag *=  -1;
            }
            if (c == EOF && flag < 0)
                break;
            //list = new listOfLex;
            //list->lex = new lexeme;
            //list->lex->text = new char;
            //list->lex->text = lexer.step(c);
            lexeme = lexer.step(c);
            if (lexeme != nullptr)
            {
                if (lexeme->type == -1)
                    break;
                printf("lexem: %s\tline: %d\ttype: %d\n", lexeme->text, lexeme->line, lexeme->type);
                if (lexeme->m_isFirstOfTwo)
                {
                    lexeme = lexer.step(c);
                    if (lexeme != nullptr)
                    {
                        if (lexeme->type == -1)
                            break;
                        printf("lexem: %s\tline: %d\ttype: %d\n", lexeme->text, lexeme->line, lexeme->type);
                    }
                }
            }

            if (lexeme != nullptr)
            {
                list->lex = new Lexem;
                list->lex = lexeme;
                list = list->next;
            }
        }
        close(fd);
    }


    return 0;
}
*/