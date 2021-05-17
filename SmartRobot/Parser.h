//
// Created by mi4r on 16.04.2021.
//

#ifndef PROJECTSMARTROBOT_PARSER_H
#define PROJECTSMARTROBOT_PARSER_H

#include "Lexem.h"
#include "Lexer.h"

class Parser
{
    Lexem * CurLex;
    void NextLex();
    void start_hdl();
    void body_hdl();
    void assign_hdl();
    void if_hdl();
    void while_hdl();
    void in_hdl();
    void print_hdl();
    void func_hdl();
    void func_tail_hdl();
    void var_hdl();
    void exp_hdl();
    void exp5_hdl();
    void exp4_hdl();
    void exp3_hdl();
    void exp2_hdl();
    void exp1_hdl();
    void exp0_hdl();
public:
    Parser(Lexem * lexeme);
    void Parse();
};

#endif //PROJECTSMARTROBOT_PARSER_H
