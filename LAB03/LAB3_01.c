#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int polynomial[2][20] = { 0 };

void poly_add(int start_1, int finish_1, int start_2, int finish_2, int* start_3, int* finish_3);

int main()
{
	FILE* fp_1, * fp_2;
	int num_1 = 0, num_2 = 0;
	fp_1 = fopen("input.txt", "r");
	fscanf(fp_1, "%d %d", &num_1, &num_2);
	int start_1 = 0, start_2 = num_1;
	int finish_1 = num_1 - 1, finish_2 = num_2 + num_1 - 1;
	int start_3 = finish_2 + 1, finish_3 = 0;
	for (int i = 0; i < start_2; i++)
	{
		fscanf(fp_1, "%d %d", &polynomial[0][i], &polynomial[1][i]);
	}
	for (int j = start_2; j < start_3; j++)
	{
		fscanf(fp_1, "%d %d", &polynomial[0][j], &polynomial[1][j]);
	}
	poly_add(start_1, finish_1, start_2, finish_2, start_3, &finish_3);
	fp_2 = fopen("output.txt", "w");
	for (; start_3 < finish_3; start_3++)
	{
		fprintf(fp_2, "%d %d\n", polynomial[0][start_3], polynomial[1][start_3]);
	}
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}

void poly_add(int start_1, int finish_1, int start_2, int finish_2, int start_3, int* finish_3)
{
	int count = 0;

	while (start_1 <= finish_1 && start_2 <= finish_2)
	{
		if (polynomial[1][start_1] < polynomial[1][start_2])
		{
			polynomial[1][start_3] = polynomial[1][start_2];
			polynomial[0][start_3] = polynomial[0][start_2];
			start_2++, start_3++;
		}
		else if (polynomial[1][start_1] == polynomial[1][start_2])
		{
			if (polynomial[1][start_1] == 0 && polynomial[0][start_1] == 0)
			{
				if (polynomial[1][start_2] == 0 && polynomial[0][start_2] == 0)
				{
					break;
				}
			}
			polynomial[0][start_3] = polynomial[0][start_1] + polynomial[0][start_2];
			polynomial[1][start_3] = polynomial[1][start_1];
			start_1++, start_2++, start_3++;
			count++;
		}
		else if (polynomial[1][start_1] > polynomial[1][start_2])
		{
			polynomial[1][start_3] = polynomial[1][start_1];
			polynomial[0][start_3] = polynomial[0][start_1];
			start_1++, start_3++;
		}

		if (start_1 > finish_1 && start_2 > finish_2)
		{
			break;
		}
		else if (start_1 > finish_1)
		{
			start_1--;
			polynomial[1][start_1] = 0;
			polynomial[0][start_1] = 0;
		}
		else if (start_2 > finish_2)
		{
			start_2--;
			polynomial[1][start_2] = 0;
			polynomial[0][start_2] = 0;
		}
	}
	*finish_3 = start_3;
}
