#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
short int visited[20] = { 0 };
int edges1[40];
int edges2[40];
int edge_count = 0;

typedef struct graphnode* graphpointer;
typedef struct graphnode {
	int vertex;
	graphpointer link;
} graphnode;

typedef struct queue* queuepointer;
typedef struct queue {
	int vertex;
	queuepointer link;
} queue;
queuepointer front, rear;

graphpointer goto_last(graphpointer node);
void print_node(graphpointer node);
graphpointer insert_node(graphpointer node, int vertex);
void dfs(int v, graphpointer graph[]);
void bfs(int v, graphpointer graph[]);
void connected(graphpointer graph[], int size, int num);
void addq(int a);
int deleteq();

int main()
{
	FILE* fp_r, * fp_w;
	fp_r = fopen("input.txt", "r");
	int mat_size = 0;
	fscanf(fp_r, "%d", &mat_size);
	graphpointer graph[20];
	for (int i = 0; i < mat_size; i++)
	{
		graph[i] = (graphpointer)malloc(sizeof(graphnode));
		graph[i]->vertex = -1;
		graph[i]->link = NULL;
	}
	for (int j = 0; j < mat_size; j++)
	{
		for (int s = 0; s < mat_size; s++)
		{
			int boolnum = 0;
			fscanf(fp_r, "%d", &boolnum);
			if (boolnum == 1)
			{
				graph[j] = insert_node(graph[j], s);
			}
		}
	}
	fclose(fp_r);
	for (int q = 0; q < 40; q++)
	{
		edges1[q] = -1;
		edges2[q] = -1;
	}
	fp_w = fopen("output.txt", "w");
	bfs(0, graph);
	int find = TRUE;
	for (int u = 0; u < mat_size; u++)
	{
		if (!visited[u])
		{
			find = FALSE;
			break;
		}
	}
	if (find == TRUE)
	{
		fprintf(fp_w, "adjacency matrix (%d by %d), Tree Edges = { ", mat_size, mat_size);
		for (int o = 0; o < edge_count; o++)
		{
			fprintf(fp_w, "(%d, %d), ", edges1[o], edges2[o]);
		}
		fprintf(fp_w, "}\n");
		int tree_mat[20][20] = { 0 };
		for (int count = 0; count < edge_count; count++)
		{
			tree_mat[edges1[count]][edges2[count]] = 1;
			tree_mat[edges2[count]][edges1[count]] = 1;
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
		fprintf(fp_w, "Can't find spanning tree, all connected component(-1 means not connected to any node) = {{");
		int o = 0;
		for (o; o < edge_count; o++)
		{
			fprintf(fp_w, "(%d, %d), ", edges1[o], edges2[o]);
		}
		fprintf(fp_w, "}, ");
		for (int p = 0; p < mat_size; p++)
		{
			if (!visited[p])
			{
				fprintf(fp_w, "{");
				connected(graph, mat_size, p);
				for (o; o < edge_count; o++)
				{
					fprintf(fp_w, "(%d, %d), ", edges1[o], edges2[o]);
				}
				fprintf(fp_w, "}, ");
			}
		}
		fprintf(fp_w, "}");
	}
	fclose(fp_w);
	for (int r = 0; r < mat_size; r++)
	{
		free(graph[r]);
	}
	free(front);

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
		printf("%d->", temp->vertex);
	}
}

graphpointer insert_node(graphpointer head, int vertex)
{
	graphpointer node = head;
	node = goto_last(node);
	graphpointer temp = (graphpointer)malloc(sizeof(graphnode));
	temp->vertex = vertex;
	temp->link = NULL;
	node->link = temp;
	return head;
}

void dfs(int v, graphpointer graph[])
{
	graphpointer w;
	visited[v] = TRUE;
	for (w = graph[v]; w; w = w->link)
	{
		if (w->vertex == -1)
		{
			w = w->link;
		}
		if (!visited[w->vertex])
		{
			edges1[edge_count] = v;
			edges2[edge_count++] = w->vertex;
			dfs(w->vertex, graph);
		}
	}
}

void bfs(int v, graphpointer graph[])
{
	graphpointer w;
	front = rear = NULL;
	visited[v] = TRUE;
	addq(v);
	int br = 0;
	while (front)
	{
		v = deleteq();
		for (w = graph[v]; w; w = w->link)
		{
			if (w->vertex == -1 && w->link)
			{
				w = w->link;
			}
			else if (w->vertex == -1 && !w->link)
			{
				edges1[edge_count] = v;
				edges2[edge_count++] = -1;
				br = 1;
			}
			if (br == 0)
			{
				if (!visited[w->vertex])
				{
					edges1[edge_count] = v;
					edges2[edge_count++] = w->vertex;
					addq(w->vertex);
					visited[w->vertex] = TRUE;
				}
			}
		}
	}
}

void connected(graphpointer graph[], int size, int num)
{
	if (!visited[num])
	{
		bfs(num, graph);
	}
}

void addq(int a)
{
	queuepointer temp = (queuepointer)malloc(sizeof(queue));
	temp->vertex = a;
	temp->link = NULL;
	if (front)
	{
		rear->link = temp;
	}
	else
	{
		front = temp;
	}
	rear = temp;
}

int deleteq()
{
	queuepointer temp = front;
	int vertex;
	vertex = temp->vertex;
	front = temp->link;
	free(temp);
	return vertex;
}