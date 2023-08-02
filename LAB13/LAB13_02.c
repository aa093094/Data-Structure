#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 30

#define FALSE "false"
#define TRUE "true"
#define OR "or"
#define AND "and"
#define NOT "not"
#define EMPTY "empty"
#define VARIABLE "x"

#define N_NONE -1;
#define N_FALSE 0
#define N_TRUE 1
#define N_OR 2
#define N_AND 3
#define N_NOT 4
#define N_EMPTY 5
#define N_VARIABLE 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node
{
	struct node* left;
	int data;
	int value;
	struct node* right;
} Node;

Node* convert_to_node(int value, int* var_value)
{
	Node* result = (Node*)malloc(sizeof(Node));
	result->data = value > 6 ? 6 : value;
	result->value = value > 6 ? var_value[value - 6 - 1] : N_NONE;
	result->left = NULL;
	result->right = NULL;
}

Node* copytree(int original, int* data, int* value)
{
	Node* temp;
	if (original < 64 && data[original] != EMPTY)
	{
		temp = (Node*)malloc(sizeof(Node));
		temp->left = copytree(original * 2, data, value);
		temp->right = copytree(original * 2 + 1, data, value);
		temp->data = data[original];
		temp->value = value[original];
		return temp;
	}
	return NULL;
}

void postOrderEval(Node* node)
{
	if (node)
	{
		postOrderEval(node->left);
		postOrderEval(node->right);
		switch (node->data)
		{
		case 4: node->value = !node->right->value;
			break;
		case 3 : node->value = node->right->value && node->left->value;
			break;
		case 2 : node->value = node->right->value || node->left->value;
			break;
		case 1: node->value = 1;
			break;
		case 0: node->value = 0;
		}
	}
}

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");

	char** strs = (char**)malloc(sizeof(char*));
	int strs_idx = 0;
	while (feof(fp) == 0)
	{
		char str[MAX_LEN];
		fscanf(fp, "%s\r\n", str);
		strs[strs_idx] = (char*)calloc(MAX_LEN, 1);
		strcpy(strs[strs_idx++], str);
	}

	fclose(fp);

	int n = atoi(strs[0]);

	int var_values[10] = { 0 };
	int vi = 0;
	char** strp = strs + 1;

	while (vi < n)
	{
		if (strstr(*strp, TRUE) != NULL)
		{
			var_values[vi++] = N_TRUE;
			strp++;
		}
		else
		{
			var_values[vi++] = N_FALSE;
			strp++;
		}
	}
	

	int node_values[128];

	for (int idx = 0; idx < strs_idx - 1 - n; strp++, idx++)
	{
		if (strstr(*strp, OR) != NULL)
			node_values[idx] = N_OR;
		else if (strstr(*strp, AND) != NULL)
			node_values[idx] = N_AND;
		else if (strstr(*strp, NOT) != NULL)
			node_values[idx] = N_NOT;
		else if (strstr(*strp, EMPTY) != NULL)
			node_values[idx] = N_EMPTY;
		else if (strstr(*strp, VARIABLE) != NULL)
			node_values[idx] = N_VARIABLE + atoi(*strp + 1);
	}

	Node* nodes[128];
	for (int idx = 1; idx < strs_idx - n; idx++)
	{
		nodes[idx] = convert_to_node(node_values[idx-1], var_values);
	}
	int datas[128];
	int values[128];
	for (int i = 1; i < strs_idx - n; i++)
	{
		datas[i] = nodes[i]->data;
		values[i] = nodes[i]->value;
	}
	Node* tree = copytree(1, datas, values);
	postOrderEval(tree);
	printf("%d", tree->value);

	for (int i = 0; i < strs_idx; i++)
		free(strs[i]);

	return 0;
}