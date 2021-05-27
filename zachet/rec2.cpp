#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

class Reader
{
public:
    virtual int GetChar() = 0;
    virtual ~Reader()
    {
    }
};

class StringReader : public Reader
{
    char * m_str;
    unsigned int cur;
public:
    StringReader(char * str)
    :m_str(str), cur(0)
    {
    }
    ~StringReader()
    {
    }
    virtual int GetChar()
    {
        cur++;
        if (cur-1 < strlen(m_str))
            return m_str[cur-1];
        return EOF;
    }
};

class StdReader : public Reader
{
public:
    StdReader()
    {
    }
    ~StdReader()
    {
    }
    virtual int GetChar()
    {
        int c = getchar();
        return c;
    }
};

class Parser
{
    int m_c;
    Reader * m_pReader;
    void S();
    void T();
    void P();
    void Q();
    void R();
public:
    Parser(Reader * pReader)
    :m_pReader(pReader)
    {
    }
    void analysis();
};

void Parser::analysis()
{
    m_c = m_pReader->GetChar();
    if (m_c == EOF)
        throw 11;
    S();
    if (m_c != EOF)
        throw 12;
}

void Parser::S()
{
    if (m_c == '+')
    {
        m_c = m_pReader->GetChar();
        P();
        S();
    }
    else if (m_c == '<')
    {
        m_c = m_pReader->GetChar();
        Q();
        S();
    }
    else if (m_c == ' ' || m_c == '\t' || m_c == '\n')
    {
        m_c = m_pReader->GetChar();
        S();
    }
    else if (m_c == '!')
    {
        m_c = m_pReader->GetChar();
        T();
    }
    else throw 2;
}

void Parser::T()
{
    if (m_c >= 'a' && m_c <= 'z')
    {
        m_c = m_pReader->GetChar();
        T();
    }
    else if (m_c == ' ' || m_c == '\t' || m_c == '\n')
    {
        m_c = m_pReader->GetChar();
        T();
    }
    else return;
}

void Parser::P()
{
    R();
    if (m_c != '>')
        throw 3;
    m_c = m_pReader->GetChar();
}

void Parser::Q()
{
    R();
    if (m_c != '=')
        throw 4;
    m_c = m_pReader->GetChar();
}

void Parser::R()
{
    if (m_c >= 'a' && m_c <= 'z')
    {
        m_c = m_pReader->GetChar();
        R();
    }
    else if (m_c == '(')
    {
        m_c = m_pReader->GetChar();
        S();
        if (m_c != ')')
            throw 5;
        m_c = m_pReader->GetChar();
    }
    else return;
}

int main(int argc, char **argv)
{
    bool errFlag = false;
    try
    {
        Reader * pReader;
        if (argc >= 2)
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
        errFlag = true;
        printf("NO\n");
    }
    if (!errFlag)
        printf("YES\n");

    return 0;
}