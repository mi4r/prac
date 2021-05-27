//
// Created by mi4r on 10.04.2021.
//

#ifndef PROJECTRECTANGLE_BADADDITION_H
#define PROJECTRECTANGLE_BADADDITION_H

class BadAddition
{
    int m_x1, m_x2, m_y1, m_y2;
public:
    BadAddition(int x1, int y1, int x2, int  y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2)
    {}
    int GetX1() const
    {
        return m_x1;
    }
    int GetX2() const
    {
        return m_x2;
    }
    int GetY1() const
    {
        return m_y1;
    }
    int GetY2() const
    {
        return m_y2;
    }
};

#endif //PROJECTRECTANGLE_BADADDITION_H
