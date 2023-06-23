//Singly Linked List
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *link;
} * header;

typedef struct node Node;

Node *GetNode();                //Allocates memory for Node and returns its address
void traversal();               //Prints each node in Linked List one by one
void reversal();                //Reverses the linked list
void deallocateNode(Node *ptr); //Prints the data of given Node and deallocates memory for given Node

void insertion(int choice);
void deletion(int choice);
/*
    choice == 1 , Insert At Front
    choice == 2 , Insert In Between
    choice == 3 , Insert At End
    choice == 4 , Delete From Front
    choice == 5 , Delete A Node Of Particular Key
    choice == 6 , Insert At End
*/

void main()
{
    header = GetNode();
    int choice;

    do
    {
        system("cls");
        printf("Menu\n");
        printf("\n1.Insert At Front");
        printf("\n2.Insert In Between");
        printf("\n3.Insert At End");
        printf("\n4.Delete From Front");
        printf("\n5.Delete A Node Of Particular Key");
        printf("\n6.Delete From End");
        printf("\n7.Reversal");
        printf("\n8.Traversal");
        printf("\n9.Exit");
        printf("\n\nEnter choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        case 2:
        case 3:
            insertion(choice);
            break;
        case 4:
        case 5:
        case 6:
            deletion(choice);
            break;
        case 7:
            reversal();
            break;
        case 8:
            traversal();
            break;
        }

    } while (choice != 9);
}

Node *GetNode()
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = 0;
    new->link = NULL;
    return new;
}

void traversal()
{
    Node *curr = header->link;
    system("cls");
    if (curr == NULL)
        printf("\nLinked List is empty");
    else
    {
        printf("\nLinked List:-\n");
        printf("Header");
        while (curr != NULL)
        {
            printf(" -> %d", curr->data);
            curr = curr->link;
        }
    }

    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}

void reversal()
{
    system("cls");

    Node *prev, *curr, *next;

    prev = NULL;
    curr = header->link;

    if (curr == NULL)
        printf("Linked List is empty");
    else
    {
        while (curr != NULL)
        {
            next = curr->link;
            curr->link = prev;
            prev = curr;
            curr = next;
        }
        header->link = prev;
        printf("Reversal is completed");
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

void insertion(int choice)
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

        if (choice == 1) // INSERTION AT FRONT
        {
            new->link = header->link;
            header->link = new;
            printf("\nInserted new node at front");
        }

        if (choice == 2) //INSERTION IN BETWEEN
        {
            printf("Enter Key for searching and insertion: ");
            scanf("%d", &key);

            while (curr->data != key && curr->link != NULL)
                curr = curr->link;

            if (curr->data != key)
            {
                printf("\nKey not found in between.Inserted new node at end");
                curr->link = new;
            }
            else
            {
                new->link = curr->link;
                curr->link = new;
                printf("\nInserted new node in between at key = %d", key);
            }
        }

        if (choice == 3) //INSERTION AT END
        {
            while (curr->link != NULL)
                curr = curr->link;

            curr->link = new;
            printf("\nInserted new node at end");
        }
    }
    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}

void deletion(int choice)
{
    system("cls");

    if (header->link == NULL)
    {
        printf("Linked List Empty");
        printf("\n\nPress any key to continue");
        scanf("%*c%*c");
        return;
    }

    Node *prev, *curr;

    if (choice == 4) // DELETION FROM FRONT
    {
        curr = header->link;
        header->link = curr->link;
        deallocateNode(curr);
    }

    if (choice == 5) //DELETION FROM ANY POSITION
    {
        int key;
        printf("Enter Key for searching and deletion: ");
        scanf("%d", &key);

        curr = header;

        while (curr->link != NULL && curr->data != key)
        {
            prev = curr;
            curr = curr->link;
        }

        if (curr->data == key)
        {
            prev->link = curr->link;
            deallocateNode(curr);
        }
        else
            printf("\nKey not found.No deletion took place");
    }

    if (choice == 6) //DELETION FROM END
    {
        curr = header;

        while (curr->link != NULL)
        {
            prev = curr;
            curr = curr->link;
        }

        prev->link = NULL;
        deallocateNode(curr);
    }
    printf("\n\nPress any key to continue");
    scanf("%*c%*c");
}