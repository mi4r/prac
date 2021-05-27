#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct item
{
    int digit;
    struct item * next;
}list;

class SelectiveIntStack
{
    list * stack;
protected:
    virtual bool Check(int a) const = 0;
public:
    SelectiveIntStack()
    {
        stack = 0;
    }
    bool Push(int x)
    {
        if (Check(x))
        {
            list * tmp = new list;
            tmp->digit = x;
            tmp->next = stack;
            stack = tmp;
            return true;
        }
        return false;
    }
    bool Pop(int &x)
    {
        if (stack != 0)
        {
            x = stack->digit;
            list * tmp = stack;
            stack = stack->next;
            delete tmp;
            return true;
        }
        return false;
    }
    virtual ~SelectiveIntStack()
    {
        list * tmp = stack;
        while (stack != 0)
        {
            tmp = stack;
            stack = stack->next;
            delete tmp;
        }
    }
};

class SimpleStack : public SelectiveIntStack
{
    virtual bool Check(int a) const
    {
        return true;
    }
public:
    virtual ~SimpleStack()
    {
    }
};

class OddStack : public SelectiveIntStack
{
    virtual bool Check(int a) const
    {
        return (abs(a) % 2 != 0);
    }
public:
    virtual ~OddStack()
    {
    }
};

class NegativeStack : public SelectiveIntStack
{
    virtual bool Check(int a) const
    {
        return (a < 0);
    }
public:
    virtual ~NegativeStack()
    {
    }
};

class DeciStack : public SelectiveIntStack
{
    int m_last;
    virtual bool Check(int a) const
    {
        return (abs(a) % 10 == m_last);
    }
public:
    DeciStack(int last)
    :m_last(last)
    {
    }
    virtual ~DeciStack()
    {
    }
};

int main()
{
    const int vec[12] = {27, 1, 0, 15, -4, 12, 78, 63, 16, -5, 101, 7};
    SelectiveIntStack *obj[5] = {new SimpleStack, new OddStack, new NegativeStack,
                                 new DeciStack(2), new DeciStack(7)};
    int counters[5] = {0, 0, 0, 0, 0};
    int i, j, x;
    for (i = 0; i < 12; i++)
        for (j = 0; j < 5; j++)
            if (obj[j]->Push(vec[i]))
                counters[j]++;
    for (i = 0; i < 5; i++)
    {
        printf("%2d: ", counters[i]);
        while (obj[i]->Pop(x))
            printf("%3d ", x);
        printf("\n");
    }
    return 0;
}
