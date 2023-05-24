#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	int arr_1[16];
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
	for (int k = 1; k < 16; k++)
	{
		printf("%d ", arr_1[k]);
		if (k == 1 || k == 3 || k == 7)
		{
			printf("/ ");
		}
	}
	fclose(fp_r);

	return 0;
}