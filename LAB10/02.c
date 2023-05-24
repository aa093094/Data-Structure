#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	int arr_1[16];
	int llink[8] = { 0 };
	int rlink[8] = { 0 };
	for (int j = 0; j <= 15; j++)
	{
		arr_1[j] = -1;
	}
	int size = 0;
	fscanf(fp_r, "%d", &size);
	for (int i = 1; i <= 15; i++)
	{
		int a = -1;
		fscanf(fp_r, "%d", &a);
		if (a == -1)
		{
			continue;
		}
		else
		{
			arr_1[i] = a;
		}
	}
	for (int r = 1; r <= 7; r++)
	{
		if (arr_1[r * 2] != -1)
		{
			llink[r] = r * 2;
		}
		else
		{
			llink[r] = -1;
		}
		if (arr_1[r * 2 + 1] != -1)
		{
			rlink[r] = r * 2 + 1;
		}
		else
		{
			rlink[r] = -1;
		}
	}
	for (int k = 1; k < 16; k++)
	{
		printf("%d ", arr_1[k]);
		if (k == 1 || k == 3 || k == 7)
		{
			printf("/ ");
		}
	}
	printf("\nllink: ");
	for (int s = 1; s <= 7; s++)
	{
		printf("%d ", llink[s]);
	}
	printf("\nrlink: ");
	for (int s = 1; s <= 7; s++)
	{
		printf("%d ", rlink[s]);
	}
	fclose(fp_r);

	return 0;
}