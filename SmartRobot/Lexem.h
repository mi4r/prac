//
// Created by mi4r on 30.03.2021.
//

#ifndef PROJECTSMARTROBOT_LEXEM_H
#define PROJECTSMARTROBOT_LEXEM_H

class Lexem
{
public:
    char * text;
    // unsigned int m_sizeTextBuffer;

    int line;
    int type;
    int error;
    bool m_isFirstOfTwo;
    //void addChar(char ch);
    //void extendTextBuffer();
    void Print();
    void ErrorHandling(int save);
};

#endif //PROJECTSMARTROBOT_LEXEM_H
