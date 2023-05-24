#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
	int data;
	struct ListNode* link;
} ListNode;
int len = 0;

ListNode* insert_first(ListNode* head, int value);
ListNode* insert(ListNode* head, ListNode* pre, int value);
ListNode* delete_first(ListNode* head);
ListNode* delete(ListNode* head, ListNode* pre);
void print_list(ListNode* head);
ListNode* reverse(ListNode* head);

int main()
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	head->link = NULL;
	FILE* fp, * fp_w;
	fp = fopen("input.txt", "r");
	int value = 0;
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
	ListNode* rev_list = reverse(head);
	fp_w = fopen("output.txt", "w");
	for (int i = 0; i < len; rev_list = rev_list->link)
	{
		fprintf(fp_w, "%d->", rev_list->data);
		i++;
	}
	fprintf(fp_w, "NULL");
	fclose(fp_w);
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
	for (int i = 0; i < len; p = p->link)
	{
		printf("%d->", p->data);
		i++;
	}
	printf("NULL");
	printf("\n");
}

ListNode* reverse(ListNode* head)
{
	ListNode* p, * q, * r;
	p = head;
	q = NULL;

	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}