#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
    E -> E + T | T
    T -> T * F | F
    F -> id | (E)
*/

struct PRODUCTION
{
    char l;
    char r[50][20];
    char first[20];         // first of E (includes all r prodn)
    char first_sep[50][20]; // For table: To show r prodn first seperately
    char follow[20];
    int r_len;
    int first_len;
    int follow_len;
} prod[50];

int prod_len = 0;
char start_prod;

int current_free_char = 'A';

int table_L_index[50][50]; // holds index of L part of prod
int table_R_index[50][50]; // holds index of R part of prod

char terminals[50];
int terminals_len = 0;

// Helper
int array_contains(char *x, char v)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (x[i] == v)
            return 1;
    }
    return 0;
}

int get_prod_index(char x)
{
    for (int i = 0; i < prod_len; ++i)
    {
        if (prod[i].l == x)
            return i;
    }
    return -1;
}

int get_terminal_index(char x)
{
    for (int i = 0; i < terminals_len; ++i)
    {
        if (terminals[i] == x)
            return i;
    }
    return -1;
}

// Print utils
void print_prod()
{
    printf("\n");
    for (int i = 0; i < prod_len; i++)
    {
        printf("\n%c -> ", prod[i].l);
        for (int j = 0; j < prod[i].r_len; j++)
        {
            printf("%s", prod[i].r[j]);
            if (j + 1 != prod[i].r_len)
                printf(" | ");
        }
    }
    printf("\n");
}

void print_first()
{
    printf("\n=== First ===");
    printf("\n");
    for (int i = 0; i < prod_len; i++)
    {
        printf("\n%c: ", prod[i].l);
        for (int j = 0; j < prod[i].first_len; j++)
        {
            printf("%c ", prod[i].first[j]);
        }
    }
    printf("\n");
}

void print_follow()
{
    printf("\n=== Follow ===");
    printf("\n");
    for (int i = 0; i < prod_len; i++)
    {
        printf("\n%c: ", prod[i].l);
        for (int j = 0; j < prod[i].follow_len; j++)
        {
            printf("%c ", prod[i].follow[j]);
        }
    }
    printf("\n");
}

void print_parsing_table()
{
    printf("\n=== Parsing Table ===\n");
    printf("\n%-5s", "");
    char temp[50];
    for (int i = 0; i < terminals_len; i++)
    {
        sprintf(temp, "%c", terminals[i]);
        printf("%-10s", temp);
    }

    for (int i = 0; i < prod_len; i++)
    {
        sprintf(temp, "%c", prod[i].l);
        printf("\n%-5s", temp);
        for (int j = 0; j < terminals_len; j++)
        {
            int prod_i = table_L_index[i][j];
            int sub_i = table_R_index[i][j];

            if (prod_i != -1 && sub_i != -1)
            {
                sprintf(temp, "%c->%s", prod[i].l, prod[i].r[sub_i]);
                printf("%-10s", temp);
            }
            else
                printf("%-10s", "");
        }
    }
    printf("\n");
}

// Handlers

void remove_left_recursion()
{
    printf("\n=== Removing Left Recursion === ");
    for (int i = 0; i < prod_len; ++i)
    {
        int flag[100] = {0};       // Represents which prod in r array prodn are recursive
        int is_left_recursive = 0; // Represents if any of r array prodn are recursive

        for (int j = 0; j < prod[i].r_len; ++j)
        {
            if (prod[i].l == prod[i].r[j][0])
            {
                flag[j] = 1;
                is_left_recursive = 1;
            }
        }

        if (is_left_recursive)
        {
            int old_r_len = 0;

            int new_r_len = 0;
            struct PRODUCTION *new_prod = &prod[prod_len];

            new_prod->l = current_free_char;

            for (int j = 0; j < prod[i].r_len; ++j)
            {
                if (flag[j] == 1)
                {
                    /*
                        E -> E*F

                        New prod: A -> *FA
                        Copy *FA in new prod to prod[new].r
                    */
                    //                                                +1 to remove the left recursive char : E*F -> *F
                    sprintf(new_prod->r[new_r_len++], "%s%c", prod[i].r[j] + 1, new_prod->l);
                }
                else
                {
                    // Convert non recursive terms like E->T to E -> TA
                    sprintf(prod[i].r[old_r_len++], "%s%c", prod[i].r[j], new_prod->l);
                }
            }

            // Change length of old prod
            prod[i].r_len = old_r_len;

            // Add null production
            strcpy(new_prod->r[new_r_len++], "^");
            new_prod->r_len = new_r_len;

            current_free_char++;
            prod_len++;
        }
    }
}

