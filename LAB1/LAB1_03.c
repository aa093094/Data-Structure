#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int size, arr_1[5][5], arr_2[5][5], arr_3[5][5];
	FILE* fp1;
	FILE* fp2;
	fp1 = fopen("input.txt", "r");
	fscanf(fp1, "%d", &size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int num_1 = 0;
			fscanf(fp1, "%d", &num_1);
			arr_1[i][j] = num_1;
		}
	}
	for (int k = 0; k < size; k++)
	{
		for (int r = 0; r < size; r++)
		{
			int num_2 = 0;
			fscanf(fp1, "%d", &num_2);
			arr_2[k][r] = num_2;
		}
	}
	int t = 0, count = 0, e = 0;
	for (int p = 0; p < size; p++)
	{
		for (int q = 0; q < size; q++)
		{
			arr_3[p][q] = 0;
			for (int t = 0; t < size; t++)
			{
				arr_3[p][q] += arr_1[p][t] * arr_2[t][q];
			}
		}
	}
	
	fp2 = fopen("output.txt", "w");
	for (int m = 0; m < size; m++)
	{
		for (int n = 0; n < size; n++)
		{
			fprintf(fp2, "%d ", arr_3[m][n]);
		}
		fprintf(fp2, "\n");
	}

	return 0;
}