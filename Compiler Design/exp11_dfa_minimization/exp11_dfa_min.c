#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define N 30

int nfa_goto_state[N][N];

int states, actions;
int final[N];
int wanted[N];

int eq[N][N];

void print_head()
{
    printf("%-20s", "State");

    char x = 'A';
    for (int i = 0; i < actions; i++)
    {
        printf("%-20c", x++);
    }
}

void print_dfa()
{
    print_head();

    for (int i = 0; i < states; i++)
    {
        char op[10] = "";
        sprintf(op, "q%d", i);
        printf("\n%-20s", op);

        for (int j = 0; j < actions; j++)
        {
            int dfa_state = nfa_goto_state[i][j];
            char x[3];
            sprintf(x, "q%d", dfa_state);

            if (dfa_state != -1)
                printf("%-20s", x);
            else
                printf("%-20s", "");
        }
    }
}

void init()
{
    printf("\nEnter number of states:");
    scanf("%d", &states);

    printf("Enter number of actions:");
    scanf("%d", &actions);

    for (int i = 0; i < states; i++)
    {
        // not bit mask since DFA
        printf("Enter goto state of q%d on actions order_wise: ", i);
        for (int j = 0; j < actions; j++)
        {
            scanf("%d", &nfa_goto_state[i][j]);
        }
    }

    printf("Enter final states (bit wise):");
    for (int i = 0; i < states; i++)
    {
        scanf("%d", &final[i]);
    }
}

int check_same_eq(int a, int b, int curr_eq_class)
{
    return eq[curr_eq_class][a] == eq[curr_eq_class][b];
}

void traverse(int x)
{
    wanted[x] = 1;

    for (int i = 0; i < actions; i++)
    {
        int idx = nfa_goto_state[x][i];

        if (idx != x && wanted[idx] != 1)
            traverse(idx);
    }
}

void main()
{
    init();
    printf("\n=======================================================");
    printf("\nDFA\n");
    print_dfa();

    traverse(0); // 0 start state
    printf("\n");
    for (int i = 0; i < states; i++)
    {
        if (wanted[i] == 0)
        {
            printf("\nq%d is unreachable", i);
        }
    }

    // First partition of final and non final
    for (int i = 0; i < states; i++)
    {
        eq[0][i] = final[i];
    }

    int curr_free_eq = 2; // 0,1 taken by previous
    int curr_eq_class = 0;

    for (int i = 0; i < curr_free_eq; i++)
    {
        for (int z = 0; z < states; z++)
        {
            eq[curr_eq_class + 1][z] = eq[curr_eq_class][z];
        }

        for (int j = 0; j < states; j++)
        {
            if (wanted[j] == 0)
                continue;

            for (int k = j + 1; k < states; k++)
            {
                if (wanted[k] == 0)
                    continue;

                if (check_same_eq(j, k, curr_eq_class))
                {
                    for (int action = 0; action < actions; action++)
                    {
                        if (!check_same_eq(nfa_goto_state[j][action], nfa_goto_state[k][action], curr_eq_class))
                        {
                            // partition into 2
                            eq[curr_eq_class + 1][k] = curr_free_eq++;
                            break;
                        }
                        else
                        {
                            // same

                            // This case will come since we partition and later it might be the same set
                            if (eq[curr_eq_class + 1][j] != eq[curr_eq_class + 1][k])
                            {
                                eq[curr_eq_class + 1][k] = eq[curr_eq_class + 1][j];
                            }
                        }
                    }
                }
            }
        }

        curr_eq_class++;
    }

    printf("\n=======================================================");
    printf("\nDFA - MINIMIZED\n");
    print_head();
    for (int i = 0; i < curr_free_eq; i++)
    {
        // Check if i exists in eq first
        int exists = 0;
        for (int j = 0; j < states; j++)
        {
            if (eq[curr_eq_class][j] == i)
            {
                exists = 1;
                break;
            }
        }
        if (!exists)
            continue;

        // Otherwise do this

        char temp[5];
        sprintf(temp, "q%d", i);
        printf("\n%-20s", temp);

        for (int action = 0; action < actions; action++)
        {
            for (int k = 0; k < states; k++)
            {
                if (eq[curr_eq_class][k] == i)
                {
                    int new = nfa_goto_state[k][action];
                    sprintf(temp, "q%d ", eq[curr_eq_class][new]);
                    printf("%-20s", temp);
                    break;
                }
            }
        }
    }
}

/*

Input
=======

7
2
1 2
0 3
4 5
4 5
4 5
5 5
4 4
0 0 1 1 1 0 0

Output
=======

Enter number of states:6
Enter number of actions:2
Enter goto state of q0 on actions order_wise: 1 2
Enter goto state of q1 on actions order_wise: 0 3
Enter goto state of q2 on actions order_wise: 4 5
Enter goto state of q3 on actions order_wise: 4 5
Enter goto state of q4 on actions order_wise: 4 5
Enter goto state of q5 on actions order_wise: 5 5
Enter final states (bit wise):0 0 1 1 1 0

=======================================================
DFA
State               A                   B
q0                  q1                  q2
q1                  q0                  q3
q2                  q4                  q5
q3                  q4                  q5
q4                  q4                  q5
q5                  q5                  q5
=======================================================
DFA - MINIMIZED
State               A                   B
q0                  q0                  q1
q1                  q1                  q3
q3                  q3                  q3

*/