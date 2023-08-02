#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int edges1[20];
int edges2[20];
int total_edge[10];
int edge_count = 0;
int total_coast = 0;

typedef struct graphnode* graphpointer;
typedef struct graphnode {
	int vertex;
	int weight;
	graphpointer link;
} graphnode;

graphpointer goto_last(graphpointer head);
void print_node(graphpointer head);
graphpointer insert_node(graphpointer head, int vertex, int weight);
void krus_al(graphpointer graph[], int mat_size, int coast_list[][10]);
void prim_al(graphpointer graph[], int mat_size, int coast_list[][10]);
int isCycle();
int find(int parent[], int i);
void Union(int parent[], int x, int y);

int main()
{
	FILE* fp_r, * fp_w;
	fp_r = fopen("input.txt", "r");
	int mat_size = 0;
	fscanf(fp_r, "%d", &mat_size);
	graphpointer graph[10];
	int coast_list[10][10];
	for (int k = 0; k < 10; k++)
	{
		for (int t = 0; t < 10; t++)
		{
			coast_list[k][t] = -1;
		}
	}
	for (int i = 0; i < mat_size; i++)
	{
		graph[i] = (graphpointer)malloc(sizeof(graphnode));
		graph[i]->vertex = -1;
		graph[i]->weight = -1;
		graph[i]->link = NULL;
	}
	for (int j = 0; j < mat_size; j++)
	{
		for (int s = 0; s < mat_size; s++)
		{
			int boolnum = 0;
			fscanf(fp_r, "%d", &boolnum);
			if (boolnum != 0)
			{
				graph[j] = insert_node(graph[j], s, boolnum);
				coast_list[j][s] = boolnum;
			}
		}
	}
	fclose(fp_r);
	for (int q = 0; q < 20; q++)
	{
		edges1[q] = -1;
		edges2[q] = -1;
	}
	for (int q = 0; q < 10; q++)
	{
		total_edge[q] = -1;
	}
	int cp_coast_list[10][10];
	for (int h = 0; h < 10; h++)
	{
		for (int y = 0; y < 10; y++)
		{
			cp_coast_list[h][y] = coast_list[h][y];
		}
	}
	prim_al(graph, mat_size, cp_coast_list);
	fp_w = fopen("output.txt", "w");
	if (edge_count == mat_size - 1)
	{
		fprintf(fp_w, "Adjacency matrix representation MCST = {");
		for (int o = 0; o < edge_count; o++)
		{
			fprintf(fp_w, "(%d, %d), ", edges1[o], edges2[o]);
		}
		fprintf(fp_w, "}\nTotal cost = %d\n", total_coast);
		int tree_mat[20][20] = { 0 };
		for (int count = 0; count < edge_count; count++)
		{
			tree_mat[edges1[count]][edges2[count]] = coast_list[edges1[count]][edges2[count]];
			tree_mat[edges2[count]][edges1[count]] = coast_list[edges2[count]][edges1[count]];
		}
		for (int t = 0; t < mat_size; t++)
		{
			for (int y = 0; y < mat_size; y++)
			{
				fprintf(fp_w, "%d ", tree_mat[t][y]);
			}
			fprintf(fp_w, "\n");
		}
	}
	else
	{
		fprintf(fp_w, "MCST not found");
	}
	fclose(fp_w);
	for (int r = 0; r < mat_size; r++)
	{
		free(graph[r]);
	}

	return 0;
}

graphpointer goto_last(graphpointer head)
{
	graphpointer node = head;
	for (; node->link != NULL; node = node->link);
	return node;
}

void print_node(graphpointer head)
{
	graphpointer temp = head;
	temp = temp->link;
	for (; temp != NULL; temp = temp->link)
	{
		printf("%d, %d->", temp->vertex, temp->weight);
	}
}

