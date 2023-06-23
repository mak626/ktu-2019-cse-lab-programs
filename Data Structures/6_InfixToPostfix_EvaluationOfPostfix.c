//Infix to Postfix , Evaluation of Postfix

#include <ctype.h>
#include <math.h>
#include <stdio.h>

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

//For postfix evaluation
float stack1[50];
void push1(float ch)
{
    stack1[++top] = ch;
}
float pop1()
{
    return stack1[top--];
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
    float a, b, values[50];

    printf("Enter the expression:");
    scanf("%[^\n]%*c", exp);

    push('(');
    for (i = 0; exp[i] != '\0'; i++) {} // Getting length of exp
    exp[i] = ')';                       //Adding closing bracket at end of expression for stack evaluation
    exp[i + 1] = '\0';

    i = 0;
    j = 0;

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
                if (y == x && x == '^') //Right to left associative
                {
                    break;
                }
                else
                {
                    op[j++] = y;
                    y = pop();
                }
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
    printf("\nPostfix Expression: %s\n", op);

    /* 
        Getting values for each variable

        Iterates through the postfix expression op[] and replaces the variables by '1' to mark as stored to avoid repetion
        and then stores the orginal value at the proper index in values[] array
    */

    for (i = 0; op[i] != '\0'; i++)
    {
        if (isalpha(op[i]))
        {
            float temp;
            printf("Enter Value for %c :", op[i]);
            scanf("%f", &temp);

            for (int k = i + 1; op[k] != '\0'; k++)
            {
                if (op[k] == op[i])
                {
                    op[k] = '1';
                    values[k] = temp;
                }
            }

            op[i] = '1';
            values[i] = temp;
        }
    }

    //POSTFIX EVALUATION
    i = 0;
    x = op[i];
    while (x != '\0')
    {
        if (!checkop(x))
            push1(values[i]);
        else
        {
            b = pop1();
            a = pop1();

            if (x == '+')
                push1(a + b);
            else if (x == '-')
                push1(a - b);
            else if (x == '/')
                push1(a / b);
            else if (x == '*')
                push1(a * b);
            else if (x == '^')
                push1(pow(a, b));
        }

        x = op[++i];
    }

    printf("\nResult: %.3f", pop1());
}