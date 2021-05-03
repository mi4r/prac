//
// Created by mi4r on 16.04.2021.
//

#ifndef PROJECTSMARTROBOT_PARSER_H
#define PROJECTSMARTROBOT_PARSER_H

#include "Lexem.h"

class Parser
{
    Lexem CurLex;
    void NextLex();
    void KeyWordParse();
    void FunctionParse();
    void WhileParse();
    void IfParse();
    void BuildParse();
    void BuyParse();
    void SellParse();
    void ProdParse();
    void PrintParse();
    void BoolExprParse();
    void AssignmentExprParse();
    void Statement();
public:
    Parser(Lexem lexeme);
    void Parse();
};

#endif //PROJECTSMARTROBOT_PARSER_H
