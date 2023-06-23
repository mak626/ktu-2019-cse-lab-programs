//Infix to Postfix , Evaluation of Postfix

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int top = -1;

//For infix to Postfix
char stack[50];
void push(char ch)
{
    stack[++top] = ch;
}
char pop()
{
    return stack[top--];
}

int checkop(char x)
{
    switch (x)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return 1;

    default:
        return 0;
    }
}

int priority(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void main()
{
    char exp[50], op[50], x, y;
    int i, j;

    printf("Enter the expression:");
    scanf("%[^\n]%*c", exp);

    push('(');

    strrev(exp); //Reversing exp
    //Changing brackets
    for (i = 0; i < strlen(exp); i++)
    {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
    }

    i = strlen(exp); // Getting length of exp
    exp[i] = ')';    //Adding closing bracket at end of expression for stack evaluation
    exp[i + 1] = '\0';

    i = j = 0;

    //INFIX TO POSTFIX
    while (top != -1)
    {
        x = exp[i++];
        if (x == '(')
            push('(');
        else if (x == ')')
        {
            y = pop();
            while (y != '(')
            {
                op[j++] = y;
                y = pop();
            }
        }
        else if (!checkop(x))
            op[j++] = x;
        else if (checkop(x))
        {
            y = pop();
            while (priority(y) >= priority(x))
            {
                op[j++] = y;
                y = pop();
            }
            push(y);
            push(x);
        }
        else
        {
            printf("Invalid Character %c is present.Skipping it", x);
        }
    }
    op[j++] = '\0'; //Adding null character for printing

    strrev(op); //Reversing result
    printf("\nPrefix Expression: %s\n", op);
}