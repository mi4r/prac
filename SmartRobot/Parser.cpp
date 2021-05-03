//
// Created by mi4r on 16.04.2021.
//
/*
#include "Parser.h"
#include "Common.h"

Parser::Parser(Lexem lexeme)
{
    CurLex = lexeme;
}

void Parser::NextLex()
{

}

void Parser::BoolExprParse()
{
    NextLex();
    if (CurLex.type == varName)
    {

    }
    else if (CurLex.type == function)
    {

    }
    else
    {
        //throw
    }
}

void Parser::IfParse()
{
    BoolExprParse();
    if (CurLex.text == "then")
    {
        NextLex();
        if (CurLex.type == function)
        {
            FunctionParse();
        }
        else if (CurLex.type == keyWord)
        {
            KeyWordParse();
        }
    }
    else
    {
        //throw
    }
}

void Parser::KeyWordParse()
{
    if (CurLex.text == "if")
    {
        IfParse();
    }
    else if (CurLex.text == "while")
    {
        WhileParse();
    }
    else if (CurLex.text == "build")
    {
        BuildParse();
    }
    else if (CurLex.text == "print")
    {
        PrintParse();
    }
    else if (CurLex.text == "buy")
    {
        BuyParse();
    }
    else if (CurLex.text == "sell")
    {
        SellParse();
    }
    else if (CurLex.text == "prod")
    {
        ProdParse();
    }
    else
    {
        //throw
    }
}

void Parser::Parse()
{
    NextLex();
    if (CurLex.type == keyWord)
    {
        KeyWordParse();
    }
    else if (CurLex.type == varName)
    {
        AssignmentExprParse();
    }
    else
    {
        //throw
    }
}
*/