int first(char x) // Returns index of prod with L == x
{
    int index = get_prod_index(x);

    if (index == -1)
    {
        printf("Error: no prod %c", x);
        return -1;
    }

    struct PRODUCTION *old_prod = &prod[index];

    // If already calculated skip
    if (old_prod->first_len != 0)
        return index;

    int first_len = 0;

    for (int i = 0; i < old_prod->r_len; ++i)
    {
        char right_first_char = old_prod->r[i][0];

        if (isupper(right_first_char)) // Non-Terminal
        {
            int new_index = first(right_first_char);
            struct PRODUCTION *new_prod = &prod[new_index];

            // Copying first of new_prod to old_prod
            for (int j = 0; j < new_prod->first_len; j++)
            {
                old_prod->first[first_len++] = new_prod->first[j];
            }

            sprintf(old_prod->first_sep[i], "%s", new_prod->first);
        }
        else // Terminal
        {
            old_prod->first[first_len++] = right_first_char;
            sprintf(old_prod->first_sep[i], "%c", right_first_char);
        }
    }

    old_prod->first_len = first_len;
    return index;
}

// Follow helpers
int follow(char x); // Function definition to use follow before its declared

void handle_follow_left(int i, int index, int *follow_len)
{
    int new_index = follow(prod[i].l);
    struct PRODUCTION *old_prod = &prod[index];
    struct PRODUCTION *new_prod = &prod[new_index];

    // Copy each char of follow of new_prod into old_prod
    for (int j = 0; j < new_prod->follow_len; j++)
    {
        if (!array_contains(old_prod->follow, new_prod->follow[j])) // prevent duplicates in follow array
            old_prod->follow[(*follow_len)++] = new_prod->follow[j];
    }
}

void handle_follow_terminal(int index, int *follow_len, char terminal)
{
    struct PRODUCTION *old_prod = &prod[index];

    if (!array_contains(old_prod->follow, terminal)) // prevent duplicates
        old_prod->follow[(*follow_len)++] = terminal;
}

void handle_follow_non_terminal(int i, int j, int k, int index, int *follow_len, char right_of_x)
{
    int new_index = first(right_of_x);
    struct PRODUCTION *old_prod = &prod[index];
    struct PRODUCTION *new_prod = &prod[new_index];

    for (int l = 0; l < new_prod->first_len; l++)
    {
        if (new_prod->first[l] == '^') // If first of right_of_x has null
        {
            char right_second_of_x = prod[i].r[j][k + 2];

            if (right_second_of_x == '\0')
            {
                handle_follow_left(i, index, follow_len);
            }
            else if (isupper(right_second_of_x))
            {
                handle_follow_non_terminal(i, j, k + 1, index, follow_len, right_second_of_x);
            }
            else
            {
                handle_follow_terminal(index, follow_len, right_second_of_x);
            }
        }
        else
        {
            handle_follow_terminal(index, follow_len, new_prod->first[l]);
        }
    }

    *follow_len = strlen(old_prod->follow);
}

int follow(char x)
{
    int index = get_prod_index(x);
    struct PRODUCTION *old_prod = &prod[index];

    if (index == -1)
    {
        printf("\nError: no prod %c", x);
        return -1;
    }

    // If already calculated skip
    if (old_prod->follow_len != 0)
        return index;

    int follow_len = 0;

    if (start_prod == x) // x is a starting symbol. Then add $ to its follow
    {
        old_prod->follow[follow_len++] = '$';
    }

    // Search for prod that has x in right side
    for (int i = 0; i < prod_len; i++)
    {

        if (prod[i].l == x) // avoid productions of itself because it causes infinite recursion
            continue;

        for (int j = 0; j < prod[i].r_len; j++)
        {
            // Iterate through each char of prod[i].r[j] to find x
            for (int k = 0; k < strlen(prod[i].r[j]); k++)
            {
                if (x == prod[i].r[j][k])
                {
                    char right_of_x = prod[i].r[j][k + 1];

                    if (right_of_x == '\0') // Null Case
                    {
                        // Take follow of Left side of prod
                        handle_follow_left(i, index, &follow_len);
                    }
                    else if (isupper(right_of_x))
                    {
                        // Non-Terminal. Take first(right of x)
                        handle_follow_non_terminal(i, j, k, index, &follow_len, right_of_x);
                    }
                    else
                    {
                        // terminal
                        handle_follow_terminal(index, &follow_len, right_of_x);
                    }
                }
            }
        }
    }

    old_prod->follow_len = follow_len;
    return index;
}

void calc_first_follow()
{
    for (int i = 0; i < prod_len; i++)
        first(prod[i].l);

    for (int i = 0; i < prod_len; i++)
        follow(prod[i].l);
}

void parsing_table()
{
    // Reset parsing table with -1 values
    memset(table_L_index, -1, sizeof(table_L_index));
    memset(table_R_index, -1, sizeof(table_R_index));

    // Find all terminals
    for (int i = 0; i < prod_len; i++)
    {
        for (int j = 0; j < strlen(prod[i].first); j++)
        {
            char terminal = prod[i].first[j];
            if (terminal == '^')
                continue;
            if (!array_contains(terminals, terminal))
            {
                terminals[terminals_len++] = terminal;
            }
        }
        for (int j = 0; j < strlen(prod[i].follow); j++)
        {
            char terminal = prod[i].follow[j];
            if (!array_contains(terminals, terminal))
            {
                terminals[terminals_len++] = terminal;
            }
        }
    }

    for (int i = 0; i < prod_len; i++)
    {
        for (int j = 0; j < prod[i].r_len; j++)
        {
            char *first = prod[i].first_sep[j];

            for (int k = 0; k < strlen(first); k++)
            {
                int index = get_terminal_index(first[k]);
                if (index == -1) // Null
                {
                    char *follow = prod[i].follow;
                    for (int z = 0; z < strlen(follow); z++)
                    {
                        int follow_index = get_terminal_index(follow[z]);
                        table_L_index[i][follow_index] = i;
                        table_R_index[i][follow_index] = j;
                    }
                }
                else
                {
                    table_L_index[i][index] = i;
                    table_R_index[i][index] = j;
                }
            }
        }
    }
}

