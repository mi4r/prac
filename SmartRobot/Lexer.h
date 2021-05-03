//
// Created by mi4r on 24.03.2021.
//

#ifndef PROJECTSMARTROBOT_LEXER_H
#define PROJECTSMARTROBOT_LEXER_H

#include "Lexem.h"

class Lexer
{
    int state;
    int size;
    char * buf;
    int cur;
    int LineCounter;
    int save;
    int ErrorFlag;
    bool LineBreakFlag;
    bool FlagEOF;
    //int m_c;
    //bool m_saved;
    //Lexem * m_pLexem;
    Lexem * start(int c);
    Lexem * makeDigit(int c);
    Lexem * makeString(int c);
    Lexem * makeIdentifier(int c);
    Lexem * makeKeyWord(int c);
    Lexem * makeAssign(int c);
    char * extendBuf();
    void initBuf();
    Lexem * check(Lexem * lexeme);
    Lexem * step(int c);
public:
    Lexer(void);
    ~Lexer();
    Lexem * analysisStart(int c);
};

#endif //PROJECTSMARTROBOT_LEXER_H
