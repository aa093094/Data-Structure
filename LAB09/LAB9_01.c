#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
	int data;
	struct ListNode* link;
} ListNode;

int main()
{
	FILE* fp_r, * fp_w;
	int size = 0;
	fp_r = fopen("input.txt", "r");
	fscanf(fp_r, "%d", &size);
	short int out[50];
	ListNode* seq[50];
	int num_list[50];
	memset(num_list, -1, 50);
	int e_class[50][50];
	memset(e_class, -1, (50 * 50));
	for (int i = 0; i < 50; i++)
	{
		out[i] = 1;
		seq[i] = NULL;
	}
	int p = 0, q = 0, k = 0;
	ListNode* x,* y,* top;
	char equal;
	for (int j = 0; j < size; j++)
	{
		fscanf(fp_r, "%d %c %d", &p, &equal, &q);
		num_list[k++] = p;
		num_list[k++] = q;
		x = (ListNode*)malloc(sizeof(ListNode));
		x->data = q;
		x->link = seq[p];
		seq[p] = x;
		x = (ListNode*)malloc(sizeof(ListNode));
		x->data = p;
		x->link = seq[q];
		seq[q] = x;
	}
	fclose(fp_r);
	int max_num = 0;
	for (int s = 0; s < k; s++)
	{
		if (max_num < num_list[s])
		{
			max_num = num_list[s];
		}
	}
	for (int s = 0; s <= max_num; s++)
	{
		int count = 0;
		for (int u = 0; num_list[u] != -1; u++)
		{
			if (s == num_list[u])
			{
				count++;
				break;
			}
		}
		if (count == 0)
		{
			out[s] = 0;
		}
	}
	int row = 0;
	for (int r = 0; r <= max_num; r++)
	{
		int col = 0;
		if (out[r])
		{
			e_class[row][col++] = r;
			out[r] = 0;
			x = seq[r];
			top = NULL;
			for (;;)
			{
				while (x)
				{
					p = x->data;
					if (out[p])
					{
						e_class[row][col++] = p;
						out[p] = 0;
						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else
					{
						x = x->link;
					}
				}
				if (!top)break;
				x = seq[top->data];
				top = top->link;
			}
			row++;
		}
	}
	fp_w = fopen("output.txt", "w");
	fprintf(fp_w, "%d\n", row);
	for (int n = 0; n < row; n++)
	{
		fprintf(fp_w, "{");
		int u = 0;
		while (1)
		{
			fprintf(fp_w, "%d", e_class[n][u]);
			u++;
			if (e_class[n][u] == -1)
			{
				if (n == row - 1)
				{
					fprintf(fp_w, "}");
					break;
				}
				else
				{
					fprintf(fp_w, "}, ");
					break;
				}
			}
			else
			{
				fprintf(fp_w, ", ");
			}
		}
	}
	fclose(fp_w);

	return 0;
}