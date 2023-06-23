#include <stdio.h>
int E(), T(), F();
char *ip;
char str[50];

int main()
{
    printf("Enter the string: ");
    scanf("%s", str);
    ip = str; // ip points to str[0]

    printf("\n%-8s | %-8s", "Input", "Action");
    printf("\n--------------------------------");

    if (E() && *ip == '\0')
    {
        printf("\n--------------------------------");
        printf("\n\nString is successfully parsed");
    }
    else
    {
        printf("\n--------------------------------");
        printf("\n\nError in parsing String");
    }
}

int E() // E   ->  +TF
{
    printf("\n%-8s | %-8s", ip, "E->+TF");
    if (*ip == '+')
    {
        ip++;
        if (T())
        {
            if (F())
                return 1;
            else
                return 0;
        }
    }
    else
        return 0;
}

int T() // T   ->  ab | a
{
    if (*ip == 'a')
    {
        printf("\n%-8s | %-8s", ip, "T->a");
        ip++;
        if (*ip == 'b')
        {
            printf("\n%-8s | %-8s", ip, "T->ab");
            ip++;
            return 1;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int F() // F   -> TaF | ^
{
    printf("\n%-8s | %-8s", ip, "F->TaF");
    if (T())
    {
        if (*ip == 'a')
        {
            ip++;
            if (F())
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("\n%-8s | %-8s", ip, "F->^");
        return 1;
    }
}

/*
    Productions
    -----------
    E   ->  +TF
    T   ->  ab | a
    F   -> TaF | ^

    Input: +ababaaa
*/