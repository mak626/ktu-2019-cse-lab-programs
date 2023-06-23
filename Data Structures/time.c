// C program to demonstrate
// example of time() function.
#include <stdio.h>
#include <time.h>

void mergeSort()
{
    printf("fun() starts \n");
    printf("Press enter to stop fun \n");
    while (1)
    {
        if (getchar())
            break;
    }
    printf("fun() ends \n");
}

int main()
{
    clock_t initial, final;
    initial = clock();

    mergeSort();

    final = clock();
    double time_taken = ((double) final - initial) / CLOCKS_PER_SEC; // in seconds

    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}
