#include <ctype.h>
#include <stdio.h>
#include <string.h>

int top = -1;

// For infix to Postfix
char stack_char[50];
void push(char ch)
{
    stack_char[++top] = ch;
}
char pop()
{
    return stack_char[top--];
}

// For postfix evaluation : string stack
char stack_str[50][5];
void push1(char ch[5])
{
    strcpy(stack_str[++top], ch);
}
char *pop1()
{
    return stack_str[top--];
}

// Helpers
int check_op(char x)
{
    switch (x)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '=':
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
    else if (c == '=')
        return 0;
    else
        return -1;
}

void printOp(char a[5], char b[5], char op, char r[5])
{
    // Note: op is char
    if (op != '=')
        printf("\n%s = %s %c %s", r, a, op, b);
    else
        printf("\n%s = %s", a, b);
}

void main()
{
    char exp[50], op[50], x, y;
    int i, j;

    printf("Enter the expression: ");
    scanf("%[^\n]%*c", exp);

    strcat(exp, ")");
    // i = strlen(exp);
    // exp[i] = ')'; // Adding closing bracket at end of expression for stack evaluation
    // exp[i + 1] = '\0';

    i = j = 0;

    // INFIX TO POSTFIX
    push('(');
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
        else if (!check_op(x))
            op[j++] = x;
        else if (check_op(x))
        {
            y = pop();
            while (priority(y) >= priority(x))
            {
                if (y == x && x == '^') // Left to right associative
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

    printf("\nIntermediate Code:-\n");

    op[j++] = '\0'; // Adding null character for printing
    printf("\nPostfix Format: %s\n", op);

    // POSTFIX EVALUATION
    printf("\nThree Address Format:\n");
    i = 0;
    x = op[i];

    char str_result[5] = "", a[5], b[5];
    char free_num = 1;

    while (x != '\0')
    {
        if (!check_op(x))
        {
            sprintf(str_result, "%c", x);
            push1(str_result);
        }
        else
        {
            // First popped is b not a
            strcpy(b, pop1());
            strcpy(a, pop1());

            sprintf(str_result, "S%d", free_num++);
            push1(str_result);

            printOp(a, b, x, str_result);
        }

        x = op[++i];
    }
}

/*
=======================
Input
=======================
 a=b+c*d


=======================
Ouput
=======================
Intermediate Code:-

Postfix Format: abcd*+=

Three Address Format:

S1 = c * d
S2 = b + S1
a = S2
S
*/