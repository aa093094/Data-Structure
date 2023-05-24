#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

void infixToPostfix(char* infix, char* postfix) {
    int i, j, top = -1;
    char stack[MAX_SIZE], ch;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--; // remove the '(' from the stack
        }
        else if (isOperator(ch)) {
            while (top != -1 && precedence(ch) <= precedence(stack[top])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = ch;
        }
        else if (ch == ' ')
        {

        }
        else {
            printf("Error: Invalid character '%c'\n", ch);
            exit(1);
        }
    }

    while (top != -1) {
        if (stack[top] == '(') {
            printf("Error: Unmatched parentheses\n");
            exit(1);
        }
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
}

int main()
{
    FILE* fp, * fp_w, * fp_w2;
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    fp = fopen("input.txt", "r");
    fp_w = fopen("output1.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    fgets(infix, MAX_SIZE, fp);
    infixToPostfix(infix, postfix);

    fprintf(fp_w, "%s", postfix);
    fp_w2 = fopen("output2.txt", "w");
    char symbol;
    int len = strlen(postfix);
    int int_st[MAX_SIZE] = { 0 };
    int top = -1;
    int op1, op2;
    for (int j = 0; j < len; j++)
    {
        symbol = postfix[j];
        if (isalnum(symbol)) {
            int_st[++top] = symbol - '0';
        }
        else
        {
            
                op2 = int_st[top];
                int_st[top] = 0;
                top--;
                op1 = int_st[top];
                int_st[top] = 0;
                top--;
                switch (symbol)
                {
                case '+':int_st[++top] = op1 + op2;
                    break;
                case '-':int_st[++top] = op1 - op2;
                    break;
                case '*':int_st[++top] = op1 * op2;
                    break;
                case '/':int_st[++top] = op1 / op2;
                    break;
                case '%':int_st[++top] = op1 % op2;
                }
            
        }
    }
    fprintf(fp_w2, "%d", int_st[top]);

    fclose(fp);
    fclose(fp_w);
    fclose(fp_w2);

    return 0;
}
