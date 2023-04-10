#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack 
{
	int data;
	struct stack* link;
} stack;
int i = -1;

stack* push(stack* top, int item);
int pop(stack* top);

int main()
{
	stack* top = (stack*)malloc(sizeof(stack));
	FILE* fp, * fp_w;
	fp = fopen("input.txt", "r");
	char a = '\0';
	int value = 0;
	do
	{
		fscanf(fp, "%d", &value);
		top = push(top, value);
	} while (a = fgetc(fp) != EOF);
	fclose(fp);
	fp_w = fopen("output.txt", "w");
	for (i;i > -1;)
	{
		value = pop(top);
		fprintf(fp_w, "%d ", value);
	}
	fclose(fp_w);
	free(top);

	return 0;
}

stack* push(stack* top, int item)
{
	stack* temp = (stack*)malloc(sizeof(stack));
	stack* last = top;
	for (int j = -1; j < i; j++)
	{
		last = last->link;
	}
	temp->data = item;
	temp->link = last->link;
	last->link = temp;
	i++;
	return top;
}

int pop(stack* top)
{
	stack* last = top;
	for (int k = 0; k <= i; k++)
	{
		last = last->link;
	}
	int item;
	item = last->data;
	free(last);
	i--;
	return item;
}