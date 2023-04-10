#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp_1, * fp_2;
	int size;
	float* arr_1;
	fp_1 = fopen("input.txt", "r");
	fscanf(fp_1, "%d", &size);
	arr_1 = (float*)malloc(size * sizeof(float));
	for (int i = 0; i < size; i++)
	{
		fscanf(fp_1, "%f", &arr_1[i]);
	}
	fp_2 = fopen("output.txt", "w");
	for (int j = 0; j < size; j++)
	{
		int num = (int)arr_1[j];
		if (num != arr_1[j])
		{
			fprintf(fp_2, "%f ", arr_1[j]);
		}
	}
	fclose(fp_1);
	fclose(fp_2);
	free(arr_1);

	return 0;
}