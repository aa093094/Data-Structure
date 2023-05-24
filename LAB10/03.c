#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode *ListPointer;
typedef struct ListNode
{
	ListPointer llink;
	int data;
	ListPointer rlink;
} ListNode;

ListPointer dlinsert(ListPointer head, ListPointer pre, int data);
ListPointer drinsert(ListPointer head, ListPointer pre, int data);

int main()
{
	FILE *fp_r;
	fp_r = fopen("input.txt", "r");
	ListPointer head = (ListPointer)malloc(sizeof(ListNode));
	head->llink = NULL;
	head->rlink = NULL;
	int *arr_1;
	char *arr_2;
	int size = 0;
	fscanf(fp_r, "%d", &size);
	int arr_size = 1;
	for (int i = 1; i <= size; i++)
	{
		arr_size *= 2;
	}
	arr_1 = (int *)malloc(arr_size * sizeof(int));
	for (int j = 0; j < arr_size; j++)
	{
		arr_1[j] = -1;
	}
	for (int k = 1; k < arr_size; k++)
	{
		int a = -1;
		fscanf(fp_r, "%d", &a);
		if (a == -1)
		{
			continue;
		}
		else
		{
			arr_1[k] = a;
		}
	}
	head->data = arr_1[1];
	int ch_size = size;
	arr_2 = (char *)malloc(ch_size * sizeof(char));
	for (int t = 0; t < ch_size; t++)
	{
		arr_2[t] = '\0';
	}
	int top = -1;
	int num = 1;
	for (int r = 1; r < arr_size / 2; r++)
	{
		ListPointer p = head;
		int q = r;
		if (arr_1[r] != -1)
		{
			while (q != 1)
			{
				if (q % 2 == 0)
				{
					q = q / 2;
					arr_2[++top] = 'l';
				}
				else
				{
					q = q / 2;
					arr_2[++top] = 'r';
				}
			}
			while (top != -1)
			{
				if (arr_2[top] == 'l')
				{
					p = p->llink;
					arr_2[top--] = '\0';
				}
				else
				{
					p = p->rlink;
					arr_2[top--] = '\0';
				}
			}
			if (arr_1[r * 2] == -1)
			{
				p->llink = NULL;
			}
			else
			{
				dlinsert(head, p, arr_1[r * 2]);
				num++;
			}
			if (arr_1[r * 2 + 1] == -1)
			{
				p->rlink = NULL;
			}
			else
			{
				drinsert(head, p, arr_1[r * 2 + 1]);
				num++;
			}
		}
		if (num == size)
		{
			break;
		}
	}
	printf("Print left and right components\n");
	for (ListPointer temp = head; temp != NULL; temp = temp->llink)
	{
		printf("%d->", temp->data);
	}
	printf("\n");
	for (ListPointer temp = head; temp != NULL; temp = temp->rlink)
	{
		printf("%d->", temp->data);
	}
	fclose(fp_r);
	free(head);

	return 0;
}

ListPointer dlinsert(ListPointer head, ListPointer pre, int data)
{
	ListPointer p = (ListPointer)malloc(sizeof(ListNode));
	p->data = data;
	p->llink = NULL;
	p->rlink = NULL;
	pre->llink = p;
	return head;
}

ListPointer drinsert(ListPointer head, ListPointer pre, int data)
{
	ListPointer p = (ListPointer)malloc(sizeof(ListNode));
	p->data = data;
	p->llink = NULL;
	p->rlink = NULL;
	pre->rlink = p;
	return head;
}