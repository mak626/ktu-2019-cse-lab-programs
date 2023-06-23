//M Aswin Kishore
//Stack and Queue

#include <stdio.h>
#include <stdlib.h>

void Stack()
{
    int size;
    printf("\nEnter Size Of Stack:");
    scanf("%d", &size);

    int stack[size], top = -1, ch, ele;

    do
    {
        system("cls");
        printf("1.Push\n2.Pop\n3.Display\n4.Exit\nEnter the choice:");
        scanf("%d", &ch);
        system("cls");
        if (ch == 1)
        {
            if (top + 1 == size)
                printf("Stack Overflow!");
            else
            {
                printf("Enter element to be pushed:");
                scanf("%d", &ele);
                stack[++top] = ele;
            }
        }
        else if (ch == 2)
        {
            if (top == -1)
                printf("Stack Underflow!");
            else
                printf("Element popped: %d", stack[top--]);
        }
        else if (ch == 3)
        {
            if (top == -1)
                printf("Stack Underflow!");
            else
            {
                printf("Stack:-\n");
                printf("%d <--Top\n", stack[top]);
                for (int i = top - 1; i >= 0; i--)
                    printf("%d\n", stack[i]);
            }
        }
        else if (ch == 4)
        {
            break;
        }

        printf("\nPress enter to continue..");
        scanf("%*c%*c");

    } while (ch != 4);
}

void Queue()
{
    int size;
    printf("\nEnter Size Of Queue:");
    scanf("%d", &size);

    int queue[size], ch, front = -1, rear = -1, ele;

    do
    {
        system("cls");
        printf("1.enQueue\n2.deQueue\n3.Display\n4.Exit\nEnter the choice:");
        scanf("%d", &ch);
        system("cls");

        if (ch == 1)
        {
            if (rear + 1 == size)
                printf("Queue full !");
            else
            {
                printf("Enter element to be inserted:");
                scanf("%d", &ele);
                if (front == -1)
                    front = 0;
                queue[++rear] = ele;
            }
        }
        else if (ch == 2)
        {
            if (front == -1)
                printf("Queue empty !");
            else
            {
                printf("Element deleted: %d", queue[front]);
                if (front == rear)
                    front = rear = -1;
                else
                    front++;
            }
        }
        else if (ch == 3)
        {
            if (front == -1)
                printf("Queue empty !");
            else
            {
                printf("Queue:-\n");
                printf("Front-->");
                for (int i = front; i <= rear; i++)
                    printf(" %d ", queue[i]);
                printf("<--Rear");
            }
        }
        else if (ch == 4)
        {
            break;
        }

        printf("\nPress enter to continue..");
        scanf("%*c%*c");

    } while (ch != 4);
}

void main()
{
    int ch;

    do
    {
        system("cls");
        printf("1.Stack\n2.Queue\n3.Exit\nEnter the choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            Stack();
            break;
        case 2:
            Queue();
            break;
        }
    } while (ch != 3);
}