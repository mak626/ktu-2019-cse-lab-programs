#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*

=====================
How input is derived
=======================
Reference TOC Diagram: https://www.tutorialspoint.com/what-is-an-epsilon-closure-in-toc


    E   A   B    C
QO  Q1  Q0  {}  {}
Q1  Q2  {}  Q1  {}
Q2  {}  {}  {}  Q2

    E    A    B    C
QO  010  001  000  000              q2q1q0 (bitmask)
Q1  100  000  010  000
Q2  000  000  000  100

In integer (input is integer)

    E    A    B    C
QO  2   1     0    0              q2q1q0 (bitmask)
Q1  4   0     2    0
Q2  0   0     0    4

*/

#define N 30

int nfa_goto_state[N][N];

int states, actions;
int printedStates[N];

int get_bit(int num, int pos)
{
    return (num >> pos) & 1;
}

void print_state(int state)
{
    char op[100] = "{";
    for (int k = 0; k < states; k++)
    {
        int valid = get_bit(state, k); // Get each bit one by one : q0,q1,q2..
        if (valid)
        {
            char op1[50] = "";
            sprintf(op1, " q%d", k);
            strcat(op, op1);
        }
    }
    strcat(op, " }");
    printf("%-20s", op);
}

void print_head()
{
    printf("%-20s", "State");

    printf("%-20c", 'E');

    char x = 'A';
    for (int i = 0; i < actions - 1; i++)
    {
        printf("%-20c", x++);
    }
}

void print_nfa()
{
    print_head();

    for (int i = 0; i < states; i++)
    {
        char op[10] = "";
        sprintf(op, "q%d", i);
        printf("\n%-20s", op);

        for (int j = 0; j < actions; j++)
        {
            int nfa_state = nfa_goto_state[i][j];
            print_state(nfa_state);
        }
    }
}

void init()
{

    printf("\nEnter number of states:");
    scanf("%d", &states);

    printf("Enter number of actions (including epsilon):");
    scanf("%d", &actions);

    for (int i = 0; i < states; i++)
    {
        printf("Enter state mask of q%d on actions order_wise starting with epsilon: ", i);
        for (int j = 0; j < actions; j++)
        {
            scanf("%d", &nfa_goto_state[i][j]);
        }
    }
}

void traverse(int stateIndex)
{
    int gotoStateOfEpsilon = nfa_goto_state[stateIndex][0]; // 0 is reserved for epsilon

    if (gotoStateOfEpsilon == 0) // No where to go
        return;
    else
    {
        for (int j = 0; j < states; j++)
        {
            int valid = get_bit(gotoStateOfEpsilon, j); // Get each bit one by one : q0,q1,q2..

            if (valid && !printedStates[j]) // This state is present and not already printed before
            {
                printf(" q%d", j);
                printedStates[j] = 1;
                traverse(j);
            }
        }
    }
}

void epsilonClosure()
{
    printf("Epsilon Closure");
    for (int i = 0; i < states; i++)
    {
        memset(printedStates, 0, sizeof(printedStates)); // Initialize all states to 0. To prevent avoid duplicate printing

        printf("\nq%d: { q%d", i, i); // itself
        printedStates[i] = 1;
        traverse(i);
        printf("}");
    }
}

void main()
{
    init();
    printf("\n=======================================================");
    printf("\nNFA\n");
    print_nfa();
    printf("\n=======================================================\n\n");

    epsilonClosure();
}

/*
Input
=======

3
4
2 1 0 0
4 0 2 0
0 0 0 4


Output
=======

Enter number of states:3
Enter number of actions (including epsilon):4
Enter state mask of q0 on actions order_wise starting with epsilon: 2 1 0 0
Enter state mask of q1 on actions order_wise starting with epsilon: 4 0 2 0
Enter state mask of q2 on actions order_wise starting with epsilon: 0 0 0 4

=======================================================
NFA
State               E                   A                   B                   C
q0                  { q1 }              { q0 }              { }                 { }
q1                  { q2 }              { }                 { q1 }              { }
q2                  { }                 { }                 { }                 { q2 }
=======================================================

Epsilon Closure
q0: { q0 q1 q2}
q1: { q1 q2}
q2: { q2}

*/