#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SW 5
#define W 6
#define NW 7

typedef struct {
	int row;
	int col;
	int dir;
}element;
int top = 0;

void find_path(FILE* fp_2, int** maze, int mark[22][22], element stack[400], int top, int exitrow, int exitcol);
void pop(element stack[400], int top);
void add(element stack[400], int top, int nextrow, int nextcol);

int main()
{
	FILE* fp_1, * fp_2;
	int** maze;
	fp_1 = fopen("input.txt", "r");
	int row = 0, col = 0;
	fscanf(fp_1, "%d %d", &row, &col);
	maze = (int**)malloc((row + 2) * sizeof(int*));
	for (int i = 0; i < row + 2; i++)
	{
		maze[i] = (int*)malloc((col + 2) * sizeof(int));
	}
	for (int j = 0; j < col + 2; j++)
	{
		maze[0][j] = 1;
		maze[row + 1][j] = 1;
	}
	for (int k = 0; k < row + 2;k++)
	{
		maze[k][0] = 1;
		maze[k][col + 1] = 1;
	}
	for (int p = 1; p < row + 1; p++)
	{
		for (int s = 1; s < col + 1;s++)
		{
			fscanf(fp_1, "%d", &maze[p][s]);
		}
	}
	int mark[22][22] = { 0 };
	mark[1][1] = 1;
	element stack[400] = { 0 };
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = N;
	fp_2 = fopen("output.txt", "w");
	find_path(fp_2, maze, mark, stack, top, row, col);
	free(maze);
	fclose(fp_1);
	fclose(fp_2);

	return 0;
}

void find_path(FILE* fp_2, int** maze, int mark[22][22], element stack[400], int top, int exitrow, int exitcol)
{
	int find = 0;
	while (stack[0].row != 0)
	{
		while (stack[top].dir <= 7)
		{
			if (top == -1)
			{
				break;
			}
			if (stack[top].row == exitrow && stack[top].col == exitcol)
			{
				find = 1;
				break;
			}
			int row = stack[top].row; 
			int col = stack[top].col;
			int nextrow = 0, nextcol = 0;
			switch (stack[top].dir)
			{
			case N:
				if (maze[row - 1][col] == 0 && mark[row - 1][col] == 0)
				{
					nextrow = row - 1;
					nextcol = col;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case NE:
				if (maze[row - 1][col + 1] == 0 && mark[row - 1][col + 1] == 0)
				{
					nextrow = row - 1;
					nextcol = col + 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case E:
				if (maze[row][col + 1] == 0 && mark[row][col + 1] == 0)
				{
					nextrow = row;
					nextcol = col + 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case SE:
				if (maze[row + 1][col + 1] == 0 && mark[row + 1][col + 1] == 0)
				{
					nextrow = row + 1;
					nextcol = col + 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case S:
				if (maze[row + 1][col] == 0 && mark[row + 1][col] == 0)
				{
					nextrow = row + 1;
					nextcol = col;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case SW:
				if (maze[row + 1][col - 1] == 0 && mark[row + 1][col - 1] == 0)
				{
					nextrow = row + 1;
					nextcol = col - 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case W:
				if (maze[row][col - 1] == 0 && mark[row][col - 1] == 0)
				{
					nextrow = row;
					nextcol = col - 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			case NW:
				if (maze[row - 1][col - 1] == 0 && mark[row - 1][col - 1] == 0)
				{
					nextrow = row - 1;
					nextcol = col - 1;
					mark[nextrow][nextcol] = 1;
					top++;
					add(stack, top, nextrow, nextcol);
					break;
				}
				stack[top].dir++;
			default: 
			{
				pop(stack, top);
				top--;
			}
			}
		}
		if (find == 1)
		{
			break;
		}
		if (top == -1)
		{
			find = 0;
			break;
		}
	}
	if (find == 1)
	{
		fprintf(fp_2, "%s", "success\npath는 ");
		for (int i = 0; i <= top; i++)
		{
			fprintf(fp_2, "(%d, %d) ", stack[i].row, stack[i].col);
		}
		fprintf(fp_2, "\n사용한 스택의 크기 / 스택의 최대 크기 = %d / %d", top + 1, exitrow * exitcol);
	}
	else
	{
		fprintf(fp_2, "%s", "fail\n");
	}
}

void pop(element stack[400], int top)
{
	stack[top].row = 0;
	stack[top].col = 0;
	stack[top].dir = 0;
}

void add(element stack[400], int top, int nextrow, int nextcol)
{
	stack[top].row = nextrow;
	stack[top].col = nextcol;
	stack[top].dir = N;
}