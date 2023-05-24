#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* fp_1, * fp_2;
	char** arr_1;
	arr_1 = (char**)malloc(50 * sizeof(char*));
	fp_1 = fopen("input.txt", "r");
	int a = 0;
	fp_2 = fopen("output.txt", "w");
	for (int i = 0; i < 2; i++)
	{
		fgets(arr_1, 50, fp_1);
		fprintf(fp_2, "%s", arr_1);
	}
	free(arr_1);
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}