#include <stdio.h>
#include "BadAddition.h"

class IntPair
{
    int m_x,m_y;
public:
    virtual int Measure() const = 0;
    /*
    void SetX(int x)
    {
        m_x = x;
    }
    void SetY(int y)
    {
        m_y = y;
    }
     */
    IntPair()
    {
    }
    IntPair(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    ~IntPair()
    {
    }
    int GetX() const
    {
        return m_x;
    }
    int GetY() const
    {
        return m_y;
    }

};

class IntRectangle : virtual public IntPair
{
public:
    IntRectangle()
    {
    }
    IntRectangle(int x, int y)
    : IntPair(x, y)
    {
    }
    ~IntRectangle()
    {
    }

    virtual int Measure() const;

    IntRectangle operator + (const IntRectangle &rec2)
    {
        if (this->GetX() != rec2.GetX() && this->GetX() != rec2.GetY()
            && this->GetY() != rec2.GetX()&& this->GetY() != rec2.GetY())
        {
            throw BadAddition(this->GetX(),this->GetY(), rec2.GetX(), rec2.GetY());
        }
        else
        {
            if (this->GetX() == rec2.GetX() && this->GetX() == rec2.GetY()
                && this->GetY() == rec2.GetX() && this->GetY() == rec2.GetY())
            {
                if (this->GetX() < this->GetY())
                {
                    IntRectangle rectangle(this->GetX(), this->GetY() + rec2.GetX());
                    return rectangle;
                }
                else
                {
                    IntRectangle rectangle(this->GetY(), this->GetX() + rec2.GetX());
                    return rectangle;
                }
            }
            else if (this->GetX() == rec2.GetX())
            {
                IntRectangle rectangle(this->GetX(), this->GetY() + rec2.GetY());
                return rectangle;
            }
            else if (this->GetX() == rec2.GetY())
            {
                IntRectangle rectangle(this->GetX(), this->GetY() + rec2.GetX());
                return rectangle;
            }
            else if (this->GetY() == rec2.GetX())
            {
                IntRectangle rectangle(this->GetY(), this->GetX() + rec2.GetY());
                return rectangle;
            }
            else if (this->GetY() == rec2.GetY())
            {
                IntRectangle rectangle(this->GetY(), this->GetX() + rec2.GetX());
                return rectangle;
            }
        }
    }
};

int IntRectangle::Measure() const
{
    return GetX()*GetY();
}

int main()
{
    try
    {
        IntRectangle a(3, 5), b(5, 7), c(11, 4), d(6, 11);
        IntRectangle p, q;
        p = a + b;
        q = c + d;
        printf("%d\n", (p+q).Measure());
        printf("%d\n", (q+a).Measure());
    }
    catch (const BadAddition &bad)
    {
        printf("Bad addition: (%dx%d)+(%dx%d)\n", bad.GetX1(), bad.GetY1(), bad.GetX2(), bad.GetY2());
    }

    return 0;
}
