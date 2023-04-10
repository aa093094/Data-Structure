#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row;
	int col;
	int value;
}matrix;

void mat_multi(int arr_1[20][20], int arr_2[20][20], int arr_3[20][20], int rows_1, int cols_1, int rows_2, int cols_2);

int main()
{
	FILE* fp_1, * fp_2,* fp_3;
	matrix* arr_1, * arr_2, * arr_3;
	fp_1 = fopen("input1.txt", "r");
	int rows_1 = 0, cols_1 = 0;
	int nums_1 = 0;
	fscanf(fp_1, "%d %d %d", &rows_1, &cols_1, &nums_1);
	arr_1 = (matrix*)malloc(nums_1 * sizeof(matrix));
	for (int i = 0; i < nums_1; i++)
	{
		fscanf(fp_1, "%d %d %d", &arr_1[i].row, &arr_1[i].col, &arr_1[i].value);
	}
	fp_2 = fopen("input2.txt", "r");
	int rows_2 = 0, cols_2 = 0;
	int nums_2 = 0;
	fscanf(fp_2, "%d %d %d", &rows_2, &cols_2, &nums_2);
	arr_2 = (matrix*)malloc(nums_2 * sizeof(matrix));
	for (int j = 0; j < nums_2; j++)
	{
		fscanf(fp_2, "%d %d %d", &arr_2[j].row, &arr_2[j].col, &arr_2[j].value);
	}
	int mat_1[20][20] = { 0 }, mat_2[20][20] = { 0 };
	int mat_3[20][20] = { 0 };
	for (int k = 0; k < nums_1; k++)
	{
		mat_1[arr_1[k].row][arr_1[k].col] = arr_1[k].value;
	}
	for (int r = 0; r < nums_2; r++)
	{
		mat_2[arr_2[r].row][arr_2[r].col] = arr_2[r].value;
	}
	mat_multi(mat_1, mat_2, mat_3, rows_1, cols_1, rows_2, cols_2);
	arr_3 = (matrix*)malloc(400 * sizeof(matrix));
	int temp = 0, nums_3 = 0;
	for (int i = 0; i < rows_1; i++)
	{
		for (int j = 0; j < cols_2; j++)
		{
			temp = mat_3[i][j];
			if (temp != 0)
			{
				arr_3[nums_3].row = i;
				arr_3[nums_3].col = j;
				arr_3[nums_3].value = temp;
				nums_3++;
			}
		}
	}
	arr_3 = (matrix*)realloc(arr_3, nums_3 * sizeof(matrix));
	fp_3 = fopen("output.txt", "w");
	fprintf(fp_3, "%d %d %d\n", rows_1, cols_2, nums_3);
	for (int r = 0; r < nums_3; r++)
	{
		fprintf(fp_3, "%d %d %d\n", arr_3[r].row, arr_3[r].col, arr_3[r].value);
	}
	free(arr_1);
	free(arr_2);
	free(arr_3);
	fclose(fp_1);
	fclose(fp_2);
	fclose(fp_3);

	return 0;
}

void mat_multi(int arr_1[20][20], int arr_2[20][20], int arr_3[20][20], int rows_1, int cols_1, int rows_2, int cols_2)
{
	for (int i = 0; i < rows_1; i++)
	{
		for (int j = 0; j < cols_2; j++)
		{
			for (int k = 0; k < rows_2; k++)
			{
				arr_3[i][j] += arr_1[i][k] * arr_2[k][j];
			}
		}
	}
}