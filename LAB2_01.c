#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void matrix_addtion(int** arr_1, int** arr_2, int** arr_3, int rows, int cols);

int main()
{
	FILE* fp_1, * fp_2;
	int rows = 0, cols = 0, ** arr_1, ** arr_2, ** arr_3;
	fp_1 = fopen("input.txt", "r");
	if (fp_1 == NULL)
	{
		printf("Can't read file");
		exit(1);
	}
	fscanf(fp_1, "%d %d", &rows, &cols);
	arr_1 = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++)
	{
		arr_1[i] = (int*)malloc(cols * sizeof(int));
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fscanf(fp_1, "%d", &arr_1[i][j]);
		}
	}
	arr_2 = (int**)malloc(rows * sizeof(int*));
	for (int p = 0; p < rows; p++)
	{
		arr_2[p] = (int*)malloc(cols * sizeof(int*));
	}
	for (int p = 0; p < rows; p++)
	{
		for (int q = 0; q < cols; q++)
		{
			fscanf(fp_1, "%d", &arr_2[p][q]);
		}
	}
	arr_3 = (int**)malloc(rows * sizeof(int*));
	for (int k = 0; k < rows; k++)
	{
		arr_3[k] = (int*)malloc(cols * sizeof(int*));
	}
	fp_2 = fopen("output.txt", "w");
	matrix_addtion(arr_1, arr_2, arr_3, rows, cols);
	for (int k = 0; k < rows; k++)
	{
		for (int s = 0; s < cols; s++)
		{
			fprintf(fp_2, "%d ", arr_3[k][s]);
		}
		fprintf(fp_2, "\n");
	}
	free(arr_1);
	free(arr_2);
	free(arr_3);
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}

void matrix_addtion(int** arr_1, int** arr_2, int** arr_3, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr_3[i][j] = arr_1[i][j] + arr_2[i][j];
		}
	}
}
