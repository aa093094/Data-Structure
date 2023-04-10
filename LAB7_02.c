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
ListNode* combine(ListNode* head, ListNode* last, ListNode* head_2);
void print_list(ListNode* head);

int main()
{
	ListNode* head_1 = (ListNode*)malloc(sizeof(ListNode));
	head_1->link = NULL;
	ListNode* head_2 = (ListNode*)malloc(sizeof(ListNode));
	head_2->link = NULL;
	FILE* fp,* fp_w;
	fp = fopen("input.txt", "r");
	int value = 0;
	int len_1 = 0, len_2 = 0;
	char a = '\0';
	do
	{
		fscanf(fp, "%d", &value);
		ListNode* pre = head_1;
		for (int i = 0; i < len_1; i++)
		{
			pre = pre->link;
		}
		head_1 = insert(head_1, pre, value);
		len_1++;
	} while (a = fgetc(fp) != '\n');
	do
	{
		fscanf(fp, "%d", &value);
		ListNode* pre = head_2;
		for (int i = 0;i < len_2;i++)
		{
			pre = pre->link;
		}
		head_2 = insert(head_2, pre, value);
		len_2++;
	} while (a = fgetc(fp) != EOF);
	fclose(fp);
	ListNode* last_1 = head_1;
	for (int i = 0; i < len_1; i++)
	{
		last_1 = last_1->link;
	}
	combine(head_1, last_1, head_2);
	fp_w = fopen("output.txt", "w");
	ListNode* p = head_1;
	p = p->link;
	for (p; p != NULL; p = p->link)
	{
		fprintf(fp_w, "%d->", p->data);
	}
	fprintf(fp_w, "NULL");
	fclose(fp_w);
	free(head_1);
	free(head_2);

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

ListNode* combine(ListNode* head_1, ListNode* last, ListNode* head_2)
{
	last->link = head_2->link;
	return head_1;
}