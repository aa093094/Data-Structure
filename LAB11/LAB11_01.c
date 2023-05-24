#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inorder(int ptr, char tree[20]);
void preorder(int ptr, char tree[20]);
void postorder(int ptr, char tree[20]);

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	char tree[20];
	memset(tree, 'N', 20);
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
			tree[ptr++] = a;
			i++;
		}
	}
	fclose(fp_r);
	printf("inorder traversal: ");
	inorder(1, tree);
	printf("\npreorder traversal: ");
	preorder(1, tree);
	printf("\npostorder traversal: ");
	postorder(1, tree);

	return 0;
}

void inorder(int ptr, char tree[20])
{
	if (tree[ptr] != 'N' && ptr < 20)
	{
		inorder(ptr * 2, tree);
		printf("%c", tree[ptr]);
		inorder(ptr * 2 + 1, tree);
	}
}

void preorder(int ptr, char tree[20])
{
	if (tree[ptr] != 'N' && ptr < 20)
	{
		printf("%c", tree[ptr]);
		preorder(ptr * 2, tree);
		preorder(ptr * 2 + 1, tree);
	}
}

void postorder(int ptr, char tree[20])
{
	if (tree[ptr] != 'N' && ptr < 20)
	{
		postorder(ptr * 2, tree);
		postorder(ptr * 2 + 1, tree);
		printf("%c", tree[ptr]);
	}
}