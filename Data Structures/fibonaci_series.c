#include <stdio.h>

void fibonaci_recursive(int n1, int n2, int terms)
{
    if (terms == 0)
        return;

    // First  two nos.
    if (n1 == 0 && n2 == 1 && terms >= 1)
    {
        printf("0 ");
        fibonaci_recursive(n2, n1 + n2, --terms);
    }
    else if (n1 == 1 && n2 == 1 && terms >= 2)
    {
        printf("1 ");
        fibonaci_recursive(n2, n1 + n2, --terms);
    }

    //Remaining 
    else
    {
        printf("%d ", n2);
        fibonaci_recursive(n2, n1 + n2, --terms);
    }
}

void main()
{
    int terms = 1;
    fibonaci_recursive(0, 1, terms);
}