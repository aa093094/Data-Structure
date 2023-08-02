#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
    int key;
    treePointer left;
    treePointer right;
    int height;
} treeNode;

int find_max(int a, int b);
int height(treePointer N);
treePointer newNode(int key);
treePointer rightRotate(treePointer y);
treePointer leftRotate(treePointer x);
int getBalance(treePointer N);
treePointer insertNode(treePointer node, int key);
void printPreOrder(FILE* fp_w, treePointer root, int i);

int main() {
    treePointer root = NULL;
    FILE* fp_r, * fp_w;
    fp_r = fopen("input.txt", "r");
    int size = 0;
    fscanf(fp_r, "%d", &size);
    for (int i = 0; i < size; i++)
    {
        int num = 0;
        fscanf(fp_r, "%d", &num);
        root = insertNode(root, num);
    }
    fclose(fp_r);
    fp_w = fopen("output.txt", "w");
    fprintf(fp_w, "preorder 순서로 출력:\n");
    printPreOrder(fp_w, root, 1);
    fclose(fp_w);
    free(root);

    return 0;
}

int height(treePointer N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int find_max(int a, int b)
{
    return (a > b) ? a : b;
}

treePointer newNode(int key)
{
    treePointer node = (treePointer)malloc(sizeof(treeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

treePointer rightRotate(treePointer y)
{
    treePointer x = y->left;
    treePointer T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = find_max(height(y->left), height(y->right)) + 1;
    x->height = find_max(height(x->left), height(x->right)) + 1;

    return x;
}

treePointer leftRotate(treePointer x)
{
    treePointer y = x->right;
    treePointer T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = find_max(height(x->left), height(x->right)) + 1;
    y->height = find_max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(treePointer N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

treePointer insertNode(treePointer node, int key)
{

    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = 1 + find_max(height(node->left),
        height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printPreOrder(FILE* fp_w, treePointer root, int i)
{
    if (root != NULL)
    {
        if (root->left && root->right)
        {
            fprintf(fp_w, "CBT %d번 노드 = %d    \tbf = %d\n", i, root->key, root->left->height - root->right->height);
        }
        else if (root->left && !root->right)
        {
            fprintf(fp_w, "CBT %d번 노드 = %d    \tbf = %d\n", i, root->key, root->left->height);
        }
        else if (!root->left && root->right)
        {
            fprintf(fp_w, "CBT %d번 노드 = %d    \tbf = %d\n", i, root->key, 0 - root->right->height);
        }
        else
        {
            fprintf(fp_w, "CBT %d번 노드 = %d    \tbf = %d\n", i, root->key, 0);
        }
        printPreOrder(fp_w, root->left, i * 2);
        printPreOrder(fp_w, root->right, i * 2 + 1);
    }
}