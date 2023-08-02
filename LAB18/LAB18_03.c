#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int sorted[20] = { 0 };

void rec_merge(int nums[], int left, int right);
void merge(int nums[], int left, int mid, int right);
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
	rec_merge(nums, 0, size - 1);
	printf("nondecreasing order by recursive merge sort : ");
	for (int j = 0; j < size; j++)
	{
		printf("%d ", nums[j]);
	}
	fclose(fp);

	return 0;
}

void rec_merge(int nums[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;
		rec_merge(nums, left, mid);
		rec_merge(nums, mid + 1, right);
		merge(nums, left, mid, right);
	}
}

void merge(int nums[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right)
	{
		if (nums[i] <= nums[j])
		{
			sorted[k++] = nums[i++];
		}
		else
		{
			sorted[k++] = nums[j++];
		}
	}
	if (i > mid)
	{
		for (l = j; l <= right; l++)
		{
			sorted[k++] = nums[l];
		}
	}
	else
	{
		for (l = i; l <= mid; l++)
		{
			sorted[k++] = nums[l];
		}
	}
	for (l = left; l <= right; l++)
	{
		nums[l] = sorted[l];
	}
}

void Swap(int nums[], int i, int j, int temp)
{
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}