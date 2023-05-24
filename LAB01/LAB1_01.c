#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen("input.txt", "r");
	int num = 0;
	fscanf(fp1, "%d", &num);
	int sum = 0;
	for (int i = 1; i <= num; i++)
	{
		sum = sum + i;
	}
	fp2 = fopen("output.txt", "w");
	fprintf(fp2, "%d", sum);
	fclose(fp1);
	fclose(fp2);

	return 0;
}