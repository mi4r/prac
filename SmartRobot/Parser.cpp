#include <stdio.h>
#include "Parser.h"
#include "Common.h"
#include <string.h>

Parser::Parser(Lexem * lexeme)
{
    CurLex->text = lexeme->text;
    CurLex->line = lexeme->line;
    CurLex->type = lexeme->type;
    CurLex->errStatus = lexeme->errStatus;
    CurLex->readiness = lexeme->readiness;
    CurLex->ending = lexeme->ending;
}

void Parser::NextLex()
{
    Lexer  lexer;
    int c;
    c = getchar();
    Lexem * tmp = lexer.analysisStart(c);
    while (tmp->readiness != ready)
    {
        c = getchar();
        tmp = lexer.analysisStart(c);
    }
    CurLex->text = tmp->text;
    CurLex->line = tmp->line;
    CurLex->type = tmp->type;
    CurLex->errStatus = tmp->errStatus;
    CurLex->readiness = tmp->readiness;
    CurLex->ending = tmp->ending;
}

void Parser::start_hdl()
{
    if (strcmp(CurLex->text, "begin") != 0)
        throw ;
    NextLex();
    body_hdl();
    if (strcmp(CurLex->text, "end") != 0)
        throw ;
}

void Parser::body_hdl()
{
    if (CurLex->type == varName)
    {
        NextLex();
        assign_hdl();
    }
    else if (strcmp(CurLex->text, "if") == 0)
    {
        NextLex();
        if_hdl();
    }
    else if (strcmp(CurLex->text, "while") == 0)
    {
        NextLex();
        while_hdl();
    }
    else if (strcmp(CurLex->text, "{") == 0)
    {
        NextLex();
        in_hdl();
    }
    else if (strcmp(CurLex->text, "endturn") == 0)
    {
        NextLex();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, "prod") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, "build") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, "buy") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ",") != 0)
            throw ;
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, "sell") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ",") != 0)
            throw ;
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, "print") == 0)
    {
        NextLex();
        print_hdl();
    }
    else throw ;
}

void Parser::assign_hdl()
{
    if (strcmp(CurLex->text, "[") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, "]") != 0)
            throw ;
        NextLex();
        if (strcmp(CurLex->text, ":=") != 0)
            throw ;
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else if (strcmp(CurLex->text, ":=") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else throw ;
}

void Parser::if_hdl()
{
    if (strcmp(CurLex->text, "(") != 0)
        throw ;
    NextLex();
    exp_hdl();
    if (strcmp(CurLex->text, ")") != 0)
        throw ;
    NextLex();
    body_hdl();
}

void Parser::while_hdl()
{
    if (strcmp(CurLex->text, "(") != 0)
        throw ;
    NextLex();
    exp_hdl();
    if (strcmp(CurLex->text, ")") != 0)
        throw ;
    NextLex();
    body_hdl();
}

void Parser::in_hdl()
{
    body_hdl();
    if (strcmp(CurLex->text, "}") == 0)
    {
        NextLex();
        return;
    }
    else in_hdl();
}

void Parser::print_hdl()
{
    if (CurLex->type == string)
    {
        NextLex();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
    else
    {
        exp_hdl();
        if (strcmp(CurLex->text, ";") != 0)
            throw ;
    }
}

void Parser::var_hdl()
{
    if (strcmp(CurLex->text, "[")  == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, "]") != 0)
            throw ;
    }
    else return;
}

void Parser::func_hdl()
{
    if (CurLex->type != function)
        throw ;
    NextLex();
    if (strcmp(CurLex->text, "(") != 0)
        throw ;
    NextLex();
    func_tail_hdl();
}

void Parser::func_tail_hdl()
{
    if (strcmp(CurLex->text, ")") == 0)
    {
        NextLex();
        return;
    }
    exp_hdl();
    if (strcmp(CurLex->text, ")") != 0)
        throw ;
}

void Parser::exp_hdl()
{
    exp5_hdl();
    if (strcmp(CurLex->text, "or") == 0)
    {
        NextLex();
        exp_hdl();
    }
    else throw ;
}

void Parser::exp5_hdl()
{
    exp4_hdl();
    if (strcmp(CurLex->text, "and") == 0)
    {
        NextLex();
        exp5_hdl();
    }
    else throw ;
}

void Parser::exp4_hdl()
{
    exp3_hdl();
    if (strcmp(CurLex->text, ">") == 0)
    {
        NextLex();
        exp4_hdl();
    }
    else if (strcmp(CurLex->text, "<") == 0)
    {
        NextLex();
        exp4_hdl();
    }
    else if (strcmp(CurLex->text, "=") == 0)
    {
        NextLex();
        exp4_hdl();
    }
    else throw ;
}

void Parser::exp3_hdl()
{
    exp2_hdl();
    if (strcmp(CurLex->text, "+") == 0)
    {
        NextLex();
        exp3_hdl();
    }
    else if (strcmp(CurLex->text, "-") == 0)
    {
        NextLex();
        exp3_hdl();
    }
    else throw ;
}

void Parser::exp2_hdl()
{
    exp1_hdl();
    if (strcmp(CurLex->text, "*") == 0)
    {
        NextLex();
        exp2_hdl();
    }
    else if (strcmp(CurLex->text, "/") == 0)
    {
        NextLex();
        exp2_hdl();
    }
    else if (strcmp(CurLex->text, "%") == 0)
    {
        NextLex();
        exp2_hdl();
    }
    else throw ;
}

void Parser::exp1_hdl()
{
    exp3_hdl();
    if (strcmp(CurLex->text, "not") == 0)
    {
        NextLex();
        exp1_hdl();
    }
    else
    {
       NextLex();
        if (CurLex->type == varName || CurLex->type == function
            || CurLex->type == digit || strcmp(CurLex->text, "(") == 0)
        {
            exp0_hdl();
        }
        else throw ;
    }
}

void Parser::exp0_hdl()
{
    if (CurLex->type == varName)
    {
        NextLex();
        var_hdl();
    }
    else if (CurLex->type == function)
    {
        func_hdl();
    }
    else if (CurLex->type == digit)
    {
        NextLex();
        return;
    }
    else if (strcmp(CurLex->text, "(") == 0)
    {
        NextLex();
        exp_hdl();
        if (strcmp(CurLex->text, ")") != 0)
            throw ;
    }
    else
    {
        NextLex();
        if (strcmp(CurLex->text, ";") == 0)
        {
            return;
        }
        else throw ;
    }
}

void Parser::Parse()
{
    if (CurLex->ending)
        return;
    NextLex();
    start_hdl();
}