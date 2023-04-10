#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int accountNum;
	char name[30];
	int deposit;
	int loan;
}account;

int main()
{
	account num[50];
	FILE* fp_1, * fp_2;
	int i = 0, a = 0;
	fp_1 = fopen("input.txt", "r");
	while ((a = fgetc(fp_1)) != EOF)
	{
		fscanf(fp_1, "%d %s %d %d", &num[i].accountNum, num[i].name, &num[i].deposit, &num[i].loan);
		i++;
	}
	fp_2 = fopen("output.txt", "w");
	int max = num[0].loan;
	int max_num = 0;
	for (int j = 1; j < i; j++)
	{
		if (num[j].loan > max)
		{
			max = num[j].loan;
			max_num = j;
		}
	}
	fprintf(fp_2, "%d %s %d %d", num[max_num].accountNum, num[max_num].name, num[max_num].deposit, num[max_num].loan);
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}