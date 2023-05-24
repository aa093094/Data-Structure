#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct stack
{
    char data;
    struct stack* link;
} stack;

typedef struct int_st
{
    int data;
    struct int_st* link;
} int_st;
int i = -1;
int p = -1;

int precedence(char op);
int isOperator(char ch);
void infixToPostfix(char* infix, char* postfix);
stack* push(stack* top, char item);
char pop(stack* top);
char call_top(stack* top);
int_st* push_i(int_st* top, char item);
int pop_i(int_st* top);
int call_top_i(int_st* top);


int main()
{
    FILE* fp, * fp_w, * fp_w2;
    char infix[100], postfix[50];

    fp = fopen("input.txt", "r");
    fp_w = fopen("output1.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    fgets(infix, 100, fp);
    infixToPostfix(infix, postfix);

    fprintf(fp_w, "%s", postfix);
    fp_w2 = fopen("output2.txt", "w");
    char symbol;
    int len = strlen(postfix);
    int_st* top = (int_st*)malloc(sizeof(int_st));
    int op1, op2;
    for (int j = 0; j < len; j++)
    {
        symbol = postfix[j];
        if (isalnum(symbol)) {
            top = push_i(top, symbol - '0');
        }
        else
        {
            if (symbol == '&' || symbol == '|' || symbol == '!' || symbol == '=')
            {
                op2 = pop_i(top);
                op1 = pop_i(top);
                j++;
                switch (symbol)
                {
                case '&':top = push_i(top, op1 && op2);
                    break;
                case '|':top = push_i(top, op1 || op2);
                    break;
                case '!':top = push_i(top, op1 != op2);
                    break;
                case '=':top = push_i(top, op1 == op2);
                }
            }
            else if (symbol == '>' || symbol == '<')
            {
                int tp_j = j;
                tp_j++;
                if (postfix[tp_j] == '=')
                {
                    op2 = pop_i(top);
                    op1 = pop_i(top);
                    j++;
                    switch (symbol)
                    {
                    case '>':push_i(top, op1 >= op2);
                        break;
                    case '<':push_i(top, op1 <= op2);
                    }
                }
                else
                {
                    op2 = pop_i(top);
                    op1 = pop_i(top);
                    switch (symbol)
                    {
                    case '>':push_i(top, op1 > op2);
                        break;
                    case '<':push_i(top, op1 < op2);
                    }
                }
            }
            else
            {
                op2 = pop_i(top);
                op1 = pop_i(top);
                switch (symbol)
                {
                case '+':push_i(top, op1 + op2);
                    break;
                case '-':push_i(top, op1 - op2);
                    break;
                case '*':push_i(top, op1 * op2);
                    break;
                case '/':push_i(top, op1 / op2);
                    break;
                case '%':push_i(top, op1 % op2);
                }
            }
        }
    }
    int result = pop_i(top);
    fprintf(fp_w2, "%d", result);
    free(top);
    fclose(fp_w2);
    

    fclose(fp);
    fclose(fp_w);

    return 0;
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '&' || op == '|')
        return 3;
    if (op == '>' || op == '<' || op == '=' || op == '!')
        return 4;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
        ch == '&' || ch == '|' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '!';
}

