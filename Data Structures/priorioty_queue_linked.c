//Stack and Queue using linked list
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int priority;
    struct node *link;
} * headerStack, *headerQueue;

typedef struct node Node;

Node *GetNode();                //Allocates memory for Node and returns its address
void traversal(Node *);         //Prints each node in Linked List one by one
void deallocateNode(Node *ptr); //Prints the data of given Node and deallocates memory for given Node
void insertion(Node *);
void deletion(Node *);

void main()
{
    Node *header = GetNode(); //common header

    int ch, choice;

    do
    {
        system("cls");
        printf("\n1.Insert");
        printf("\n2.Delete");
        printf("\n3.Display");
        printf("\n4.Exit");

        printf("\n\nEnter choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insertion(header);
            break;
        case 2:
            deletion(header);
            break;
        case 3:
            traversal(header);
            break;
        }

    } while (choice != 4);
}

Node *GetNode()
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = 0;
    new->priority = INT_MIN;
    new->link = NULL;
    return new;
}

void traversal(Node *header)
{
    Node *curr = header->link;
    system("cls");
    if (curr == NULL)
    {
        printf("\nQueue Empty");
    }
    else
    {
        printf("\nQueue:-\n");
        printf("\nD - P", curr->data, curr->priority);
        while (curr != NULL)
        {
            printf("\n%d - %d", curr->data, curr->priority);
            curr = curr->link;
        }
    }

    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}

void deallocateNode(Node *ptr)
{
    printf("\nDeleted Node with data: %d", ptr->data);
    free(ptr);
    ptr = NULL;
}

void insertion(Node *header)
{
    system("cls");
    Node *new = GetNode();

    if (new == NULL)
        printf("Memory not available");
    else
    {
        int value, p, key;

        printf("\nEnter Value for new node: ");
        scanf("%d", &value);
        printf("\nEnter prioriy for new node: ");
        scanf("%d", &p);
        new->data = value;
        new->priority = p;

        Node *curr, *prev;

        prev = header;
        curr = header->link;

        while (curr != NULL && curr->priority <= p)
        {
            prev = curr;
            curr = curr->link;
        }

        new->link = prev->link;
        prev->link = new;

        printf("\nInserted new node");
    }
    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}

void deletion(Node *header)
{
    system("cls");

    if (header->link == NULL)
    {
        printf("\nQueue Empty");
        printf("\n\nPress any key to continue");
        scanf("%*c%*c");
        return;
    }

    //DELETION AT FRONT
    Node *curr;

    curr = header->link;
    header->link = curr->link;
    deallocateNode(curr);

    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}