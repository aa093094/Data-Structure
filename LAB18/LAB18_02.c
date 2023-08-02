#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int n);
int Min(int x, int y);
void Swap(int nums[], int i, int j, int temp);

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int size = 0;
	fscanf(fp, "%d", &size);
	int nums[20] = { 0 };
	for (int i = 0; i < size; i++)
	{
		int num = 0;
		fscanf(fp, "%d", &num);
		nums[i] = num;
	}
	mergeSort(nums, size);
	printf("nondecreasing order by iterative merge sort : ");
	for (int j = 0; j < size; j++)
	{
		printf("%d ", nums[j]);
	}
	fclose(fp);

	return 0;
}

void mergeSort(int arr[], int n)
{
	int curr_size;  
	int left_start;
	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			int mid = Min(left_start + curr_size - 1, n - 1);

			int right_end = Min(left_start + 2 * curr_size - 1, n - 1);

			merge(arr, left_start, mid, right_end);
		}
	}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[20], R[20];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

int Min(int x, int y) { return (x < y) ? x : y; }

void Swap(int nums[], int i, int j, int temp)
{
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}