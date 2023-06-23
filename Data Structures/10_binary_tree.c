//Binary Tree
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *Lchild;
    struct node *Rchild;
};

typedef struct node Node;

//Returns address of a new node with data = value
Node *getNode(int value)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = value;
    new->Lchild = NULL;
    new->Rchild = NULL;
    return new;
}

//Print functions
void printPostorder(Node *ptr)
{
    if (ptr == NULL)
        return;

    printPostorder(ptr->Lchild);
    printPostorder(ptr->Rchild);
    printf(" %d ", ptr->data);
}

void printInorder(Node *ptr)
{
    if (ptr == NULL)
        return;

    printInorder(ptr->Lchild);
    printf(" %d ", ptr->data);
    printInorder(ptr->Rchild);
}

void printPreorder(Node *ptr)
{
    if (ptr == NULL)
        return;

    printf(" %d ", ptr->data);
    printPreorder(ptr->Lchild);
    printPreorder(ptr->Rchild);
}

//Returns the address of the node with data = search_value
Node *search(Node *ptr, int search_value)
{
    if (ptr == NULL || ptr->data == search_value)
        return ptr;

    Node *L, *R;

    L = search(ptr->Lchild, search_value);
    R = search(ptr->Rchild, search_value);

    if (L != NULL)
        return L;
    else
        return R;
}

void main()
{
    int choice = 0, value, search_value;
    Node *root, *parent;

    system("cls");
    printf("\nEnter root node:");
    scanf("%d", &value);
    root = getNode(value);

    do
    {
        system("cls");
        printf("\nBinary Tree in PreOrder  : ");
        printPreorder(root);
        printf("\nBinary Tree in InOrder   : ");
        printInorder(root);
        printf("\nBinary Tree in PostOrder : ");
        printPostorder(root);

        printf("\n\n1.Create a new node\n2.Exit\nEnter choice : ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\nSelect Parent Node: ");
            scanf("%d", &search_value);

            parent = search(root, search_value);

            if (parent == NULL)
                printf("\nValue not found!");
            else
            {
                int sub_choice;
                printf("1.Enter Left Child\n2.Enter Right Child\n3.Return\nEnter choice : ");
                scanf("%d", &sub_choice);

                if (sub_choice == 1)
                {
                    if (parent->Lchild == NULL)
                    {
                        printf("Enter Value  : ");
                        scanf("%d", &value);
                        parent->Lchild = getNode(value);
                    }
                    else
                        printf("\nLeft Child is already allocated");
                }
                else if (sub_choice == 2)
                {
                    if (parent->Rchild == NULL)
                    {
                        printf("Enter Value  : ");
                        scanf("%d", &value);
                        parent->Rchild = getNode(value);
                    }
                    else
                        printf("\nRight Child is already allocated");
                }
            }

            printf("\nPress any key to continue");
            scanf("%*c%*c");
        }

    } while (choice != 2);
}