void init()
{
    start_prod = 'E';

    prod[prod_len].l = 'E';
    strcpy(prod[prod_len].r[0], "E+T");
    strcpy(prod[prod_len].r[1], "T");
    prod[prod_len].r_len = 2;
    prod_len++;

    prod[prod_len].l = 'T';
    strcpy(prod[prod_len].r[0], "T*F");
    strcpy(prod[prod_len].r[1], "F");
    prod[prod_len].r_len = 2;
    prod_len++;

    prod[prod_len].l = 'F';
    strcpy(prod[prod_len].r[0], "i");
    strcpy(prod[prod_len].r[1], "(E)");
    prod[prod_len].r_len = 2;
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

// Parsing Input String
void parser(char input[])
{
    printf("\n\n=== Parsing input ===\n");

    push('$');
    push(start_prod);

    strcat(input, "$"); // input = input$
    char *curr = input;

    printf("\n%-10s | %-10s | %-10s", "Stack", "Input", "Production");
    printf("\n---------------------------------------------");

    while (stack[top] != '$')
    {
        if (stack[top] == *curr)
        {
            // Printing stack only
            char stack_str[100] = "";
            strncpy(stack_str, stack, top + 1);
            printf("\n%-10s | %-10s | %-10s", stack_str, curr, "");

            pop();
            curr++;
        }
        else if (islower(stack[top])) // Terminal Check
        {
            printf("\nError: Terminal %c", stack[top]);
            break;
        }
        else
        {
            int row_non_terminal = get_prod_index(stack[top]);
            int col_terminal = get_terminal_index(*curr);

            int index = table_L_index[row_non_terminal][col_terminal];
            int r_index = table_R_index[row_non_terminal][col_terminal];

            if (index == -1 && r_index == -1)
            {
                printf("\nError: no entry found");
                break;
            }
            else
            {
                char r[100];
                strcpy(r, prod[index].r[r_index]);

                // Printing current prod
                char stack_str[200] = "";
                char prod_str[200] = "";

                strncpy(stack_str, stack, top + 1); // Returns stack as string upto TOP
                sprintf(prod_str, "%c -> %s", prod[index].l, r);

                printf("\n%-10s | %-10s | %-10s", stack_str, curr, prod_str);

                // Remaing operations
                pop();

                for (int i = strlen(r) - 1; i >= 0; i--)
                {
                    // push right side of prod in reverse order
                    if (r[i] != '^') // dont push null prodn
                        push(r[i]);
                }
            }
        }
    }

    if (stack[top] == '$')
        printf("\n\nString parsed successfully\n");
    else
        printf("\n\nString cannot be parsed\n");
}

void main()
{
    init();
    printf("=== Production ===");
    print_prod();

    remove_left_recursion();
    print_prod();

    calc_first_follow();
    print_first();
    print_follow();

    parsing_table();
    print_parsing_table();

    printf("\nEnter input string: ");
    char input[100];
    scanf("%s", input);

    parser(input);
}

/*
======================================
Input
======================================

i+i*i

======================================
Output
======================================

=== Production ===

E -> E+T | T
T -> T*F | F
F -> i | (E)

=== Removing Left Recursion ===

E -> TA
T -> FB
F -> i | (E)
A -> +TA | ^
B -> *FB | ^

=== First ===

E: i (
T: i (
F: i (
A: + ^
B: * ^

=== Follow ===

E: $ )
T: + $ )
F: * + $ )
A: $ )
B: + $ )

=== Parsing Table ===

     i         (         $         )         +         *
E    E->TA     E->TA
T    T->FB     T->FB
F    F->i      F->(E)
A                        A->^      A->^      A->+TA
B                        B->^      B->^      B->^      B->*FB

Enter input string: i+i*i


=== Parsing input ===

Stack      | Input      | Production
---------------------------------------------
$E         | i+i*i$     | E -> TA
$AT        | i+i*i$     | T -> FB
$ABF       | i+i*i$     | F -> i
$ABi       | i+i*i$     |
$AB        | +i*i$      | B -> ^
$A         | +i*i$      | A -> +TA
$AT+       | +i*i$      |
$AT        | i*i$       | T -> FB
$ABF       | i*i$       | F -> i
$ABi       | i*i$       |
$AB        | *i$        | B -> *FB
$ABF*      | *i$        |
$ABF       | i$         | F -> i
$ABi       | i$         |
$AB        | $          | B -> ^
$A         | $          | A -> ^

String parsed successfully

*/