graphpointer insert_node(graphpointer head, int vertex, int weight)
{
	graphpointer node = head;
	node = goto_last(node);
	graphpointer temp = (graphpointer)malloc(sizeof(graphnode));
	temp->vertex = vertex;
	temp->weight = weight;
	temp->link = NULL;
	node->link = temp;
	return head;
}

void krus_al(graphpointer graph[], int mat_size, int coast_list[][10])
{
	while (edge_count != mat_size - 1)
	{
		int least_edge = 10000;
		int row = 0;
		int col = 0;
		for (int i = 0; i < mat_size; i++)
		{
			for (int j = i + 1; j < mat_size; j++)
			{
				if (coast_list[i][j] < least_edge && coast_list[i][j] != -1)
				{
					least_edge = coast_list[i][j];
					row = i;
					col = j;
				}
			}
		}
		coast_list[row][col] = -1;
		coast_list[col][row] = -1;
		edges1[edge_count] = row;
		edges2[edge_count++] = col;
		if (edge_count == 1)
		{
			total_coast += least_edge;
		}
		else
		{
			if (!isCycle())
			{
				total_coast += least_edge;
			}
			else
			{
				edge_count--;
				edges1[edge_count] = -1;
				edges2[edge_count] = -1;
			}
		}
		int br = 0;
		int br_2 = 0;
		for (int k = 0; k < mat_size; k++)
		{
			for (int s = 0; s < mat_size; s++)
			{
				if (coast_list[k][s] == -1)
				{
					br = 1;
					br_2 = 1;
				}
				else if (coast_list[k][s] != -1)
				{
					br = 0;
					br_2 = 0;
					break;
				}
			}
			if (br_2 == 0)
			{
				break;
			}
		}
		if (br == 1)
		{
			break;
		}
	}
}

void prim_al(graphpointer graph[], int mat_size, int coast_list[][10])
{
	total_edge[0] = 0;
	while (edge_count != mat_size - 1)
	{
		if (edge_count == 0)
		{
			int v = -1;
			int least_edge = 10000;
			graphpointer node = graph[0];
			node = node->link;
			for (node; node != NULL; node = node->link)
			{
				if (node->weight < least_edge)
				{
					least_edge = node->weight;
					v = node->vertex;
				}
			}
			total_coast += least_edge;
			coast_list[0][v] = -1;
			coast_list[v][0] = -1;
			total_edge[1] = v;
			edges1[edge_count] = 0;
			edges2[edge_count++] = v;
		}
		else
		{
			int v = -1;
			int u = -1;
			int least_edge = 10000;
			for (int i = 0; i <= edge_count; i++)
			{
				int k = total_edge[i];
				int br = 0;
				graphpointer node = graph[k];
				node = node->link;
				for (node; node != NULL; node = node->link)
				{
					for (int s = 0; s <= edge_count; s++)
					{
						if (node->vertex == total_edge[s])
						{
							br = 1;
							break;
						}
					}
					if (node->weight < least_edge && coast_list[k][node->vertex] != -1 && br == 0)
					{
						least_edge = node->weight;
						v = node->vertex;
						u = k;
					}
					br = 0;
				}
			}
			if (least_edge == 10000)
			{
				break;
			}
			total_coast += least_edge;
			coast_list[u][v] = -1;
			coast_list[v][u] = -1;
			edges1[edge_count] = u;
			edges2[edge_count++] = v;
			total_edge[edge_count] = v;
		}
	}
}

int isCycle()
{
	int* parent = (int*)malloc(10 * sizeof(int));
	for (int j = 0; j < 10; j++)
	{
		parent[j] = -1;
	}
	for (int i = 0; i < edge_count; ++i)
	{
		int x = find(parent, edges1[i]);
		int y = find(parent, edges2[i]);
		if (x == y && (x != -1 && y != -1))
			return 1;
		Union(parent, x, y);
	}
	return 0;
}

int find(int parent[], int i)
{
	if (parent[i] == -1)
		return i;
	return find(parent, parent[i]);
}

void Union(int parent[], int x, int y)
{
	parent[y] = x;
}