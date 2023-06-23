#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define N 30

/*
    0   1   1     = 3 (bitmask representing q0 can go to q0,q1)
    q2  q1  q0

    Represent States

        a        b
    qo  011     000   => indicates qo can go to q1 and q0 through a
    q1  000     100
    q2  000     000
*/
int nfa_goto_state[N][N];
int dfa_goto_state[N][N];

int dfa_state[N]; // check what is on left side (combination of states) like q0, q0q1q2,  ..
int dfa_state_curr = 0;

int states, actions;

int get_bit(int num, int pos)
{
    return (num >> pos) & 1;
}

int dfa_state_exists(int state)
{
    for (int i = 0; i < dfa_state_curr + 1; i++)
    {
        if (dfa_state[i] == state)
            return 1;
    }

    return 0;
}

void traverse(int nfa_state)
{
    int curr_state = dfa_state_curr;
    dfa_state[curr_state] = nfa_state;

    for (int action = 0; action < actions; action++)
    {
        for (int j = 0; j < states; j++)
        {
            int valid = get_bit(nfa_state, j); // Get each bit one by one : q0,q1,q2..

            if (valid)                                                           // This state is present
                dfa_goto_state[curr_state][action] |= nfa_goto_state[j][action]; // Or operation
        }

        if (!dfa_state_exists(dfa_goto_state[curr_state][action]))
        {
            traverse(dfa_goto_state[dfa_state_curr++][action]);
        }
    }
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

    char x = 'A';
    for (int i = 0; i < actions; i++)
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

void print_dfa()
{
    print_head();

    for (int i = 0; i <= dfa_state_curr; i++)
    {
        printf("\n");
        print_state(dfa_state[i]);
        for (int j = 0; j < actions; j++)
        {
            int dfa_state = dfa_goto_state[i][j];
            print_state(dfa_state);
        }
    }
}

void init()
{
    // Testing : Uncomment following and comment the lines after that
    /*
        states = 3;
        actions = 2;

        nfa_goto_state[0][0] = 3;
        nfa_goto_state[0][1] = 1;
        nfa_goto_state[1][0] = 0;
        nfa_goto_state[1][1] = 4;
        nfa_goto_state[2][0] = 0;
        nfa_goto_state[2][1] = 0;
    */

    printf("\nEnter number of states:");
    scanf("%d", &states);

    printf("Enter number of actions:");
    scanf("%d", &actions);

    for (int i = 0; i < states; i++)
    {
        printf("Enter state mask of q%d on actions order_wise: ", i);
        for (int j = 0; j < actions; j++)
        {
            scanf("%d", &nfa_goto_state[i][j]);
        }
    }
}

void main()
{
    init();
    printf("\n=======================================================");
    printf("\nNFA\n");
    print_nfa();

    /*
        q0 state = 001
        q2q1q0 = 001
    */
    traverse(1);

    printf("\n\n=======================================================");
    printf("\nDFA\n");
    print_dfa();
}

/*
Input
=======

3
2
3 1
0 4
0 0


Output
=======

Enter number of states:3
Enter number of actions:2
Enter state mask of q0 on actions order_wise: 3 1
Enter state mask of q1 on actions order_wise: 0 4
Enter state mask of q2 on actions order_wise: 0 0

=======================================================
NFA
State               A                   B
q0                  { q0 q1 }           { q0 }
q1                  { }                 { q2 }
q2                  { }                 { }

=======================================================
DFA
State               A                   B
{ q0 }              { q0 q1 }           { q0 }
{ q0 q1 }           { q0 q1 }           { q0 q2 }
{ q0 q2 }           { q0 q1 }           { q0 }

*/