#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int fin_root;

typedef struct Op_tree {
	int start;
	int end;
	int weight;
	int cost;
	int root;
} Op_tree;

typedef struct from_index {
	int first_row;
	int first_col;
	int last_row;
	int last_col;
} from_index;

void recur_left(Op_tree** tree, from_index** indexes, int first_row, int first_col, int last_row, int last_col, int roots[100], int i);
void recur_right(Op_tree** tree, from_index** indexes, int first_row, int first_col, int last_row, int last_col, int roots[100], int i);

int main()
{
	FILE* fp_r, * fp_w;
	fp_r = fopen("input.txt", "r");
	int size = 0, m = 0;
	fscanf(fp_r, "%d %d", &size, &m);
	int* nums = (int*)malloc((size + 1) * sizeof(int));
	int* ps = (int*)malloc((size + 1) * sizeof(int));
	int* qs = (int*)malloc((size + 1) * sizeof(int));
	nums[0] = 0;
	for (int i = 1; i < size + 1; i++)
	{
		int num = 0;
		fscanf(fp_r, "%d", &num);
		nums[i] = num;
	}
	ps[0] = 0;
	for (int i = 1; i < size + 1; i++)
	{
		int p = 0;
		fscanf(fp_r, "%d", &p);
		ps[i] = p;
	}
	for (int i = 0; i < size + 1; i++)
	{
		int q = 0;
		fscanf(fp_r, "%d", &q);
		qs[i] = q;
	}
	fclose(fp_r);
	int total = 0;
	for (int j = size + 1; j >= 1; j--)
	{
		total += j;
	}
	Op_tree** tree = (Op_tree**)malloc((size + 1) * sizeof(Op_tree*));
	from_index** indexes = (from_index**)malloc((size + 1) * sizeof(from_index*));
	for (int j = 0; j < size + 1; j++)
	{
		tree[j] = (Op_tree*)malloc((size + 1) * sizeof(Op_tree));
		indexes[j] = (from_index*)malloc((size + 1) * sizeof(from_index));
	}
	for (int j = 0; j < size + 1; j++)
	{
		tree[0][j].start = j;
		tree[0][j].end = j;
		tree[0][j].weight = qs[j];
		tree[0][j].cost = 0;
		tree[0][j].root = 0;
		indexes[0][j].first_row = -1;
		indexes[0][j].first_col = -1;
		indexes[0][j].last_row = -1;
		indexes[0][j].last_col = -1;
	}
	int first_row = 0;
	int first_col = 0;
	int last_row = 0;
	int last_col = 0;
	for (int j = 1; j < size + 1; j++)
	{
		int k = j;
		for (int i = 0; i < size + 1 - j; i++)
		{
			tree[j][i].start = i;
			tree[j][i].end = k;
			int temp_cost = 100;
			int temp_weight = 0;
			int temp_root = 0;
			for (int s = 0; s < j; s++)
			{
				int weight = tree[s][i].weight + tree[j - s - 1][i + s + 1].weight + ps[tree[j - s - 1][i + s + 1].start];
				int cost = weight + tree[s][i].cost + tree[j - s - 1][i + s + 1].cost;
				if (cost < temp_cost)
				{
					temp_cost = cost;
					temp_weight = weight;
					temp_root = tree[j - s - 1][i + s + 1].start;
					first_row = s;
					first_col = i;
					last_row = j - s - 1;
					last_col = i + s + 1;
				}
			}
			tree[j][i].cost = temp_cost;
			tree[j][i].weight = temp_weight;
			tree[j][i].root = temp_root;
			indexes[j][i].first_row = first_row;
			indexes[j][i].first_col = first_col;
			indexes[j][i].last_row = last_row;
			indexes[j][i].last_col = last_col;
			k++;
		}
	}
	Op_tree fin_tree = tree[size][0];
	int fin_cost = fin_tree.cost / m;
	fin_root = fin_tree.root;
	int op_tree[260] = { 0 };
	op_tree[1] = fin_root;
	int left_nums = tree[indexes[size][0].first_row][indexes[size][0].first_col].end;
	int right_nums = tree[indexes[size][0].last_row][indexes[size][0].last_col].end - tree[indexes[size][0].last_row][indexes[size][0].last_col].start;
	int left_roots[100] = { 0 };
	int right_roots[100] = { 0 };
	first_row = indexes[size][0].first_row;
	first_col = indexes[size][0].first_col;
	last_row = indexes[size][0].last_row;
	last_col = indexes[size][0].last_col;
	recur_left(tree, indexes, first_row, first_col, last_row, last_col, left_roots, 0);
	recur_right(tree, indexes, first_row, first_col, last_row, last_col, right_roots, 0);
	fp_w = fopen("output.txt", "w");
	fprintf(fp_w, "Optimal Binary Search Tree의 총 비용은 %d이며 (%d/%d = %d)\n그 토폴로지는 다음과 같습니다.\n", fin_cost, fin_tree.cost, m, fin_cost);
	int index = 1;
	for (int u = 0; u < left_nums; u++)
	{
		if (left_roots[u] < op_tree[index])
		{
			index *= 2;
			op_tree[index] = left_roots[u];
		}
		else
		{
			index = index * 2 + 1;
			op_tree[index] = left_roots[u];
		}
	}
	index = 1;
	for (int y = 0; y < right_nums; y++)
	{
		if (right_roots[y] < op_tree[index])
		{
			index *= 2;
			op_tree[index] = right_roots[y];
		}
		else
		{
			index = index * 2 + 1;
			op_tree[index] = right_roots[y];
		}
	}
	int count = 0;
	for (int o = 1; o < 260; o++)
	{
		if (op_tree[o] != 0)
		{
			fprintf(fp_w, "\nComplete BT의 %d번 노드 자리에 원소 %d가 위치합니다.", o, nums[op_tree[o]]);
			count++;
		}
		if (size == count)
		{
			break;
		}
	}
	fclose(fp_w);
	for (int i = 0; i < size + 1; i++)
	{
		free(tree[i]);
		free(indexes[i]);
	}
	free(nums);
	free(ps);
	free(qs);

	return 0;
}

void recur_left(Op_tree** tree, from_index** indexes, int first_row, int first_col, int last_row, int last_col, int roots[100], int i)
{
	if (first_row != 0)
	{
		if (tree[first_row][first_col].root != fin_root)
		{
			roots[i++] = tree[first_row][first_col].root;
		}
		int l_row = indexes[first_row][first_col].first_row;
		int l_col = indexes[first_row][first_col].first_col;
		recur_left(tree, indexes, l_row, l_col, last_row, last_col, roots, i);
		int r_row = indexes[first_row][first_col].last_row;
		int r_col = indexes[first_row][first_col].last_col;
		if (last_row != 0)
		{
			recur_right(tree, indexes, l_row, l_col, r_row, r_col, roots, i);
		}
	}
}

void recur_right(Op_tree** tree, from_index** indexes, int first_row, int first_col, int last_row, int last_col, int roots[100], int i)
{
	if (last_row != 0)
	{
		if (tree[last_row][last_col].root != fin_root)
		{
			roots[i++] = tree[last_row][last_col].root;
		}
		int r_row = indexes[last_row][last_col].last_row;
		int r_col = indexes[last_row][last_col].last_col;
		recur_right(tree, indexes, first_row, first_col, r_row, r_col, roots, i);
		int l_row = indexes[last_row][last_col].first_row;
		int l_col = indexes[last_row][last_col].first_col;
		if (first_row != 0)
		{
			recur_left(tree, indexes, l_row, l_col, r_row, r_col, roots, i);
		}
	}
}