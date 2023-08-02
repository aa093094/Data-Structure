#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
typedef struct TreeNode {
    char val;
    int index;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
int index_size = 0;

// Helper function to search for an element in an inorder array
int search(char arr[], int start, int end, char value) 
{
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;  // Element not found
}

// Recursive function to construct the binary tree
TreeNode* buildTreeHelper(char preorder[], char inorder[], int inStart, int inEnd, int* preIndex, int index) 
{
    // Base case
    if (inStart > inEnd) {
        return NULL;
    }

    // Create a new node with the current preorder element
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = preorder[*preIndex];
    newNode->index = index;
    newNode->left = NULL;
    newNode->right = NULL;

    // Find the index of the current preorder element in the inorder array
    int inIndex = search(inorder, inStart, inEnd, preorder[*preIndex]);

    // Increment the preorder index
    (*preIndex)++;

    // Recursively build the left and right subtrees
    newNode->left = buildTreeHelper(preorder, inorder, inStart, inIndex - 1, preIndex, 2*index);
    newNode->right = buildTreeHelper(preorder, inorder, inIndex + 1, inEnd, preIndex, 2*index+1);

    return newNode;
}

// Function to construct the binary tree from preorder and inorder traversals
TreeNode* buildTree(char preorder[], char inorder[], int size, int index)
{
    int preIndex = 0;  // Index for the preorder array
    return buildTreeHelper(preorder, inorder, 0, size - 1, &preIndex, index);
}

// Function to print the inorder traversal of a binary tree (for testing)
void inorderTraversal(TreeNode* root, int indexs[])
{
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, indexs);
    indexs[root->index] = root->index;
    inorderTraversal(root->right, indexs);
}

void init(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = '\0';
    }
}

int main() 
{
    FILE* fp_r, * fp_w;
    fp_r = fopen("input.txt", "r");
    char pre[100];
    init(pre, 100);
    char in[100];
    init(in, 100);
    fgets(pre, 100, fp_r);
    fgets(in, 100, fp_r);
    char preorder[20];
    init(preorder, 20);
    char inorder[20];
    init(inorder, 20);
    int i = 20;
    int count = 0;
    while (1)
    {
        if (pre[i] != '\n')
        {
            preorder[i - 20] = pre[i];
            i++;
            count++;
        }
        else
        {
            break;
        }
    }
    int j = 19;
    while (1)
    {
        if (in[j] != '\0')
        {
            inorder[j - 19] = in[j];
            j++;
        }
        else
        {
            break;
        }
    }
    fclose(fp_r);
    TreeNode* root = buildTree(preorder, inorder, count, 1);
    int indexs[100] = { 0 };
    inorderTraversal(root, indexs);
    int a = 0;
    fp_w = fopen("output.txt", "w");
    for (int k = 1; k < 100; k++)
    {
        if (indexs[k] != 0)
        {
            if (a == count - 1)
            {
                fprintf(fp_w, "%d", indexs[k]);
                break;
            }
            else
            {
                fprintf(fp_w, "%d, ", indexs[k]);
                a++;
            }
        }
    }
    fclose(fp_w);
    free(root);
    
    return 0;
}