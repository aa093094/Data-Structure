#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	int lchild;
	int rchild;
} node;

void inorder(int ptr, node tree[20]);
void preorder(int ptr, node tree[20]);
void postorder(int ptr, node tree[20]);

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	node tree[20];
	for (int j = 0; j < 20; j++)
	{
		tree[j].data = 'N';
		tree[j].lchild = -1;
		tree[j].rchild = -1;
	}
	int size = 0;
	fscanf(fp_r, "%d", &size);
	int i = 0;
	int ptr = 1;
	while (i < size)
	{
		char a = '\0';
		fscanf(fp_r, "%c", &a);
		if (a == 'N')
		{
			ptr++;
		}
		else if (a == ' ' || a == '\n')
		{

		}
		else
		{
			tree[ptr++].data = a;
			i++;
		}
	}
	fclose(fp_r);
	for (int k = 1; k < 10; k++)
	{
		if (tree[k*2].data != 'N')
		{
			tree[k].lchild = k * 2;
		}
		if (tree[k * 2 + 1].data != 'N')
		{
			tree[k].rchild = k * 2 + 1;
		}
	}
	printf("inorder traversal: ");
	inorder(1, tree);
	printf("\npreorder traversal: ");
	preorder(1, tree);
	printf("\npostorder traversal: ");
	postorder(1, tree);

	return 0;
}

void inorder(int ptr, node tree[20])
{
	if (tree[ptr].data != 'N')
	{
		if (tree[ptr].lchild != -1)
		{
			inorder(tree[ptr].lchild, tree);
		}
		printf("%c", tree[ptr].data);
		if (tree[ptr].rchild != -1)
		{
			inorder(tree[ptr].rchild, tree);
		}
	}
}

void preorder(int ptr, node tree[20])
{
	if (tree[ptr].data != 'N')
	{
		printf("%c", tree[ptr].data);
		if (tree[ptr].lchild != -1)
		{
			preorder(tree[ptr].lchild, tree);
		}
		if (tree[ptr].rchild != -1)
		{
			preorder(tree[ptr].rchild, tree);
		}
	}
}

void postorder(int ptr, node tree[20])
{
	if (tree[ptr].data != 'N')
	{
		if (tree[ptr].lchild != -1)
		{
			postorder(tree[ptr].lchild, tree);
		}
		if (tree[ptr].rchild != -1)
		{
			postorder(tree[ptr].rchild, tree);
		}
		printf("%c", tree[ptr].data);
	}
}