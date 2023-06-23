#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *llink;
    struct node *rlink;
} * head;

typedef struct node node;

node *getnode();
void insert();
void insertfront(int);
void insertbetween(int);
void insertend(int);
void delete ();
void deletefront();
void deletebetween();
void deleteend();
void traversal();

node *getnode()
{
    node *new = (node *)malloc(sizeof(node));
    new->data = 0;
    new->rlink = NULL;
    new->llink = NULL;
}

void main()
{
    int n;
    head = getnode();
    do
    {
        printf("\n\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Traversal");
        printf("\n4.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            insert();
            break;
        case 2:
            delete ();
            break;
        case 3:
            traversal();
            break;
        }
    } while (n != 4);
}

void insert()
{
    int m, choice;
    do
    {
        printf("\n\n1.Insertion at front");
        printf("\n2.Insertion in between");
        printf("\n3.Insertion at end");
        printf("\n4.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &choice);

        if (choice != 4)
        {
            printf("\nEnter the element to be inserted:");
            scanf("%d", &m);
        }

        switch (choice)
        {
        case 1:
            insertfront(m);
            break;
        case 2:
            insertbetween(m);
            break;
        case 3:
            insertend(m);
            break;
        }

    } while (choice != 4);
}

void insertfront(int l)
{
    node *new = getnode();
    if (new == NULL)
        printf("Memory not available");
    else
    {
        new->data = l;
        node *next;

        next = head->rlink;

        head->rlink = new;
        new->llink = head;

        new->rlink = next;
        if (next != NULL)
            next->llink = new;

        printf("\nA new node is inserted at the front");
    }
}

void insertbetween(int l)
{
    node *new = getnode();
    if (new == NULL)
        printf("Memory not available");
    else
    {
        new->data = l;
        node *ptr = head;

        int key;
        printf("Enter the key element:");
        scanf("%d", &key);

        while (ptr->data != key && ptr->rlink != NULL)
            ptr = ptr->rlink;

        if (ptr->data != key)
        {
            ptr->rlink = new;
            new->llink = ptr;
            printf("\nKey not found.Inserted at the end");
        }
        else if (ptr->data == key)
        {
            node *next;
            next = ptr->rlink;

            new->llink = ptr;
            ptr->rlink = new;

            new->rlink = next;
            if (next != NULL)
                next->llink = new;

            printf("\nA new node is inserted in between");
        }
    }
}

void insertend(int l)
{
    node *new = getnode();
    if (new == NULL)
        printf("Memory not available");
    else
    {
        node *ptr = head;
        new->data = l;

        while (ptr->rlink != NULL)
            ptr = ptr->rlink;

        ptr->rlink = new;
        new->llink = ptr;
        printf("\nA new node is inserted at end");
    }
}

void delete ()
{
    int p;
    do
    {
        printf("\n\n1.Delete at front");
        printf("\n2.Deletion in between");
        printf("\n3.Deletion at end");
        printf("\n4.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &p);
        switch (p)
        {
        case 1:
            deletefront();
            break;
        case 2:
            deletebetween();
            break;
        case 3:
            deleteend();
            break;
        }
    } while (p != 4);
}

void deletefront()
{

    if (head->rlink == NULL)
        printf("\nThe linked list is empty");
    else
    {
        node *ptr = head->rlink;
        node *next = ptr->rlink;

        head->rlink = next;
        if (next != NULL) //Linked List empty case we have to consider
            next->llink = head;

        int data = ptr->data;
        free(ptr);
        ptr = NULL;
        printf("The element %d is deleted from front", data);
    }
}

void deletebetween()
{
    if (head->rlink == NULL)
        printf("\nThe linked list is empty");
    else
    {
        node *ptr = head;

        int key, data;
        printf("Enter the key:");
        scanf("%d", &key);

        while (ptr->data != key && ptr->rlink != NULL)
            ptr = ptr->rlink;

        if (ptr->data == key)
        {
            node *next, *prev;

            prev = ptr->llink;
            next = ptr->rlink;

            prev->rlink = next;
            if (next != NULL)
                next->llink = prev;

            data = ptr->data;
            free(ptr);
            ptr = NULL;
            printf("The element %d is deleted", data);
        }
        else
        {
            printf("Key not found");
        }
    }
}

void deleteend()
{

    if (head->rlink == NULL)
        printf("\nThe linked list is empty");
    else
    {
        node *ptr = head;
        int data;
        while (ptr->rlink != NULL)
            ptr = ptr->rlink;

        node *prev = ptr->llink;
        prev->rlink = NULL;

        data = ptr->data;
        free(ptr);
        ptr = NULL;
        printf("The element %d is deleted", data);
    }
}

void traversal()
{
    node *ptr = head->rlink;
    if (ptr == NULL)
        printf("\nThe linked list is empty");
    else
    {
        printf("\nHeader");
        while (ptr != NULL)
        {
            printf("<--%d-->", ptr->data);
            ptr = ptr->rlink;
        }
        printf("NULL");
    }
}

void doubly_backward_traversal()
{
    if (head->rlink == NULL)
        printf("\nThe linked list is empty");
    else
    {
        node *lastNode = head->rlink;
        while (lastNode->rlink != NULL)
            lastNode = lastNode->rlink;

        node *curr = lastNode;
        while (curr != head)
        {
            printf("%d", curr->data);
            curr = curr->llink
        }
    }
}