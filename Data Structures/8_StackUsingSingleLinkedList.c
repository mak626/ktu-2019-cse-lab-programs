// Singly Linked List
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
} * headerStack, *headerQueue;

typedef struct node Node;

Node *GetNode();                //Allocates memory for Node and returns its address
void traversal(int, Node *);    //Prints each node in Linked List one by one
void deallocateNode(Node *ptr); //Prints the data of given Node and deallocates memory for given Node
void insertion(int, Node *);
void deletion(int, Node *);

void main()
{
    headerStack = GetNode();
    headerQueue = GetNode();
    Node *header = NULL; //common header

    int ch, choice;

    do
    {
        system("cls");
        printf("Menu\n");
        printf("\n1.Stack");
        printf("\n2.Queue");
        printf("\n3.Exit");
        printf("\n\nEnter choice:");
        scanf("%d", &ch);

        do
        {
            system("cls");
            if (ch == 1)
            {
                header = headerStack;
                printf("\n1.Push");
                printf("\n2.Pop");
                printf("\n3.Display");
                printf("\n4.Exit");
            }
            else if (ch == 2)
            {
                header = headerQueue;
                printf("\n1.Insert");
                printf("\n2.Delete");
                printf("\n3.Display");
                printf("\n4.Exit");
            }
            printf("\n\nEnter choice:");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                insertion(ch, header);
                break;
            case 2:
                deletion(ch, header);
                break;
            case 3:
                traversal(ch, header);
                break;
            }

        } while (choice != 4);

    } while (ch != 3);
}

Node *GetNode()
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = 0;
    new->link = NULL;
    return new;
}

void traversal(int choice, Node *header)
{
    Node *curr = header->link;
    system("cls");
    if (curr == NULL)
    {
        if (choice == 1)
            printf("\nStack Underflow");
        else
            printf("\nQueue Empty");
    }
    else
    {
        if (choice == 1)
        {
            printf("\nStack:-\n");
            while (curr != NULL)
            {
                printf("%d\n", curr->data);
                curr = curr->link;
            }
        }
        else
        {
            printf("\nQueue:-\n");
            while (curr != NULL)
            {
                printf("%d ", curr->data);
                curr = curr->link;
            }
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

void insertion(int choice, Node *header)
{
    system("cls");
    Node *new = GetNode();

    if (new == NULL)
        printf("Memory not available");
    else
    {
        int value, key;

        printf("\nEnter Value for new node: ");
        scanf("%d", &value);
        new->data = value;

        Node *curr = header;

        if (choice == 1) // INSERTION AT FRONT (STACK)
        {
            new->link = header->link;
            header->link = new;
            printf("\nInserted new node");
        }

        if (choice == 2) //INSERTION AT END (QUEUE)
        {
            while (curr->link != NULL)
                curr = curr->link;

            curr->link = new;
            printf("\nInserted new node");
        }
    }
    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}

void deletion(int choice, Node *header)
{
    system("cls");

    if (header->link == NULL)
    {
        if (choice == 1)
            printf("\nStack Underflow");
        else
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