//M Aswin Kishore 41
//Linear and binary search
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int n, x[30], i, j, ele, ch, temp, flag;

    void data()
    {
        system("cls");
        printf("Enter size of array:");
        scanf("%d", &n);
        printf("\nEnter the unsorted array:");
        for (i = 0; i < n; i++)
            scanf("%d", &x[i]);
    }

    void print()
    {
        printf("\nArray is:");
        for (i = 0; i < n; i++)
            printf("%d ", x[i]);
    }

    data(); //Get the array data

    //MENU
    do
    {
        system("cls");
        printf("1.Linear Search\n2.Binary Search\n3.Re-enter array\n4.Exit\nEnter choice:");
        scanf("%d", &ch);

        if (ch == 1) //LINEAR SEARCH
        {
            print();
            printf("\nEnter the element to be searched:");
            scanf("%d", &ele);
            flag = 0;
            for (i = 0; i < n; i++)
                if (x[i] == ele)
                {
                    printf("Element '%d' found at position %d", ele, i + 1);
                    flag = 1;
                    break;
                }
            if (!flag)
                printf("Element '%d' not found", ele);
            printf("\n\nPress enter to continue");
            scanf("%*c%*c");
        }
        else if (ch == 2) //BINARY SEARCH
        {
            //Sorting the array using bubble sort
            for (i = 0; i < n - 1; i++)
                for (j = 0; j < n - i - 1; j++)
                    if (x[j] > x[j + 1])
                    {
                        temp = x[j];
                        x[j] = x[j + 1];
                        x[j + 1] = temp;
                    }
            print();
            printf("\nEnter the element to be searched:");
            scanf("%d", &ele);

            int mid, l = 0, u = n - 1;
            flag = 0;
            while (l <= u)
            {
                mid = l + (u - l) / 2;
                if (x[mid] == ele)
                {
                    flag = 1;
                    printf("Element '%d' found at position %d", ele, mid + 1);
                    break;
                }
                else if (x[mid] > ele)
                    u = mid - 1;
                else
                    l = mid + 1;
            }
            if (!flag)
                printf("Element '%d' not found", ele);
            printf("\n\nPress enter to continue");
            scanf("%*c%*c");
        }
        else if (ch == 3)
            data();
    } while (ch != 4);
}
