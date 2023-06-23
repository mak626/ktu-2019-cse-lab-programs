//M Aswin Kishore
//Deque
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int size;
    printf("\nEnter Size Of Deque:");
    scanf("%d", &size);

    int queue[size], ch, front = -1, rear = -1, ele;

    do
    {
        system("cls");
        printf("Deque");
        printf("\n1.Insert Front\n2.Delete Front\n3.Insert Rear\n4.Delete Rear\n5.Display\n6.Exit\nEnter the choice:");
        scanf("%d", &ch);
        system("cls");

        if (ch == 1) //Insert front
        {
            if ((rear + 1) % size == front)
                printf("Dequeue full !");
            else
            {
                printf("Enter element to be inserted:");
                scanf("%d", &ele);

                if (front == -1)
                    front = rear = 0;
                else if (front == 0)
                    front = size - 1;
                else
                    front--;

                queue[front] = ele;
            }
        }
        else if (ch == 2) //Delete front
        {
            if (front == -1)
                printf("Dequeue empty !");
            else
            {
                printf("Element deleted: %d", queue[front]);
                if (front == rear)
                    front = rear = -1;
                else
                    front = (front + 1) % size;
            }
        }
        else if (ch == 3) //Insert rear
        {
            if ((rear + 1) % size == front)
                printf("DeQueue full !");
            else
            {
                printf("Enter element to be inserted:");
                scanf("%d", &ele);

                if (rear == -1)
                    front = rear = 0;
                else
                    rear = (rear + 1) % size;

                queue[rear] = ele;
            }
        }
        else if (ch == 4) //Delete rear
        {
            if (rear == -1)
                printf("Dequeue empty !");
            else
            {
                printf("Element deleted: %d", queue[rear]);
                if (front == rear)
                    front = rear = -1;
                else if (rear == 0)
                    rear = size - 1;
                else
                    rear--;
            }
        }
        else if (ch == 5) //Display
        {
            if (front == -1)
                printf("Dequeue empty !");
            else
            {
                printf("Dequeue:-\n");

                if (front != rear)
                {
                    printf("Front-->");
                    for (int i = front; i != rear; i = (i + 1) % size)
                    {
                        printf(" %d ", queue[i]);
                    }
                    printf(" %d ", queue[rear]); // last element
                    printf("<--Rear");
                }
                else //Only 1 element in Deque
                {
                    printf("Front--> %d <--Rear", queue[front]);
                }
            }
        }
        else if (ch == 6)
        {
            break;
        }

        printf("\nPress enter to continue..");
        scanf("%*c%*c");

    } while (ch != 6);
}
