#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp1;
	FILE *fp2;
	int size, * arr_1;
	fp1 = fopen("input.txt", "r");
	fscanf(fp1, "%d", &size);
	arr_1 = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		int num = 0;
		fscanf(fp1, "%d", &num);
		arr_1[i] = num;
	}
	int sum = 0;
	for (int j = 0; j < size; j++)
	{
		sum = sum + arr_1[j];
	}
	fp2 = fopen("output.txt", "w");
	fprintf(fp2, "%d", sum);

	return 0;
}