//
// Created by mi4r on 24.03.2021.
//

#include "Lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include "Common.h"

#define _MY_DEBUG_

#ifdef _MY_DEBUG_
#define _MY_DEBUG_OUTPUT_ stdout
#endif
#ifndef _MY_DEBUG_
#define _MY_DEBUG_OUTPUT_ stderr
#endif

Lexer::Lexer(void)
//: m_pLexem(nullptr)
{
    state = 0;
    cur = 0;
    LineCounter = 1;
    //m_saved = false;
    //m_c = 0;
    size = 10;
    buf = new char[size];
    buf[0] = 0;
    save = -1;
    ErrorFlag = -1;
    LineBreakFlag = false;
    //memset(&buf, 0, sizeof(buf));
}

Lexer::~Lexer()
{
    delete [] buf;
}

bool isEnding(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' ||  c == '+' || c == '-' || c == '*'|| c == '/'
        || c == '%' || c == '<' || c == '>' || c == '=' || c == ':' || c == ','|| c == ';'
        || c == '&' || c == '|' || c == '!' || c == '(' || c == ')' || c == '[' || c == ']')
        return true;
    else return false;
}

bool isSeparators(char c)
{
    if (c == '+' || c == '-' || c == '*'|| c == '/' || c == '%' || c == '<'|| c == '>'
        || c == '=' || c == ':' || c == ',' || c == ';' || c == '&' || c == '|' || c == '!' || c == '('
        || c == ')' || c == '[' || c == ']')
        return true;
    else return false;
}

void Lexer::initBuf()
{
    for (int i = 0; i <size; i++)
    {
        buf[i] = 0;
    }
}

char * Lexer::extendBuf()
{
    size *= 2;
    char * tmp = new char[size];
    strcpy(tmp,buf);
    return tmp;
}

Lexem * Lexer::start(int c)
{
    initBuf();
    cur = 0;
    if (c == '\n')
        LineCounter++;
    if (LineBreakFlag)
    {
        LineCounter++;
        LineBreakFlag = false;
    }
    else if (isdigit(c))
    {
        buf[cur++] = c;
        state = s_digit;
    }
    else if (c == '"')
    {
        buf[cur++] = c;
        state = s_string;
    }
    else if (c == '$' || c == '@' || c == '?')
    {
        buf[cur++] = c;
        state = s_identifier;
    }
    else if (isalpha(c))
    {
        buf[cur++] = c;
        state = s_keyWord;
    }
    else if (c == ':')
    {
        buf[cur++] = c;
        state = s_assign;
    }
    else if (save == ':' && c == '=')
    {
        buf[cur++] = save;
        buf[cur] = c;
        Lexem * pLexem = new Lexem;
        pLexem->text = strdup(buf);
        pLexem->line = LineCounter;
        pLexem->type = assign;
        save = -1;
        return pLexem;
    }
    else if (isSeparators(c) && (c != ':' || (save != ':' && c != '=')))
    {
        buf[cur] = c;
        Lexem * pLexem = new Lexem;
        pLexem->text = strdup(buf);
        pLexem->line = LineCounter;
        pLexem->type = separator;
        return pLexem;
    }
    else if (c != ' ' && c != '\t' && c != '\n')
    {
        ErrorFlag = start_unknown;
        state = s_error;
    }
    if (save != -1 && c != '=')
    {
        char reserv[2];
        reserv[0] = save;
        reserv[1] = '\0';
        Lexem * pLexem = new Lexem;
        pLexem->text = strdup(reserv);
        pLexem->line = LineCounter;
        if (c == '\n')
            pLexem->line--;
        pLexem->type = separator;
        save = -1;
        reserv[0] = '\0';
        return pLexem;
    }
    return nullptr;
}

Lexem * Lexer::makeDigit(int c)
{
    if (isdigit(c))
    {
        if (cur >= size)
            buf = extendBuf();
        buf[cur++] = c;
    }
    else if (isEnding(c))
    {
        state = s_start;
        Lexem * pLexem = new Lexem;
        if (isSeparators(c))
        {
            save = c;
        }
        pLexem->text = strdup(buf);
        pLexem->type = digit;
        pLexem->line = LineCounter;
        return pLexem;
    }
    else
    {
        if (isalpha(c))
            ErrorFlag = digit_letter;
        else
            ErrorFlag = digit_unknown;
        state = s_error;
    }
    return nullptr;
}

Lexem * Lexer::makeString(int c)
{
    if (c != '"')
    {
        if (cur >= size)
            buf = extendBuf();
        buf[cur++] = c;
    }
    else
    {
        if (cur >= size)
            buf = extendBuf();
        buf[cur] = c;
        state = s_start;
        Lexem * pLexem = new Lexem;
        pLexem->text = strdup(buf);
        pLexem->type = string;
        pLexem->line = LineCounter;
        return pLexem;
    }
    return nullptr;
}

