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

