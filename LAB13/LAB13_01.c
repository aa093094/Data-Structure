#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftchild;
	int data;
	treePointer rightchild;
} treeNode;

treePointer copytree(int original, int* tree);
int equal(treePointer first, treePointer second);
void inorder(treePointer head);

int main()
{
	FILE* fp_1, * fp_2;
	fp_1 = fopen("input1.txt", "r");
	int size = 0;
	fscanf(fp_1, "%d", &size);
	int tree_1[50];
	int tree_2[50];
	for (int j = 0; j < 50; j++)
	{
		tree_1[j] = -1;
		tree_2[j] = -1;
	}
	int i = 1;
	int count = 0;
	while (count < size)
	{
		int num = -1;
		fscanf(fp_1, "%d", &num);
		if (num == -1)
		{
			i++;
		}
		else
		{
			tree_1[i++] = num;
			count++;
		}
	}
	fclose(fp_1);
	treePointer c_tree_1 = copytree(1, tree_1);
	fp_2 = fopen("input2.txt", "r");
	int size_2 = 0;
	fscanf(fp_2, "%d", &size_2);
	if (size != size_2)
	{
		printf("Not equal!");
		exit(EXIT_FAILURE);
	}
	else
	{
		int i_2 = 1;
		int count_2 = 0;
		while (count_2 < size)
		{
			int num = -1;
			fscanf(fp_2, "%d", &num);
			if (num == -1)
			{
				i_2++;
			}
			else
			{
				tree_2[i_2++] = num;
				count_2++;
			}
		}
	}
	fclose(fp_2);
	treePointer c_tree_2 = copytree(1, tree_2);
	int its_equal = equal(c_tree_1, c_tree_2);
	if (its_equal)
	{
		printf("Two trees equal!");
	}
	else
	{
		printf("Two trees not equal!");
	}
	free(c_tree_1);
	free(c_tree_2);

	return 0;
}

treePointer copytree(int original, int* tree)
{
	treePointer temp;
	if (original < 50 && tree[original] != -1)
	{
		temp = (treePointer)malloc(sizeof(treeNode));
		temp->leftchild = copytree(original * 2, tree);
		temp->rightchild = copytree(original * 2 + 1, tree);
		temp->data = tree[original];
		return temp;
	}
	return NULL;
}

int equal(treePointer first, treePointer second)
{
	return ((!first && !second) || (first && second && (first->data == second->data) && equal(first->leftchild, second->leftchild) && equal(first->rightchild, second->rightchild)));
}

void inorder(treePointer head)
{
	if (head)
	{
		inorder(head->leftchild);
		printf("%d ", head->data);
		inorder(head->rightchild);
	}
}