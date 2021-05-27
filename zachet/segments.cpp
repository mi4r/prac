#include <stdio.h>
#include "Bad.h"

class FloatPair
{
    float m_a, m_b;
public:
    virtual float Measure() const = 0;
    /*
    void SetA(float a)
    {
        m_a = a;
    }
    void SetB(float b)
    {
        m_b = b;
    }
    */
    FloatPair()
    {
    }
    FloatPair(float a, float b)
    {
        m_a = a;
        m_b = b;
    }
    ~FloatPair()
    {
    }
    float GetA() const
    {
        return m_a;
    }
    float GetB() const
    {
        return m_b;
    }
};

class Segment: virtual public FloatPair
{
public:
    Segment()
    {
    }
    Segment(float a, float b);
    virtual float Measure() const;
    ~Segment()
    {
    }
    Segment operator+(const Segment &seg2)
    {
        //seg2.m_a + this.m_a;
        if (this->GetB() < seg2.GetA() || seg2.GetB() < this->GetA())
        {
            //BadAddition bad(this->m_a, this->m_b, seg2.m_a, seg2.m_b);
            //throw bad;
            //BadAddition ba(this->m_a, this->m_b, seg2.m_a, seg2.m_b);
            throw BadAddition(this->GetA(), this->GetB(), seg2.GetA(), seg2.GetB());
        } else
        {
            if (this->GetA() > seg2.GetA() && this->GetB() < seg2.GetB())
            {
                Segment segment(seg2.GetA(), seg2.GetB());
                return segment;
            }
            else if (this->GetA() > seg2.GetA() && this->GetB() >= seg2.GetB())
            {
                Segment segment(seg2.GetA(), this->GetB());
                return segment;
            }
            else if ((this->GetA() <= seg2.GetA() && this->GetB() < seg2.GetB()))
            {
                Segment segment(this->GetA(), seg2.GetB());
                return segment;
            }
            else
            {
                Segment segment(this->GetA(), this->GetB());
                return segment;
            }
            /*
            Segment segment;
            if (this->GetA() > seg2.GetA())
                segment.SetA(seg2.GetA());
            else segment.SetA(this->GetA());
            if (this->GetB() < seg2.GetB())
                segment.SetB(seg2.GetB());
            else segment.SetB(this->GetB());
            return segment;
             */
        }
    }
};

Segment::Segment(float a, float b)
:FloatPair(a,b)
{
    if (a>b)
        throw BadSegment();
}

float Segment::Measure() const
{
    float len = GetB() - GetA();
    return len;
}

int main()
{
    try
    {
        Segment f(1, 2), g(0.5, 5), h(2.5, 6.5);
        printf("%3.3f, %3.3f, %3.3f\n", (f+g).Measure(), (g+h).Measure(), (f+g+h).Measure());
        //f.operator+(g)
        printf("%3.3f\n", (f+h).Measure());
    }
    catch (const BadAddition &bad)
    {
        printf("Bad addition: [%3.3f; %3.3f]+[%3.3f, %3.3f]\n", bad.GetA1(), bad.GetB1(), bad.GetA2(), bad.GetB2());
    }
    catch (BadSegment b)
    {
        printf("Bad segment\n");
    }

    return 0;
}
