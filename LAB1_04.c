#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int bin_search(int list[], int search_num, int left, int right)
{
	int middle;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if (list[middle] == search_num)
		{
			return middle;
		}
		else if (list[middle] < search_num)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	return -1;
}

int main()
{
	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	int size, num, *arr_1;
	fscanf(fp1, "%d %d", &size, &num);
	arr_1 = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		int k = 0;
		fscanf(fp1, "%d", &k);
		arr_1[i] = k;
	}
	int left = 0, right = size - 1;
	int result = bin_search(arr_1, num, left, right);
	fp2 = fopen("output.txt", "w");
	fprintf(fp2, "%d", result);

	return 0;
}