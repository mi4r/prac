#include <stdio.h>

class StateMachine
{
    enum {H, S, A, B, C, error};
    int state;
public:
    StateMachine();
    ~StateMachine();
    void step(int c);
    bool check();
};

StateMachine::StateMachine()
{
    state = H;
}

StateMachine::~StateMachine()
{
}

void StateMachine::step(int c)
{
    switch (state)
    {
        case H:
            if (c == '-')
                state = C;
            else state = error;
            break;
        case A:
            if (c == '<' || c == '=' || c == '-')
            {
            }
            else if (c == '@')
            {
                state = S;
            }
            else state = error;
            break;
        case B:
            if (c == '>' || c == '=' || c == '-')
            {
            }
            else if (c == '*')
            {
                state = S;
            }
            else state = error;
            break;
        case C:
            if (c == '-' || c == '=')
            {
            }
            else if (c == '>')
            {
                state = B;
            }
            else if (c == '<')
            {
                state = A;
            }
            else state = error;
            break;
        case S:
            if (c)
            {
                state = error;
            }
            break;
        case error:
            break;
    }
}

bool StateMachine::check()
{
    if (state == S)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    StateMachine machine;
    int c;
    int cur = 0;
    if (argc >= 2)
    {
        while (argv[1][cur] != 0)
        {
            c = argv[1][cur];
            machine.step(c);
            cur++;
        }
    }
    else
    {
        while ((c = getchar()) != EOF)
        {
            machine.step(c);
        }
        printf("\n");
    }
    if(machine.check())
        printf("YES\n");
    else printf("NO\n");

    return 0;
}
