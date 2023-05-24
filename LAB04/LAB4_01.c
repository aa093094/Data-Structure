#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row;
	int col;
	int value;
}matrix;

void fast_transpose(matrix arr_1[400], matrix arr_2[400], int rows, int nums);

int main()
{
	FILE* fp_1, * fp_2;
	matrix* arr_1,* arr_2;
	arr_1 = (matrix*)malloc(400 * sizeof(matrix));
	fp_1 = fopen("input.txt", "r");
	int rows = 0, nums = 0;
	int temp = 0;
	fscanf(fp_1, "%d", &rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			fscanf(fp_1, "%d", &temp);
			if (temp != 0)
			{
				arr_1[nums].row = i;
				arr_1[nums].col = j;
				arr_1[nums].value = temp;
				nums++;
			}
		}
	}
	arr_1 = (matrix*)realloc(arr_1, nums * sizeof(matrix));
	arr_2 = (matrix*)malloc(nums * sizeof(matrix));
	fp_2 = fopen("output.txt", "w");
	fprintf(fp_2, "%d\n", nums);
	fast_transpose(arr_1, arr_2, rows, nums);
	for (int r = 0; r < nums; r++)
	{
		fprintf(fp_2, "%d %d %d\n", arr_2[r].row, arr_2[r].col, arr_2[r].value);
	}
	free(arr_1);
	free(arr_2);
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}


void fast_transpose(matrix arr_1[400], matrix arr_2[400], int rows, int nums)
{
	int rowterms[400] = { 0 };
	int start_pos[400] = { 0 };
	int temp = 0;
	for (int i = 0; i < nums; i++)
	{
		temp = arr_1[i].col;
		rowterms[temp]++;
	}
	for (int j = 0; j < rows - 1; j++)
	{
		start_pos[j + 1] = start_pos[j] + rowterms[j];
	}
	int col = 0, row = 0, value = 0;
	for (int k = 0; k < nums; k++)
	{
		col = arr_1[k].col;
		row = arr_1[k].row;
		value = arr_1[k].value;
		arr_2[start_pos[col]].row = col;
		arr_2[start_pos[col]].col = row;
		arr_2[start_pos[col]].value = value;
		start_pos[col]++;
	}
}