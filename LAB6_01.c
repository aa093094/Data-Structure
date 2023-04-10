#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isp[] = { 0, 19, 12, 12, 13, 13, 13 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13 };
typedef enum { lparen, rparen, plus, minus, times, divide, mod, null, operand }precedence;
char stack[50];
int int_st[50] = { 0 };
char expr_1[50];
char expr_2[50];
int n = 0;
int top = -1;

precedence getToken(char symbol);

int main()
{
	FILE* fp_1,* fp_2;
	fp_1 = fopen("input.txt", "r");
	fp_2 = fopen("output1.txt", "w");
	memset(stack, '\0', sizeof(stack));
	memset(expr_1, '\0', sizeof(expr_1));
	memset(expr_2, '\0', sizeof(expr_1));
	precedence token;
	char symbol = '\0';
	char a = '\0';
	do
	{
		fscanf(fp_1, "%c", &symbol);
		if (symbol == ' ')
		{
			continue;
		}
		else
		{
			expr_1[n] = symbol;
			n++;
		}
	} while (a = fgetc(fp_1) != EOF);
	symbol = '\0';
	for(int i = 0; i < n; i++)
	{
		symbol = expr_1[i];
		token = getToken(symbol);
		if (token == operand)
		{
			fprintf(fp_2, "%c", symbol);
		}
		else if (token == rparen)
		{
			while (stack[top] != '(')
			{
				fprintf(fp_2, "%c", stack[top]);
				stack[top] = '\0';
				top--;
			}
			stack[top] = '\0';
			top--;
		}
		else if (token == null)
		{
			continue;
		}
		else
		{
			if (top == -1)
			{
				top++;
				stack[top] = symbol;
			}
			else
			{
				precedence tp_tk = getToken(stack[top]);
				while (isp[tp_tk] >= icp[token])
				{
					fprintf(fp_2, "%c", stack[top]);
					stack[top] = '\0';
					top--;
					tp_tk = getToken(stack[top]);
				}
				top++;
				stack[top] = symbol;
			}
		}
	}

	while (top != -1)
	{
		fprintf(fp_2, "%c", stack[top]);
		stack[top] = '\0';
		top--;
	}
	fprintf(fp_2, "\n");
	fclose(fp_1);
	fclose(fp_2);
	FILE* fp_3,* fp_4;
	fp_3 = fopen("output1.txt", "r");
	char str[50] = "";
	fscanf(fp_3, "%s", str);
	strcpy(expr_2, str);
	int len = strlen(expr_2);
	int op1, op2;
	for (int j = 0; j < len; j++)
	{
		symbol = expr_2[j];
		token = getToken(symbol);
		if (token == operand)
		{
			int_st[++top] = symbol - '0';
		}
		else
		{
			op2 = int_st[top];
			int_st[top] = 0;
			top--;
			op1 = int_st[top];
			stack[top] = 0;
			top--;
			switch (token)
			{
			case plus:int_st[++top] = op1 + op2;
				break;
			case minus:int_st[++top] = op1 - op2;
				break;
			case times:int_st[++top] = op1 * op2;
				break;
			case divide:int_st[++top] = op1 / op2;
				break;
			case mod:int_st[++top] = op1 % op2;
			}
		}
	}
	fclose(fp_3);
	fp_4 = fopen("output2.txt", "w");
	fprintf(fp_4, "%d", int_st[top]);
	fclose(fp_4);

	return 0;
}

precedence getToken(char symbol)
{
	switch (symbol)
	{
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '/':return divide;
	case '*':return times;
	case '%':return mod;
	case '\0':return null;
	default:return operand;
	}
}