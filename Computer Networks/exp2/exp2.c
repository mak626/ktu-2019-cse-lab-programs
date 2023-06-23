/*
    M ASWIN KISHORE
    41 S6 CS2
    EXP2 : FORK IMPLEMENTATION
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void bubbleSortAsc(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void main()
{
    int arr[30], len;
    printf("Enter the no. of elements: ");
    scanf("%d", &len);

    printf("Enter elements: ");
    for (int i = 0; i < len; i++)
        scanf("%d", &arr[i]);

    bubbleSortAsc(arr, len);

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nIn Child Process. Array in DESC: ");
        for (int i = len - 1; i >= 0; i--)
            printf("%d ", arr[i]);
        printf("\n");
    }

    else if (pid > 0)
    {
        printf("\nIn Parent Process. Array in ASC: ");
        for (int i = 0; i < len; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    else if (pid < 0)
    {
        printf("Fork Failed!");
    }
}

/*
5
4 2 7 1 3
*/
