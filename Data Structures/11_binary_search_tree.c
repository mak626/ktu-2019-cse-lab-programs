//Binary Search Tree
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

//Operations
Node *insertNode(Node *root, int value)
{
    if (root == NULL) //Base case
        root = getNode(value);
    else if (value < root->data)
        root->Lchild = insertNode(root->Lchild, value);
    else
        root->Rchild = insertNode(root->Rchild, value);

    return root;
}

Node *deleteNode(Node *root, int search_value)
{

    if (root == NULL) //Base case
        return root;
    else if (search_value < root->data)
        root->Lchild = deleteNode(root->Lchild, search_value);
    else if (search_value > root->data)
        root->Rchild = deleteNode(root->Rchild, search_value);
    else
    {
        // Case 1:  No child
        if (root->Lchild == NULL && root->Rchild == NULL)
        {
            free(root);
            root = NULL;
        }
        //Case 2: One child
        else if (root->Lchild == NULL)
        {
            Node *temp = root;
            root = root->Rchild;
            free(temp);
        }
        else if (root->Rchild == NULL)
        {
            Node *temp = root;
            root = root->Lchild;
            free(temp);
        }
        //Case 3: 2 children
        else
        {
            //Finding next minimum inOrder
            Node *temp = root->Rchild;
            while (temp->Lchild != NULL)
                temp = temp->Lchild;

            root->data = temp->data;
            root->Rchild = deleteNode(root->Rchild, temp->data);
        }
    }
    return root;
}

int height(Node *ptr)
{
    if (ptr == NULL)
        return 0;
    else
    {
        int Lheight = height(ptr->Lchild);
        int Rheight = height(ptr->Rchild);

        if (Lheight > Rheight)
            return (Lheight + 1);
        else
            return (Rheight + 1);
    }
}

void main()
{
    int choice = 0, value, search_value;
    Node *root = NULL;

    do
    {
        system("cls");
        printf("\nBinary Tree in PreOrder  : ");
        printPreorder(root);
        printf("\nBinary Tree in InOrder   : ");
        printInorder(root);
        printf("\nBinary Tree in PostOrder : ");
        printPostorder(root);

        printf("\n\n1. Insertion\n2. Deletion\n3. Height\n4. Exit\nEnter choice : ");
        scanf("%d", &choice);

        if (choice == 1) //INSERTION
        {
            printf("\nEnter value to be added to BST: ");
            scanf("%d", &value);

            root = insertNode(root, value);
        }

        else if (choice == 2) //DELETION
        {
            if (root == NULL)
                printf("\nTree is empty");
            else
            {
                printf("\nEnter value to be deleted: ");
                scanf("%d", &search_value);
                root = deleteNode(root, search_value);
            }
        }
        else if (choice == 3)
        {
            printf("Height of BST : %d", height(root));
        }

        printf("\nPress any key to continue");
        scanf("%*c%*c");

    } while (choice != 4);
}
