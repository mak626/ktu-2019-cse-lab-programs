void fun(int queue[], int front, int rear, int size, int ele)
{
    if (front == -1)
        printf("Queue empty");
    else
    {
        int flag = 0;

        if (queue[rear] == ele)
        {
            printf("Element delted %d", queue[rear]);
            flag = 1;
            rear--;
        }
        else
        {
            for (int i = front; i != rear; i = (i + 1) % size)
            {
                if (queue[i] == ele)
                {
                    printf("Element delted %d", queue[i]);
                    flag = 1;

                    for (int j = i; j != rear; j = (j + 1) % size)
                        queue[j] = queue[(j + 1) % size];

                    rear--;
                    break;
                }
            }
        }

        if (flag == 0)
            printf("Element not found");
    }
}