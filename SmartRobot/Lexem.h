//
// Created by mi4r on 30.03.2021.
//

#ifndef PROJECTSMARTROBOT_LEXEM_H
#define PROJECTSMARTROBOT_LEXEM_H

class Lexem
{
public:
    char * text;
    int line;
    int type;
    int errStatus;
    int readiness;
    bool ending;
    Lexem();
    void Print();
    void ErrorHandling();
};

#endif //PROJECTSMARTROBOT_LEXEM_H
