//Hashing
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int hash(int data, int size)
{
    return data % size;
}

int insert(int *array, int data, int size) //Returns 1 if data is inserted.Returns 0 for overflow
{
    int key, intial_key;
    intial_key = key = hash(data, size);

    do
    {
        if (array[key] == INT_MIN)
        {
            array[key] = data;
            return 1;
        }

        key = (key + 1) % size;

    } while (key != intial_key);

    return 0;

    /*
        insert(array, data, size)
        //Returns 1 if data is inserted.Returns 0 for overflow

        key = data % size
        intial_key = key
        Repeat 
            if (array[key] = NULL)
                array[key] = data;
                return 1 and EXIT
            end if
            key = (key + 1) % size;
        Untill key != intial_key
        return 0
    */
}

int delete (int *array, int data, int size) //Returns 1 if data is deleted.If data is not present returns 0
{
    int key, intial_key;

    intial_key = key = hash(data, size);
    do
    {
        if (array[key] == data)
        {
            array[key] = INT_MIN;
            return 1;
        }

        key = (key + 1) % size;

    } while (key != intial_key);

    return 0;
}

void main()
{
    int data, size, ch;

    printf("\nEnter the size of the array:");
    scanf("%d", &size);

    int *arr = (int *)malloc(sizeof(int) * size); //Allocating Memory

    for (int i = 0; i < size; i++)
        arr[i] = INT_MIN; //Initializing each location in arr to INT_MIN

    do
    {
        system("cls");
        printf("\n\n1. Insert key\n2. Remove key\n3. Display\n\nEnter:");
        scanf("%d", &ch);

        if (ch == 1) //INSERT
        {
            printf("Enter data:");
            scanf("%d", &data);
            int flag = insert(arr, data, size);
            if (!flag)
                printf("\nArray is full");
        }

        else if (ch == 2) //REMOVE
        {
            printf("Enter data to remove:");
            scanf("%d", &data);

            if (delete (arr, data, size))
                printf("\nData removed");
            else
                printf("\nData not found");
        }

        else if (ch == 3) //DISPLAY
        {

            printf("\nValue: |");
            for (int i = 0; i < size; i++)
                if (arr[i] == INT_MIN)
                    printf("  -  |");
                else
                    printf("%5d|", arr[i]);

            printf("\n--------");
            for (int i = 0; i < size; i++)
                printf("------");

            printf("\nIndex: |");
            for (int i = 0; i < size; i++)
                printf("%5d|", i);

            printf("\n");
        }

        printf("\nPress any key to continue");
        scanf("%*c%*c");

    } while (ch != 4);
}