//M ASWIN KISHORE 41
//Sum of polynomials
#include <stdio.h>

void main()
{
    int n1, n2, i, j, z, x[20], y[20], sum[20];
    printf("\nFirst Polynomial");
    printf("\nEnter the no. of terms:");
    scanf("%d", &n1);
    n1 *= 2;
    printf("\nEnter the terms of polynomial 1 in DESCENDING ORDER OF POWER as : coefficient power\n");
    for (i = 0, j = 0; i < n1; i += 2, j++)
    {
        printf("Enter term %d:", j + 1);
        scanf("%d %d", &x[i], &x[i + 1]);
    }

    printf("\nSecond Polynomial");
    printf("\nEnter the no. of terms:");
    scanf("%d", &n2);
    n2 *= 2;
    printf("\nEnter the terms of polynomial 2 in DESCENDING ORDER OF POWER as : coefficient power\n");

    for (i = 0, j = 0; i < n2; i += 2, j++)
    {
        printf("Enter term %d:", j + 1);
        scanf("%d %d", &y[i], &y[i + 1]);
    }

    //Addition
    i = j = z = 0;
    while (i < n1 && j < n2)
    {
        if (x[i + 1] > y[j + 1])
        {
            sum[z] = x[i];
            sum[z + 1] = x[i + 1];
            i += 2;
        }

        else if (x[i + 1] < y[j + 1])
        {
            sum[z] = y[j];
            sum[z + 1] = y[j + 1];
            j += 2;
        }

        else
        {
            sum[z] = x[i] + y[j];
            sum[z + 1] = x[i + 1];
            i += 2;
            j += 2;
        }
        z += 2;
    }

    while (i < n1)
    {
        sum[z] = x[i];
        sum[z + 1] = x[i + 1];
        i += 2;
        z += 2;
    }

    while (j < n2)
    {
        sum[z] = y[j];
        sum[z + 1] = y[j + 1];
        j += 2;
        z += 2;
    }

    printf("\nThe sum of polynomials is:\n");

    for (i = 0; i < z; i += 2)
    {
        printf("%dx^%d", sum[i], sum[i + 1]);
        if (i + 2 != z)
            printf(" + "); //to avoid printing + at last element
    }
}
