//Representation of polynomials using linked list, addition and multiplication of polynomials
//Edited addition change

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int cof;
    int pow;
    struct node *link;
} * h1, *h2, *hs, *hp, *ptr; //Headers of polynomial 1 and 2 , sum and product linked list

typedef struct node Node;

Node *GetNode(int cof, int pow);
void display(Node *header);
void poly_addition(Node *h1, Node *h2, Node *hs);
void poly_multiplication(Node *h1, Node *h2, Node *hp);

void main()
{
    int p1, p2, coefficient, power;
    h1 = GetNode(0, 0);
    h2 = GetNode(0, 0);
    hp = GetNode(0, 0);
    hs = GetNode(0, 0);

    printf("\nEnter number of terms of polynomial 1:");
    scanf("%d", &p1);
    printf("\nEnter the terms of polynomial 1 in DESCENDING ORDER OF POWER as : coefficient power\n");
    ptr = h1;
    for (int i = 0; i < p1; i++)
    {
        printf("Enter term %d : ", i + 1);
        scanf("%d %d", &coefficient, &power);
        ptr->link = GetNode(coefficient, power);
        ptr = ptr->link;
    }

    printf("\nEnter number of terms of polynomial 2:");
    scanf("%d", &p2);
    printf("\nEnter the terms of polynomial 2 in DESCENDING ORDER OF POWER as : coefficient power\n");
    ptr = h2;
    for (int i = 0; i < p2; i++)
    {
        printf("Enter term %d : ", i + 1);
        scanf("%d %d", &coefficient, &power);
        ptr->link = GetNode(coefficient, power);
        ptr = ptr->link;
    }

    poly_addition(h1, h2, hs);
    poly_multiplication(h1, h2, hp);

    system("cls");
    printf("First Polynomial:-\n");
    display(h1);
    printf("\n\nSecond Polynomial:-\n");
    display(h2);
    printf("\n\nSum:-\n");
    display(hs);
    printf("\n\nProduct:-\n");
    display(hp);
}

Node *GetNode(int cof, int pow)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->link = NULL;
    new->cof = cof;
    new->pow = pow;
    return new;
}

void poly_addition(Node *h1, Node *h2, Node *hs)
{
    Node *poly1, *poly2;
    poly1 = h1->link;
    poly2 = h2->link;

    Node *polys = hs; //Note

    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->pow > poly2->pow)
        {
            // addNode(hs, poly1->cof, poly1->pow);
            polys->link = GetNode(poly1->cof, poly1->pow);
            poly1 = poly1->link;
        }

        else if (poly1->pow < poly2->pow)
        {
            //addNode(hs, poly2->cof, poly2->pow);
            polys->link = GetNode(poly2->cof, poly2->pow);
            poly2 = poly2->link;
        }

        else
        {
            //addNode(hs, poly1->cof + poly2->cof, poly1->pow);
            polys->link = GetNode(poly1->cof + poly2->cof, poly1->pow);
            poly1 = poly1->link;
            poly2 = poly2->link;
        }

        polys = polys->link; //note this
    }

    while (poly1 != NULL) //First polynomial out of bound
    {
        //addNode(hs, poly1->cof, poly1->pow);
        polys->link = GetNode(poly1->cof, poly1->pow);
        poly1 = poly1->link;
        polys = polys->link; //note this
    }

    while (poly2 != NULL) //Second polynomial out of bound
    {
        //addNode(hs, poly2->cof, poly2->pow);
        polys->link = GetNode(poly2->cof, poly2->pow);
        poly2 = poly2->link;
        polys = polys->link; //note this`
    }
}

void poly_multiplication(Node *h1, Node *h2, Node *hp)
{
    Node *poly1, *poly2, *polyp;

    poly1 = h1->link;

    polyp = hp; //Note

    while (poly1 != NULL)
    {
        poly2 = h2->link;

        while (poly2 != NULL)
        {
            int product = poly1->cof * poly2->cof;
            int power = poly1->pow + poly2->pow;

            if (product != 0)
            {
                //addNode(hp, product, power);
                polyp->link = GetNode(product, power);
                polyp = polyp->link; //note this
            }

            poly2 = poly2->link;
        }

        poly1 = poly1->link;
    }

    //ADDING SAME POWER TERMS
    Node *poly, *prev, *curr;

    poly = hp->link;

    while (poly != NULL)
    {
        prev = poly;
        curr = poly->link;

        while (curr != NULL)
        {
            if (poly->pow == curr->pow)
            {
                poly->cof += curr->cof;
                prev->link = curr->link; // Deleting curr Node
                free(curr);              // Deallocating memory
                curr = prev->link;       //prev is not changed here since the current node has been deleted
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

void display(Node *header)
{
    Node *curr = header->link;
    if (curr == NULL)
        printf("\nLinked List is empty");
    else
    {
        while (curr != NULL)
        {
            printf("%dx^%d", curr->cof, curr->pow);
            if (curr->link != NULL)
                printf(" + ");
            curr = curr->link;
        }
    }
}