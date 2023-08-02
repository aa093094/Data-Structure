#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int parent[30];

void weightedUnion(int i, int j);
void equi_classes(FILE* fp_w, int* parent, int n);

int main()
{
	FILE* fp, * fp_w;
	fp = fopen("input.txt", "r");
	int nums = 0;
	fscanf(fp, "%d", &nums);
	int first[30] = { 0 };
	int second[30] = { 0 };
	for (int i = 0; i < nums; i++)
	{
		int a = 0, b = 0;
		char equal = '\0', apo = '\0';
		fscanf(fp, "%d %c %d", &a, &equal, &b);
		if (equal == '=')
		{
			first[i] = a;
			second[i] = b;
		}
		fscanf(fp, "%c", &apo);
		if (apo == EOF) break;
	}
	fclose(fp);
	for (int e = 0; e < 30; e++)
	{
		parent[e] = 100;
	}
	for (int j = 0; j < nums; j++)
	{
		if (parent[first[j]] != -1)
		{
			parent[first[j]] = -1;
		}
		if (parent[second[j]] != -1)
		{
			parent[second[j]] = -1;
		}
	}
	int placed[30] = { 0 };
	for (int r = 0; r < 30; r++)
	{
		for (int q = 0; q < nums; q++)
		{
			if (first[q] == r)
			{
				placed[r]++;
			}
			if (second[q] == r)
			{
				placed[r]++;
			}
		}
	}
	for (int k = 0; k < nums; k++)
	{
		weightedUnion(first[k], second[k]);
	}
	int count = 0;
	for (int s = 0; s < 30; s++)
	{
		if (parent[s] < 0)
		{
			count++;
		}
	}
	fp_w = fopen("output.txt", "w");
	fprintf(fp_w, "Total # of equivalence classes = %d\n", count);
	fprintf(fp_w, "Equivalence classes : ");
	for (int p = 0; p < 30; p++)
	{
		if (parent[p] >= 0)
		{

		}
		else
		{
			fprintf(fp_w, "{");
		}
		if (parent[p] < 0)
		{
			equi_classes(fp_w, parent, p);
		}
		if (parent[p] >= 0)
		{

		}
		else
		{
			fprintf(fp_w, "}, ");
		}
	}
	fclose(fp_w);

	return 0;
}

void weightedUnion(int i, int j)
{
	while (parent[i] >= 0)
	{
		i = parent[i];
	}
	while (parent[j] >= 0)
	{
		j = parent[j];
	}
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		parent[i] = j;
		parent[j] = temp;
	}
	else
	{
		parent[j] = i;
		parent[i] = temp;
	}
}

void equi_classes(FILE* fp_w, int* parent, int n)
{
	fprintf(fp_w, "%d, ", n);
	for (int y = 0; y < 30; y++)
	{
		if (parent[y] == n)
		{
			int found = 0;
			for (int q = 0; q < 30; q++)
			{
				if (parent[q] == y)
				{
					found = 1;
					break;
				}
			}
			if (found == 1)
			{
				equi_classes(fp_w, parent, y);
			}
			else
			{
				fprintf(fp_w, "%d, ", y);
			}
		}
	}
}