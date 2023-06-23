#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct PRODUCTION
{
    char l;
    char r[50];
} prod[50];

int prod_len = 0;
char substr[50] = "";
char start_prod;

// Print utils
void print_prod()
{
    printf("\n");
    for (int i = 0; i < prod_len; i++)
    {
        printf("\n%c -> %s", prod[i].l, prod[i].r);
    }
    printf("\n");
}

void init()
{
    /*
    S –> S + S
    S –> S * S
    S –> id
    */
    start_prod = 'S';

    prod[prod_len].l = 'S';
    strcpy(prod[prod_len].r, "S+S");
    prod_len++;

    prod[prod_len].l = 'S';
    strcpy(prod[prod_len].r, "S*S");
    prod_len++;

    prod[prod_len].l = 'S';
    strcpy(prod[prod_len].r, "i");
    prod_len++;
}

// Parser Stack
char stack[100];
int top = -1;

void push(char in)
{
    stack[++top] = in;
}

void pop()
{
    stack[top--];
}

void substr_stack(int str_count)
{
    int stack_len = top; // don't include $
    memset(substr, '\0', sizeof(substr));

    if (stack_len == -1 || str_count > stack_len)
        return;

    // hello  ; len:5 str_count:3
    // 01234
    strncpy(substr, stack + 1 + (stack_len - str_count), str_count); // +1 to ignore $ of stack
}

void print_op(char input[], int current_index, char action[])
{
    char stack_str[50] = "", input_str[50] = "";
    strncpy(stack_str, stack, top + 1);
    strncpy(input_str, input + current_index, strlen(input) - current_index);

    printf("%-20s | %-20s | %-20s\n", stack_str, input_str, action);
}

void parser(char input[])
{
    int len = strlen(input);
    char action[100];
    int current_input_index = 0;

    printf("\n%-20s | %-20s | %-20s\n", "Stack", "Input", "Action");
    printf("---------------------------------------------------------------------\n");

    push('$');

    while (1)
    {
        // Checking to reduce
        int reduced_flag = 0;

        for (int i = 0; i < prod_len; i++)
        {
            substr_stack(strlen(prod[i].r));

            if (strcmp(prod[i].r, substr) == 0) // Reduce
            {
                sprintf(action, "Reduce By %c->%s", prod[i].l, prod[i].r);
                print_op(input, current_input_index, action);

                for (int j = 0; j < strlen(substr); j++) // Pop RHS elements
                    pop();

                push(prod[i].l);
                reduced_flag = 1;
                break;
            }
        }

        if (!reduced_flag)
        {
            // Accept
            if (stack[top] == start_prod && top == 1 && current_input_index >= len)
            {
                print_op(input, current_input_index, "Accept");
                break;
            }

            // Error
            if (current_input_index >= len)
            {
                print_op(input, current_input_index, "Error");
                break;
            }

            // Shift
            sprintf(action, "Shift: %c", input[current_input_index]);
            print_op(input, current_input_index, action);
            push(input[current_input_index++]);
        }
    }
}

void main()
{
    init();
    printf("=== Production ===");
    print_prod();

    printf("\nEnter input string: ");
    char input[100];
    scanf("%s", input);

    parser(input);
}

/*
    S –> S + S
    S –> S * S
    S –> i

    i+i+i
*/
