#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
	int data;
	struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, int value);
ListNode* insert(ListNode* head, ListNode* pre, int value);
ListNode* delete_first(ListNode* head);
ListNode* delete(ListNode* head, ListNode* pre);
void print_list(ListNode* head);

int main()
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	head->link = NULL;
	FILE* fp;
	fp = fopen("input.txt", "r");
	int value = 0;
	int len = 0;
	char a = '\0';
	do
	{
		fscanf(fp, "%d", &value);
		ListNode* pre = head;
		for (int i = 0; i < len; i++)
		{
				pre = pre->link;
		}
		head = insert(head, pre, value);
		len++;
	} while (a = fgetc(fp) != EOF);
	fclose(fp);
	printf("chain:");
	print_list(head);
	printf("+-------------+\n    1.insert\n    2.delete\n    3.lenth\n    4.exit\n+-------------+\n");
	int choice = 0;
	while (1)
	{
		printf("Menu: ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			int place = 0, value = 0;
			printf("insert: ");
			scanf("%d %d", &place, &value);
			ListNode* pre = head;
			for (int j = 0; j < place; j++)
			{
				pre = pre->link;
			}
			head = insert(head, pre, value);
			len++;
			printf("result: ");
			print_list(head);
		}
		else if (choice == 2)
		{
			int place = 0;
			printf("delete: ");
			scanf("%d", &place);
			ListNode* pre = head;
			for (int j = 1; j < place; j++)
			{
				pre = pre->link;
			}
			head = delete(head, pre);
			len--;
			printf("result: ");
			print_list(head);
		}
		else if (choice == 3)
		{
			printf("length: %d\n", len);
		}
		else
		{
			printf("exit");
			break;
		}
	}
	free(head);

	return 0;
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head)
{
	ListNode* p = head;
	p = p->link;
	for (p; p != NULL; p = p->link)
	{
		printf("%d->", p->data);
	}
	printf("NULL");
	printf("\n");
}