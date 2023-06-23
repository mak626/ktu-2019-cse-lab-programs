#include <stdio.h>
#include <stdlib.h>

#define size 10

struct node
{
    int data;
    struct node *link;
};

typedef struct node node;

void insert(int, node **);
node *getnode(int);
void delete (int);
void display();

node *getnode(int value)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = value;
    new->link = NULL;
    return new;
}

struct node *arr[size];

void main()
{
    int c = 0, n, i, l;
    for (i = 0; i < size; i++)
    {
        arr[i] = NULL;
    }
    do
    {
        printf("\n\n1.Insertion\n2.Deletion\n3.Exit\nEnter your choice:");
        scanf("%d", &c);
        if (c == 1)
        {
            printf("Enter the element to be inserted:");
            scanf("%d", &n);
            insert(n, arr);
        }

        if (c == 2)
        {
            printf("\nEnter the element to be deleted");
            scanf("%d", &l);
            delete (l);
        }
    } while (c != 3);
}

void insert(int value, node **arr)
{
    int key;
    node *new = getnode(value);
    key = value % size;
    node *temp;
    if (arr[key] == NULL)
        arr[key] = new;
    else
    {
        temp = arr[key];
        while (temp->link != NULL)
            temp = temp->link;

        temp->link = new;
    }
    display();
}

void delete (int value)
{
    int key = value % size;

    if (arr[key] == NULL)
        printf("Element not found");
    else
    {
        node *temp, *prev;

        temp = arr[key];

        while (temp != NULL && temp->data != value)
        {
            prev = temp;
            temp = temp->link;
        }

        if (temp->data == value)
        {
            if (temp == arr[key])
                arr[key] = temp->link;
            else
                prev->link = temp->link;

            free(temp);
        }
        else
            printf("\nThe key not found");
    }
    display();
}

void display()
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == NULL)
        {
            printf("\n  %d  |  -\n", i); //extra space
        }
        else
        {
            node *temp = arr[i];
            while (temp != NULL)
            {
                printf("\n  %d  |  %d\n", i, temp->data);
                temp = temp->link;
            }
        }
    }
}