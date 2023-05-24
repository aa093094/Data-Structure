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

treePointer copytree(int original, char* tree);
void inorder(treePointer head);

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
	while ((a = fgetc(fp)) != EOF)
	{
		if (a != 'N' && a != ' ' && a != '\n')
		{
			tree[i++] = a;
		}
		else if(a == ' ' || a == '\n')
		{
			
		}
		else
		{
			i++;
		}
	}
	fclose(fp);
	treePointer c_tree = copytree(1, tree);
	printf("recursive implementation of inorder traversal : ");
	inorder(c_tree);
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

void inorder(treePointer head)
{
	if (head)
	{
		inorder(head->leftchild);
		printf("%c", head->data);
		inorder(head->rightchild);
	}
}