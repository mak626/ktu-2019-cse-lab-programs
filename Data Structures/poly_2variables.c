//Representation of polynomials using linked list, addition of  polynomials with 2 variables

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int cof;
    int pow_x;
    int pow_y;
    struct node *link;
} * h1, *h2, *hs; //Headers of polynomial 1 and 2 , sum linked list

typedef struct node Node;

Node *GetNode();
void addNode(Node *header, int coefficient, int power_x, int power_y);
void display(Node *header);
void poly_addition(Node *h1, Node *h2, Node *hs);

void main()
{
    int p1, p2, coefficient, power_x, power_y;
    h1 = GetNode();
    h2 = GetNode();
    hs = GetNode();

    printf("\nEnter number of terms of polynomial 1:");
    scanf("%d", &p1);
    printf("\nEnter the terms of polynomial 1 in DESCENDING ORDER OF POWER as : coefficient power_x power_y\n");
    for (int i = 0; i < p1; i++)
    {
        printf("Enter term %d : ", i + 1);
        scanf("%d %d %d", &coefficient, &power_x, &power_y);
        addNode(h1, coefficient, power_x, power_y);
    }

    printf("\nEnter number of terms of polynomial 2:");
    scanf("%d", &p2);
    printf("\nEnter the terms of polynomial 2 in DESCENDING ORDER OF POWER as : coefficient power_x power_y\n");
    for (int i = 0; i < p2; i++)
    {
        printf("Enter term %d : ", i + 1);
        scanf("%d %d %d", &coefficient, &power_x, &power_y);
        addNode(h2, coefficient, power_x, power_y);
    }

    poly_addition(h1, h2, hs);

    system("cls");
    printf("First Polynomial:-\n");
    display(h1);
    printf("\n\nSecond Polynomial:-\n");
    display(h2);
    printf("\n\nSum:-\n");
    display(hs);
}

Node *GetNode()
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->link = NULL;
    return new;
}

void poly_addition(Node *h1, Node *h2, Node *hs)
{
    Node *poly1, *poly2;
    poly1 = h1->link;
    poly2 = h2->link;

    //Adding both poly1 and poly2 to poly_sum
    while (poly1 != NULL)
    {
        addNode(hs, poly1->cof, poly1->pow_x, poly1->pow_y);
        poly1 = poly1->link;
    }

    while (poly2 != NULL)
    {
        addNode(hs, poly2->cof, poly2->pow_x, poly2->pow_y);
        poly2 = poly2->link;
    }

    //Adding nodes with same power (this trick is used in removing duplicates in 9.c of multiplication)

    Node *poly = hs->link, *prev, *curr;

    while (poly != NULL)
    {
        prev = poly;
        curr = poly->link;

        while (curr != NULL)
        {
            if (curr->pow_x == poly->pow_x && curr->pow_y == poly->pow_y)
            {
                poly->cof = curr->cof + poly->cof;
                prev->link = curr->link;
                free(curr);
                break; //this is different from 9.c because there can only be one duplicate i.e from poly2 so we can break
            }
            else
            {
                prev = curr;
                curr = curr->link;
            }
        }
        poly = poly->link;
    }
}

void addNode(Node *header, int coefficient, int power_x, int power_y)
{
    Node *new = GetNode();

    if (new == NULL)
        printf("Memory not available");
    else
    {
        Node *curr = header;
        new->cof = coefficient;
        new->pow_x = power_x;
        new->pow_y = power_y;

        while (curr->link != NULL)
            curr = curr->link;

        curr->link = new;
    }
}

void display(Node *header)
{
    Node *curr = header->link;
    if (curr == NULL)
        printf("\nLinked List is empty");
    else
    {
        while (curr != NULL)
        {
            printf("%dx^%dy^%d", curr->cof, curr->pow_x, curr->pow_y);
            if (curr->link != NULL)
                printf(" + ");
            curr = curr->link;
        }
    }
}