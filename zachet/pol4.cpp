#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class tooHigh
{
    int cf;
public:
    tooHigh(double a){
        cf = a;
    }
    double get() const{
        return cf;
    }
};

class abstractFunction
{
public:
    virtual double value(double arg) const = 0;
    virtual abstractFunction * antiderivative() const = 0;
    void operator()(double arg){
        value(arg);
    }
    virtual ~abstractFunction(){};
};

class polynomial4 : public abstractFunction
{
    double cf[5];
public:
    polynomial4(double arg){
        cf[0] = arg; cf[1] = 0; cf[2] = 0; cf[3] = 0; cf[4] = 0;
    }
    double value(double arg) const{
        double sum = 0;
        for (int i = 0; i < 5; i++){
            sum += pow(arg, i) * cf[i];
        }
        return sum;
    }
    double& operator[](int ind){
        return cf[ind];
    }
    abstractFunction * antiderivative() const{
        polynomial4 * obj = new polynomial4(cf[0]);
        if(cf[4])
            throw tooHigh(cf[4] / 5);
        for(int i = 1; i < 5; i++)
            obj[0][i] = cf[i-1] / (i);
        return obj;
    }
    virtual ~polynomial4(){};
};

int main()
{
    try{
        polynomial4 pol(6);
        pol[1] = 120;
        printf("%.2lf\n", pol[1]);
        abstractFunction *f1 = &pol;
        abstractFunction *f2 = f1 -> antiderivative();
        abstractFunction *f3 = f2 -> antiderivative();
        abstractFunction *f4 = f3 -> antiderivative();
        delete f2; delete f3;
        for (int i = 0; i < 5; i++){
            printf("%.2lf ", (*(polynomial4 *)f4)[i]);
        }
        printf("\n%.2lf %.2lf\n", f4 -> value(1), f4 -> value(2));
        abstractFunction *f5 = f4 -> antiderivative();
        delete f5;
    }
    catch(tooHigh &err){
        printf("Too high %.2lf\n", err.get());
    }
    return 0;
}