void infixToPostfix(char* infix, char* postfix) {
    int k, s;
    char ch;
    stack* top = (stack*)malloc(sizeof(stack));

    for (k = 0, s = 0; infix[k] != '\0'; k++) {
        ch = infix[k];

        if (isalnum(ch)) {
            postfix[s++] = ch;
        }
        else if (ch == '(') {
            top = push(top, ch);
        }
        else if (ch == ')') {
            char c = call_top(top);
            while (i != -1 && c != '(') {
                char a = call_top(top);
                if ( a == '&' || a == '|')
                {
                    postfix[s++] = pop(top);
                    postfix[s++] = pop(top);
                }
                else if (a == '=')
                {
                    i--;
                    char b = call_top(top);
                    if (b == '!' || b == '=' || b == '>' || b == '<')
                    {
                        i++;
                        char op_1, op_2;
                        op_1 = pop(top);
                        op_2 = pop(top);
                        postfix[s++] = op_2;
                        postfix[s++] = op_1;
                    }
                    else
                    {
                        i++;
                        postfix[s++] = pop(top);
                    }
                }
                else
                {
                    postfix[s++] = pop(top);
                }
                c = call_top(top);
            }
            i--; // remove the '(' from the stack
        }
        else if (isOperator(ch)) {
            char c = call_top(top);
            while (i != -1 && precedence(ch) <= precedence(c))
            {
                char a = call_top(top);
                if (a == '&' || a == '|')
                {
                    postfix[s++] = pop(top);
                    postfix[s++] = pop(top);
                }
                else if (a == '=')
                {
                    i--;
                    char b = call_top(top);
                    if (b == '!' || b == '=' || b == '>' || b == '<')
                    {
                        i++;
                        char op_1, op_2;
                        op_1 = pop(top);
                        op_2 = pop(top);
                        postfix[s++] = op_2;
                        postfix[s++] = op_1;
                    }
                    else
                    {
                        i++;
                        postfix[s++] = pop(top);
                    }
                }
                else
                {
                    postfix[s++] = pop(top);
                }
                c = call_top(top);
            }
            if (ch == '&' || ch == '|' || ch == '=' || ch == '!')
            {
                top = push(top, ch);
                k++;
                ch = infix[k];
                top = push(top, ch);
            }
            else if (ch == '>' || ch == '<')
            {
                int tp_i = k;
                tp_i++;
                if (infix[tp_i] == '=')
                {
                    top = push(top, ch);
                    k++;
                    ch = infix[k];
                    top = push(top, ch);
                }
                else
                {
                    top = push(top, ch);
                }
            }
            else
            {
                top = push(top, ch);
            }
        }
        else if (ch == ' ')
        {

        }
        else {
            printf("Error: Invalid character '%c'\n", ch);
            exit(1);
        }
    }

    while (i != -1) {
        char a = call_top(top);
        if (a == '(') {
            printf("Error: Unmatched parentheses\n");
            exit(1);
        }
        if (a == '&' || a == '|')
        {
            postfix[s++] = pop(top);
            postfix[s++] = pop(top);
        }
        else if (a == '=')
        {
            i--;
            char b = call_top(top);
            if (b == '!' || b == '=' || b == '>' || b == '<')
            {
                i++;
                char op_1, op_2;
                op_1 = pop(top);
                op_2 = pop(top);
                postfix[s++] = op_2;
                postfix[s++] = op_1;
            }
            else
            {
                i++;
                postfix[s++] = pop(top);
            }
        }
        else
        {
            postfix[s++] = pop(top);
        }
    }

    postfix[s] = '\0';
    free(top);
}

stack* push(stack* top, char item)
{
    stack* temp = (stack*)malloc(sizeof(stack));
    stack* last = top;
    for (int r = -1; r < i; r++)
    {
        last = last->link;
    }
    temp->data = item;
    temp->link = last->link;
    last->link = temp;
    i++;
    return top;
}

char pop(stack* top)
{
    stack* last = top;
    for (int k = 0; k <= i; k++)
    {
        last = last->link;
    }
    char item;
    item = last->data;
    free(last);
    i--;
    return item;
}

char call_top(stack* top)
{
    stack* last = top;
    for (int k = 0; k <= i; k++)
    {
        last = last->link;
    }
    char item;
    item = last->data;
    return item;
}

int_st* push_i(int_st* top, char item)
{
    int_st* temp = (int_st*)malloc(sizeof(int_st));
    int_st* last = top;
    for (int r = -1; r < p; r++)
    {
        last = last->link;
    }
    temp->data = item;
    temp->link = last->link;
    last->link = temp;
    p++;
    return top;
}

int pop_i(int_st* top)
{
    int_st* last = top;
    for (int k = 0; k <= p; k++)
    {
        last = last->link;
    }
    int item;
    item = last->data;
    free(last);
    p--;
    return item;
}

int call_top_i(int_st* top)
{
    int_st* last = top;
    for (int k = 0; k <= p; k++)
    {
        last = last->link;
    }
    int item;
    item = last->data;
    return item;
}