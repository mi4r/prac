//
// Created by mi4r on 09.04.2021.
//

#ifndef PROJECTSEGMENTS_BAD_H
#define PROJECTSEGMENTS_BAD_H

class BadSegment
{
};

class BadAddition
{
    float m_A1,m_A2,m_B1,m_B2;
public:
    BadAddition(float A1, float B1, float A2, float B2)
    :m_A1(A1),m_B1(B1), m_A2(A2), m_B2(B2)
    {}

    float GetA1(void) const
    {
        return m_A1;
    }
    float GetA2(void) const
    {
        return m_A2;
    }
    float GetB1(void) const
    {
        return m_B1;
    }
    float GetB2(void) const
    {
        return m_B2;
    }
};

#endif //PROJECTSEGMENTS_BAD_H
