#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftchild;
	char data;
	treePointer rightchild;
} treeNode;
int top = -1;
treePointer stack[20];

treePointer copytree(int original, char* tree);
void iterPreorder(treePointer head);
void push(treePointer node);
treePointer pop();

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int size = 0;
	fscanf(fp, "%d", &size);
	char tree[20];
	memset(tree, 'N', 20);
	char a = '\0';
	int i = 1;
	int count = 0;
	while ((a = fgetc(fp)) != EOF)
	{
		if (a != 'N' && a != ' ' && a != '\n')
		{
			tree[i++] = a;
			count++;
		}
		else if (a == ' ' || a == '\n')
		{

		}
		else
		{
			i++;
		}
		if (count == size)
		{
			break;
		}
	}
	fclose(fp);
	treePointer c_tree = copytree(1, tree);
	printf("iterative implementation of preorder traversal : ");
	iterPreorder(c_tree);
	free(c_tree);

	return 0;
}

treePointer copytree(int original, char* tree)
{
	treePointer temp;
	if (original < 20 && tree[original] != 'N')
	{
		temp = (treePointer)malloc(sizeof(treeNode));
		temp->leftchild = copytree(original * 2, tree);
		temp->rightchild = copytree(original * 2 + 1, tree);
		temp->data = tree[original];
		return temp;
	}
	return NULL;
}

void iterPreorder(treePointer node)
{
	int k = 0;
	for (;;)
	{
		if (k == 0)
		{
			for (; node; node = node->leftchild)
			{
				printf("%c", node->data);
				push(node);
			}
			node = pop();
		}
		if (!node) break;
		if (node->rightchild)
		{
			node = node->rightchild;
			if (node->leftchild)
			{
				k = 0;
			}
			else if (node->rightchild)
			{
				printf("%c", node->data);
				k = 1;
			}
			else
			{
				printf("%c", node->data);
				k = 1;
				node = pop();
			}
		}
		else
		{
			node = pop();
			k = 1;
		}
	}
}

void push(treePointer node)
{
	stack[++top] = node;
}

treePointer pop()
{
	return stack[top--];
}