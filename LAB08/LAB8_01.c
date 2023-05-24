#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct
{
	int coef;
	int expon;
} element;

typedef struct ListNode
{
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element value);
ListNode* insert_last(ListNode* head, ListNode* last, element value);
void print_clist(ListNode* head);
ListNode* PolyAdd(ListNode* a, ListNode* b);

int main()
{
	FILE* fp_r, * fp_w;
	fp_r = fopen("input.txt", "r");
	int n = 0, m = 0;
	fscanf(fp_r, "%d %d", &n, &m);
	ListNode* a = (ListNode*)malloc(sizeof(ListNode));
	ListNode* b = (ListNode*)malloc(sizeof(ListNode));
	ListNode* c = (ListNode*)malloc(sizeof(ListNode));
	a->data.expon = -1, a->data.coef = 0, a->link = a;
	b->data.expon = -1, b->data.coef = 0, b->link = b;
	c->data.expon = -1, c->data.coef = 0, c->link = c;
	for (int i = 0; i < n; i++)
	{
		element value;
		value.coef = 0, value.expon = 0;
		fscanf(fp_r, "%d %d", &value.coef, &value.expon);
		ListNode* last = a;
		int tp_i = i;
		for (int tp_i = 0; tp_i < i; tp_i++)
		{
			last = last->link;
		}
		a = insert_last(a, last, value);
	}
	for (int j = 0; j < m; j++)
	{
		element value;
		value.coef = 0, value.expon = 0;
		fscanf(fp_r, "%d %d", &value.coef, &value.expon);
		ListNode* last = b;
		int tp_j = j;
		for (int tp_j = 0; tp_j < j; tp_j++)
		{
			last = last->link;
		}
		b = insert_last(b, last, value);
	}
	fclose(fp_r);
	c = PolyAdd(a, b);
	c = c->link;
	fp_w = fopen("output.txt", "w");
	for (int k = 0; k < count; k++)
	{
		fprintf(fp_w, "%d %d\n", c->data.coef, c->data.expon);
		c = c->link;
	}
	fclose(fp_w);
	free(a);
	free(b);
	free(c);

	return 0;
}

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	if (head == NULL)
	{
		head->link = p;
		p->link = head;
	}
	else
	{
		p->link = head->link;
		head->link = p;
	}
	return head;
}

ListNode* insert_last(ListNode* head, ListNode* last, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	if (head == NULL)
	{
		head->link = p;
		p->link = head;
	}
	else
	{
		p->link = head;
		last->link = p;
	}
	return head;
}

void print_clist(ListNode* head)
{
	ListNode* p = head;
	ListNode* tp_head = p;
	p = p->link;
	printf("Head->");
	for (p; p != tp_head; p = p->link)
	{
		printf("%d %d->", p->data.coef, p->data.expon);
	}
	printf("Head");
}

ListNode* PolyAdd(ListNode* a, ListNode* b)
{
	ListNode* c = (ListNode*)malloc(sizeof(ListNode));
	c->data.expon = -1, c->data.coef = 0, c->link = c;
	ListNode* head_a = a;
	ListNode* head_b = b;
	a = a->link;
	b = b->link;
	ListNode* last = c;
	while (1)
	{
		if (a->data.expon < b->data.expon)
		{
			c = insert_last(c, last, b->data);
			b = b->link;
			count++;
		}
		else if (a->data.expon == b->data.expon)
		{
			int sum = a->data.coef + b->data.coef;
			element value;
			value.coef = sum;
			value.expon = b->data.expon;
			c = insert_last(c, last, value);
			count++;
			a = a->link;
			b = b->link;
		}
		else
		{
			c = insert_last(c, last, a->data);
			a = a->link;
			count++;
		}
		last = last->link;
		if (a->data.expon == -1 && b->data.expon == -1)
		{
			break;
		}
	}
	return c;
}