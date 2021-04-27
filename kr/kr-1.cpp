#include <stdio.h>

class Prism
{
    double m_h;
public:
    Prism()
    {
    }
    Prism(double h)
    {
        m_h = h;
    }
    ~Prism()
    {
    }
    virtual double Square() const = 0;
    virtual double Volume() const
    {
    }
    double GetH() const
    {
        return m_h;
    }
};

class Box : virtual public Prism
{
    double m_x;
public:
    Box()
    {
    }
    Box(double h, double x)
    :Prism(h)
    {
        m_x = x;
    }
    ~Box()
    {
    }
    virtual double Square() const
    {
        return m_x*m_x;
    }
    virtual double Volume() const
    {
        return Square()*GetH();
    }
};

class Cube : virtual public Box
{
public:
    Cube()
    {
    }
    Cube(double h)
    :Prism(h)
    {
    }
    ~Cube()
    {
    }
    virtual double Square() const
    {
        return GetH()*GetH();
    }
    virtual double Volume() const
    {
        return Square()*GetH();
    }
};

int main()
{
    Prism *p, *q, *r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);
    p = &a;
    q = &b;
    r = &c;
    printf("Squares: %3.3lf %3.3lf %3.3lf\n",p->Square(),q->Square(),r->Square());
    printf("Volumes: %3.3lf %3.3lf %3.3lf\n",p->Volume(),q->Volume(),r->Volume());

    return 0;
}
