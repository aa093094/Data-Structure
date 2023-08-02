#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void quickSort(int nums[], int left, int right);
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
	quickSort(nums, 0, size - 1);
	printf("nondecreasing order by quicksort : ");
	for (int j = 0; j < size; j++)
	{
		printf("%d ", nums[j]);
	}
	fclose(fp);

	return 0;
}

void quickSort(int nums[], int left, int right)
{
	int pivot, i, j;
	int temp = 0;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = nums[left];
		do
		{
			do i++; while (nums[i] < pivot);
			do j--; while (nums[j] > pivot);
			if (i < j)
			{
				Swap(nums, i, j, temp);
			}
		} while (i < j);
		Swap(nums, left, j, temp);
		quickSort(nums, left, j - 1);
		quickSort(nums, j + 1, right);
	}
}

void Swap(int nums[], int i, int j, int temp)
{
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}