#include <stdio.h>
#include <math.h>

class NotImplemented
{
public:

};

class AbstractFunction
{
public:
    virtual double Value(double arg) const = 0;
    virtual AbstractFunction * Antiderivative() const = 0;
    double operator()(double arg)
    {
        return Value(arg);
    }
    virtual ~AbstractFunction(){}
};

class Polynomial5 : public AbstractFunction
{
    double cf[6];
public:
    Polynomial5()
    {
        cf[0] = 0; cf[1] = 0; cf[2] = 0; cf[3] = 0; cf[4] = 0; cf[5] = 0;
    }
    virtual double Value(double arg) const
    {
        double sum = 0;
        for (int i = 0; i < 6; i++)
        {
            sum += pow(arg, i) * cf[i];
        }
        return sum;
    }
    double& operator[](int ind)
    {
        return cf[ind];
    }
    AbstractFunction * Antiderivative() const
    {
        Polynomial5  * obj = new Polynomial5();
        if (cf[5])
            throw NotImplemented();
        for (int i = 1; i < 6; i++)
            obj[0][i] = cf[i-1] / (i);
        return obj;
    }
    virtual ~Polynomial5(){}
};

int main()
{
    try
    {
        Polynomial5 pol;
        pol[3] = 100;
        AbstractFunction *f3 = &pol;
        AbstractFunction *f4 = f3->Antiderivative();
        AbstractFunction *f5 = f4->Antiderivative();
        AbstractFunction *f6 = f5->Antiderivative();
        for (int i = 0; i < 6; i++)
        {
            printf("%.2lf ", (*f5)(i));
        }
        printf("\n");
        for (int i = 0; i < 6; i++)
        {
            printf("%.2lf ", (*f6)(i));
        }
        printf("\n");
    }
    catch (NotImplemented)
    {
        printf("Error: not implemented\n");
    }
    return 0;
}
