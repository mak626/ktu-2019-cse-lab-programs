//imp
void inOrder(struct Node *root)
{
    // Base Case
    if (root == NULL)
        printf("Tree is empty");

    while (root != NULL || top != -1)
    {
        /* Reach the left most Node of the root Node */
        while (root != NULL)
        {
            /* place pointer to a tree node on 
               the stack before traversing 
              the node's left subtree */
            push(root);
            root = root->left;
        }

        /* root must be NULL at this point */
        root = pop();
        printf("%d", root->data);

        /* we have visited the node and its 
           left subtree.  Now, it's right 
           subtree's turn */
        root = root->right;
    }
}

//imp
void Preorderiterative(node *root)
{
    // Base Case
    if (root == NULL)
        printf("Tree is empty");

    // Create an empty stack and push root to it
    push(root);

    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */
    while (top != -1)
    {
        // Pop the top item from stack and print it
        root = pop();
        printf("%d ", root->data);

        // Push right and left children of the popped node to stack
        if (root->right != NULL)
            push(root->right);
        if (root->left != NULL)
            push(root->left);
    }
}

// An iterative function to do postorder traversal of a given binary tree
void postOrderIterative(struct Node *root)
{
    // Check for empty tree
    if (root == NULL)
        printf("Tree is empty");

    do
    {
        // Move to leftmost node
        while (root != NULL)
        {
            // Push root's right child and then root to stack.
            if (root->right != NULL)
                push(root->right);

            push(root);

            // Set root as root's left child
            root = root->left;
        }

        // Pop an item from stack and set it as root
        root = pop();

        // If the popped item has a right child and the right child is not
        // processed yet, then make sure right child is processed before root
        if (root->right != NULL && stack[top] == root->right)
        {
            pop();              // remove right child from stack
            push(root);         // push root back to stack
            root = root->right; // change root so that the right child is processed next
        }
        else // Else print root's data and set root as NULL
        {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (top != -1)
}

int leaf(Node *ptr)
{
    if (ptr == NULL)
        return 0;
    else if (ptr->Rchild == NULL && ptr->Lchild == NULL)
        return 1;
    else
        return leaf(ptr->Lchild) + leaf(ptr->Rchild);
}

Node *deleteNodeBinaryTree(Node *root, int search_value)
{

    if (root == NULL) //Base case
        return root;
    else if (search_value != root->data)
    {
        root->Lchild = deleteNode(root->Lchild, search_value);
        root->Rchild = deleteNode(root->Rchild, search_value);
    }
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

int isFullTree(struct Node *root) // Returns true if Binary Tree is full ELSE returns false
{
    if (root == NULL || root->left == NULL && root->right == NULL)
        return 1;
    else if ((root->left) != NULL && (root->right) != NULL)
        return (isFullTree(root->left) && isFullTree(root->right));
    else
        return 0;
}

int PerfectSumTree(struct Node *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL)) // Full tree
        return 1;
    else if (root->left != NULL || root->right != NULL) // Only 1 child
        return 0;
    else
    {
        if (root->data == (root->left->data + root->right->data))
            return PerfectSumTree(root->left) && PerfectSumTree(root->left);
        else
            return 0;
    }
}