Lexem * Lexer::makeIdentifier(int c)
{
    if (isalnum(c) || c == '_')
    {
        if (cur >= size)
            buf = extendBuf();
        buf[cur++] = c;
    }
    else if (isEnding(c))
    {
        state = s_start;
        Lexem * pLexem = new Lexem;
        if (isSeparators(c))
        {
            save = c;
        }
        pLexem->text = strdup(buf);
        if (buf[0] == '$')
            pLexem->type = varName;
        if (buf[0] == '@')
            pLexem->type = label;
        if (buf[0] == '?')
            pLexem->type = function;
        pLexem->line = LineCounter;
        return pLexem;
    }
    else
    {
        ErrorFlag = id_unknown;
        state = s_error;
    }
    return nullptr;
}

Lexem * Lexer::makeKeyWord(int c)
{
    if (isalpha(c))
    {
        if (cur >= size)
            buf = extendBuf();
        buf[cur++] = c;
    }
    else if (isEnding(c))
    {
        state = s_start;
        Lexem * pLexem = new Lexem;
        if (isSeparators(c))
        {
            save = c;
        }
        if (c == '\n')
            LineBreakFlag = true;
        pLexem->text = strdup(buf);
        pLexem->type = keyWord;
        pLexem->line = LineCounter;
        return pLexem;
    }
    else
    {
        if (isdigit(c))
            ErrorFlag = keyWord_number;
        else
            ErrorFlag = keyWord_unknown;
        state = s_error;
    }
    return nullptr;
}

Lexem * Lexer::makeAssign(int c)
{
    if (c == '=')
    {
        buf[cur] = c;
        state = s_start;
        Lexem *pLexem = new Lexem;
        pLexem->text = strdup(buf);
        pLexem->type = assign;
        pLexem->line = LineCounter;
        return pLexem;
    }
    else
    {
        state = s_start;
        Lexem * pLexem = new Lexem;
        if (isSeparators(c))
        {
            save = c;
        }
        pLexem->text = strdup(buf);
        pLexem->type = separator;
        pLexem->line = LineCounter;
        return pLexem;
    }
    return nullptr;
}

Lexem * Lexer::errorHandling(int c)
{
    Lexem * pLexem = new Lexem;
    pLexem->type = -1;
    pLexem->error = ErrorFlag;
    return pLexem;
}


Lexem * Lexer::step(int c)
{
    switch (state)
    {
        case s_start:
            return start(c);
            break;
        case s_digit:
            return makeDigit(c);
            break;
        case s_string:
            return makeString(c);
            break;
        case s_identifier:
            return makeIdentifier(c);
            break;
        case s_keyWord:
            return makeKeyWord(c);
            break;
        case s_assign:
            return makeAssign(c);
            break;
        case s_error:
            return errorHandling(c);
            break;
    }
    return nullptr;
}



//Lexem * Lexer::step(int c)
//{
    /*
    if (m_pLexem == nullptr)
    {
        m_pLexem = new Lexem;
        m_pLexem ->type = 0;
        m_pLexem ->text = nullptr;
        m_pLexem ->line = 0;
    }
    */
    /*
    if (m_saved == true)
    {
        c = m_c;
    }
    */
    /*
    switch (state)
    {

        case s_start:

            memset(&buf, 0, sizeof(buf));
            cur = 0;
            if (c == '\n')
                LineCounter++;
            if (isnumber(c))
            {
                buf[cur++] = c;
                state = s_digit;
            }
            if (c == '"')
            {
                buf[cur++] = c;
                state = s_string;
            }
            if (c == '$' || c == '@' || c == '?')
            {
                buf[cur++] = c;
                state = s_identificator;
            }
            if (isalpha(c))
            {
                buf[cur++] = c;
                state = s_keyWord;
            }
            if (c == ':')
            {
                buf[cur++] = c;
                state = s_assign;
            }
            if (isSeparators(c) && c != ':')
            {*/
                /*
                ()-i->()-n->()-t->((type_int))
                           \--*-->()-....-> ((var_name))
                */
                /*
                        abc+dddd
                abc:=dddd

                step(a)
                step(b)
                step(c)
                step(:)
                * pLexem
                * m_isFirstOfTwo
                step(:)
                step(=)
                * pLexem
                */
                /*
                aaa,c
                aaa+
                $aaaa:=bbb
                $aaaa bbb

                @label:
                L -> label_name colon

                @label:
                L -> label    RE: "@label[ \t\n]*:"

                @label:
                print('hello');

                LABEL COLON IDENTIFIER LBRACKET STRING RBRACKET SEMICOLON

                //SEMICOLON : {IGNORE} ':'
                //WHITESPACE : {IGNORE} '\t' '\n' ' '
                */
