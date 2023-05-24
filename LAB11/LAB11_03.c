#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode* ListPointer;
typedef struct ListNode {
	ListPointer lchild;
	char data;
	ListPointer rchild;
} ListNode;

ListPointer dlinsert(ListPointer head, ListPointer pre, int data);
ListPointer drinsert(ListPointer head, ListPointer pre, int data);
void inorder(ListPointer head);
void preorder(ListPointer head);
void postorder(ListPointer head);

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	ListPointer head = (ListPointer)malloc(sizeof(ListNode));
	head->lchild = NULL;
	head->rchild = NULL;
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
	head->data = tree[1];
	char move[20];
	memset(move, '\0', 20);
	int top = -1;
	int num = 1;
	for (int r = 1; r < 10; r++)
	{
		ListPointer p = head;
		int q = r;
		if (tree[r] != 'N')
		{
			while (q != 1)
			{
				if (q % 2 == 0)
				{
					q = q / 2;
					move[++top] = 'l';
				}
				else
				{
					q = q / 2;
					move[++top] = 'r';
				}
			}
			while (top != -1)
			{
				if (move[top] == 'l')
				{
					p = p->lchild;
					move[top--] = '\0';
				}
				else
				{
					p = p->rchild;
					move[top--] = '\0';
				}
			}
			if (tree[r * 2] == 'N')
			{
				p->lchild = NULL;
			}
			else
			{
				dlinsert(head, p, tree[r * 2]);
				num++;
			}
			if (tree[r * 2 + 1] == 'N')
			{
				p->rchild = NULL;
			}
			else
			{
				drinsert(head, p, tree[r * 2 + 1]);
				num++;
			}
		}
		if (num == size)
		{
			break;
		}
	}
	printf("inorder traversal: ");
	inorder(head);
	printf("\npreorder traversal: ");
	preorder(head);
	printf("\npostorder traversal: ");
	postorder(head);
	free(head);

	return 0;
}

ListPointer dlinsert(ListPointer head, ListPointer pre, int data)
{
	ListPointer p = (ListPointer)malloc(sizeof(ListNode));
	p->data = data;
	p->lchild = NULL;
	p->rchild = NULL;
	pre->lchild = p;
	return head;
}

ListPointer drinsert(ListPointer head, ListPointer pre, int data)
{
	ListPointer p = (ListPointer)malloc(sizeof(ListNode));
	p->data = data;
	p->lchild = NULL;
	p->rchild = NULL;
	pre->rchild = p;
	return head;
}

void inorder(ListPointer head)
{
	if (head)
	{
		inorder(head->lchild);
		printf("%c", head->data);
		inorder(head->rchild);
	}
}

void preorder(ListPointer head)
{
	if (head)
	{
		printf("%c", head->data);
		preorder(head->lchild);
		preorder(head->rchild);
	}
}

void postorder(ListPointer head)
{
	if (head)
	{
		postorder(head->lchild);
		postorder(head->rchild);
		printf("%c", head->data);
	}
}