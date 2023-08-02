#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int c_max_heap[30] = { 0 };

void heapsort(int* heap, int n);
void adjust(int* heap, int root, int n);
void swap(int a, int b, int temp);

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int size = 0;
	fscanf(fp, "%d", &size);
	int max_heap[30] = { 0 };
	for (int i = 1; i <= size; i++)
	{
		int num = 0;
		fscanf(fp, "%d", &num);
		max_heap[i] = num;
	}
	heapsort(max_heap, size);
	for (int k = 1; k <= size; k++)
	{
		c_max_heap[k] = max_heap[k];
	}
	int sorted_nums[30] = { 0 };
	int q = 1;
	for (int r = size; r >= 1;)
	{
		int max_num = pop(&r);
		sorted_nums[q++] = max_num;
	}
	printf("오름차순 : ");
	for (int s = size; s >= 1; s--)
	{
		printf("%d ", sorted_nums[s]);
	}
	printf("\ncomplete binary tree : ");
	for (int j = 1; j <= size; j++)
	{
		printf("%d ", max_heap[j]);
	}
	fclose(fp);

	return 0;
}

void heapsort(int* heap, int n)
{
	int i, j, temp = 0;
	for (i = n / 2; i > 0; i--)
	{
		adjust(heap, i, n);
	}
	for (i = n - 1; i > 0; i--)
	{
		swap(heap[1], heap[i + 1], temp);
		adjust(heap, 1, i);
	}
}

void adjust(int* heap, int root, int n)
{
	int child, rootkey, temp;
	temp = heap[root];
	rootkey = heap[root];
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (heap[child] < heap[child + 1]))
		{
			child++;
		}
		if (rootkey > heap[child])
		{
			break;
		}
		else
		{
			heap[child / 2] = heap[child];
			child *= 2;
		}
	}
	heap[child / 2] = temp;
}

void swap(int a, int b, int temp)
{
	temp = a;
	a = b;
	b = temp;
}

int pop(int* n)
{
	int parent, child, item, temp;
	item = c_max_heap[1];
	temp = c_max_heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n)
	{
		if ((child < *n) && (c_max_heap[child] < c_max_heap[child + 1]))
		{
			child++;
		}
		if (temp >= c_max_heap[child]) break;
		c_max_heap[parent] = c_max_heap[child];
		parent = child;
		child *= 2;
	}
	c_max_heap[parent] = temp;
	return item;
}