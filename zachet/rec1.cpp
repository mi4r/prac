#include <stdio.h>
#include <cstring>

class Reader
{
public:
    virtual int GetChar() = 0;
};

class StringReader : virtual public Reader
{
    char * m_str;
    int cur;
public:
    StringReader(char * str)
    {
        m_str = str;
        cur = -1;
    }
    virtual ~StringReader()
    {
    }
    virtual int GetChar()
    {
        cur++;
        if (cur < strlen(m_str))
            return m_str[cur];
        return EOF;
    }
};

class StdReader : virtual public Reader
{
public:
    StdReader()
    {
    }
    virtual int GetChar()
    {
        int c = getchar();
        return c;
    }
    virtual ~StdReader()
    {
    }
};

//const char * setOurSymbols = "()*";

class Parser
{
    int m_c;
    Reader * m_pReader;
    void S();
    void R();
    void N();
    bool checkIn(int ch, const char * strSet);
public:
    Parser(Reader * pReader)
    :m_pReader(pReader)
    {
    }
    ~Parser()
    {
    }
    void analysis();
};

bool Parser::checkIn(int ch, const char * strSet)
{
    //if (strchr())
    for (int i = 0; i < strlen(strSet); ++i)
    {
        if (strSet[i] == ch)
        {
            return true;
        }
    }
    return false;
}

void Parser::S()
{
    if (m_c != '(')
        throw 2;
    m_c = m_pReader->GetChar();
    R();
}

void Parser::R()
{
    if (m_c == '*')
    {
        m_c = m_pReader->GetChar();
        S();
        if (m_c != ')')
            throw 31;
        m_c = m_pReader->GetChar();
    }
    else if (m_c == '(')
    {
        m_c = m_pReader->GetChar();
        N();
        if (m_c != ')')
            throw 32;
        m_c = m_pReader->GetChar();
    } else throw 33;
}

void Parser::N()
{
    if (m_c != '(' && m_c != ')' && m_c != '*' && m_c != EOF)
    {
        m_c = m_pReader->GetChar();
        N();
    }
    else if (m_c == '(')
    {
        m_c = m_pReader->GetChar();
        R();
        N();
    }
    else if (m_c == ')')
        return;
}

void Parser::analysis()
{
    m_c = m_pReader->GetChar();
    if (m_c == EOF)
        throw 11;
    S();
    if (m_c != EOF)
        throw 12;
}


#define DBG
int main(int argc, char **argv)
{
    bool err_flag = false;
    try
    {
        Reader * pReader;
        if(argc >= 2)
        {
            pReader = new StringReader(argv[1]);
        }
        else
        {
            pReader = new StdReader;
        }
        Parser parser(pReader);
        parser.analysis();
    }
    catch (int errcode)
    {
        err_flag = true;
        printf("NO\n");
#ifdef DBG
        printf("NO err:%i\n",errcode);
#endif
    }
    if (!err_flag)
    {
        printf("YES\n");
    }

    return 0;
}






/*
void Parser::N()
{
    if (!checkIn(m_c, setOurSymbols))
    {
        m_c = m_pReader->GetChar();
        N();
    }
    else if (m_c == '(')
    {
        m_c = m_pReader->GetChar();
        R();
        m_c = m_pReader->GetChar();
        N();
    }
    else throw 4;
}
*/