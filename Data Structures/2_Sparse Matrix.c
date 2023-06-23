//M Aswin Kishore 41
//Sparse Matrix
#include <stdio.h>

void main()
{
    int n, sp[20][3], i, j, k, r_c, temp, flag;
    printf("Enter the ORDER of Martix:");
    scanf("%d", &n);

    //INRIALIZE HEADER ROW
    sp[0][0] = sp[0][1] = n;
    r_c = 0;

    printf("\nEnter the data of matrix:%d\n", 1);
    for (int i = 0; i < n; i++)
    {
        printf("Enter row %d :", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &temp);
            //APPEND AS SPARSE
            if (temp != 0)
            {
                r_c++;
                sp[r_c][0] = i;
                sp[r_c][1] = j;
                sp[r_c][2] = temp;
            }
        }
    }

    printf("\nEnter the data of matrix:%d\n", 2);
    for (int i = 0; i < n; i++)
    {
        printf("Enter row %d :", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &temp);
            if (temp != 0)
            {
                flag = 0;
                for (k = 1; k <= r_c; k++)
                {
                    //CHECK IF ELEMENT ALREADY EXISTS IN SPARSE
                    if (sp[k][0] == i && sp[k][1] == j)
                    {
                        sp[k][2] += temp;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    r_c++;
                    sp[r_c][0] = i;
                    sp[r_c][1] = j;
                    sp[r_c][2] = temp;
                }
            }
        }
    }

    //Assigning row count
    sp[0][2] = r_c;

    //SORTING AND PRINTING SPARSE
    printf("\n\nThe Resultant Sparse Matrix:");
    printf("\n%d %d %d", sp[0][0], sp[0][1], sp[0][2]);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            for (k = 1; k <= r_c; k++)
            {
                if (sp[k][0] == i && sp[k][1] == j)
                {
                    printf("\n%d %d %d", sp[k][0], sp[k][1], sp[k][2]);
                    break;
                }
            }
        }
}