/*
                buf[cur] = c;
                Lexem * pLexem = new Lexem;

                //if (m_saved == true)
                //{
                //    m_saved = false;
                //    pLexem->m_isFirstOfTwo = true;
                //}

                pLexem->text = strdup(buf);
                pLexem->line = LineCounter;
                pLexem -> type = separator;
                return pLexem;
            }
            break;
        case s_digit:
            if (isnumber(c))
            {
                buf[cur++] = c;
            }
            else if (isEnding(c))
            {
                //m_c = c;
                m_saved = true;
                state = s_start;
                Lexem * pLexem = new Lexem;
 */
                //if (m_saved == true)
                //{
                //    m_saved = false;
                //    pLexem->m_isFirstOfTwo = true;
                //}
/*
                if (isSeparators(c))
                {
                    pLexem->m_isFirstOfTwo = true;
                }
                pLexem->text = strdup(buf);
                pLexem->type = digit;
                pLexem->line = LineCounter;
                return pLexem;
            }
            else
            {
                state = s_error;
            }
            break;
        case s_string:
            if (c != '"')
            {
                buf[cur++] = c;
            }
            else
            {
                buf[cur] = c;
                state = s_start;
                Lexem * pLexem = new Lexem;
                pLexem->text = strdup(buf);
                pLexem->type = string;
                pLexem->line = LineCounter;
                return pLexem;
            }
            break;
        case s_identificator:
            if (isalnum(c))
            {
                buf[cur++] = c;
            }
            else if (isEnding(c))
            {
                //m_c = c;
                m_saved = true;
                state = s_start;
                Lexem * pLexem = new Lexem;
 */
                //if (m_saved == true)
                //{
                //    m_saved = false;
                //    pLexem->m_isFirstOfTwo = true;
                //}
 /*

                if (isSeparators(c))
                {
                    pLexem->m_isFirstOfTwo = true;
                }

                pLexem->text = strdup(buf);
                if (buf[0] == '$')
                    pLexem->type = varName;
                if (buf[0] == '@')
                    pLexem->type = label;
                if (buf[0] == '?')
                    pLexem->type = function;
                pLexem->line = LineCounter;
                return pLexem;
            }
            else
            {
                state = s_error;
            }
            break;
        case s_keyWord:
            if (isalpha(c))
            {
                buf[cur++] = c;
            }
            else if (isEnding(c))
            {
                //m_c = c;
                m_saved = true;
                state = s_start;
                Lexem * pLexem = new Lexem;

                if (isSeparators(c))
                {
                    pLexem->m_isFirstOfTwo = true;
                }
*/
                //if (m_saved == true)
                //{
                //    m_saved = false;
                //    pLexem->m_isFirstOfTwo = true;
                //}
/*
                pLexem->text = strdup(buf);
                pLexem->type = TypeLexem::keyWord;
                pLexem->line = LineCounter;
                return pLexem;
            }
            else
            {
                state = s_error;
            }
            break;
        case s_assign:
            if (c == '=')
            {
                buf[cur] = c;
                state = s_start;
                Lexem *pLexem = new Lexem;
                pLexem->text = strdup(buf);
                pLexem->type = separator;
                pLexem->line = LineCounter;
                return pLexem;
            }
            else
            {
                //m_c = c;
                m_saved = true;
                state = s_start;
                Lexem * pLexem = new Lexem;
*/
                //if (m_saved == true)
                //{
                //    m_saved = false;
                //    pLexem->m_isFirstOfTwo = true;
                //}

/*
                if (isSeparators(c))
                {
                    pLexem->m_isFirstOfTwo = true;
                }

                pLexem->text = strdup(buf);
                pLexem->type = TypeLexem::keyWord;
                pLexem->line = LineCounter;
                return pLexem;
            }
            break;
        case s_error:
            fprintf(stderr, "Wrong input\n");
            Lexem * pLexem = new Lexem;
            pLexem->type = -1;
            return pLexem;
    }
    return nullptr;
}
*/

/*
ZLexicalAnalyser:
    ZLexem * getNextLexem();

ZLexem:
    type = {NORMAL, ERROR},
    typeID = {WHILE, OPEN_BRACKET, ID, LESS, NUMBER, CLOSE_BRACKET, INCR, SEMICOLON}
    typeERROR = {EOF, SYSTEM_FAILURE, WRONG_SYMBOL...};
    text = "while"
    pos = Position { filename, line, from, to };

(w) ('(') (xxx) (<) (777) ()) (xxx) (++) (;)

$while( xxx < 777) ffff(xxx) ++;

1) ungetc

2)
bool curExists;
char cur;
char cur[100];

curExists = true;

if (!curExists) cur = getch();

3)

4



while (xx < 5) xx --
yyy = 7 + yy

PLUS -> '+';
ARTH_EXP -> N PLUS N | N '*' N;

        (EOF)

*/
