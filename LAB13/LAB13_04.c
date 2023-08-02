#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftchild;
	char data;
	threadedPointer rightchild;
	short int rightThread;
} threadedTree;

void inorder(threadedPointer head);
threadedPointer insertRight(threadedPointer head, threadedPointer parent, int data);
threadedPointer insertLeft(threadedPointer head, threadedPointer parent, int data);
void tinorder(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
threadedPointer in_succ(threadedPointer ptr);
threadedPointer t_inorder(threadedPointer root, int value);
void p_inorder(threadedPointer root);
threadedPointer del_node(threadedPointer root, threadedPointer head, threadedPointer par, threadedPointer ptr);
threadedPointer par_inorder(threadedPointer root, threadedPointer child);
threadedPointer case_a(threadedPointer root, threadedPointer par, threadedPointer ptr);
threadedPointer case_b(threadedPointer root, threadedPointer par, threadedPointer ptr);
threadedPointer case_c(threadedPointer root, threadedPointer head, threadedPointer par, threadedPointer ptr);
threadedPointer in_pred(threadedPointer ptr);

int main()
{
	FILE* fp_r;
	fp_r = fopen("input.txt", "r");
	threadedPointer head = (threadedPointer)malloc(sizeof(threadedTree));
	threadedPointer root = (threadedPointer)malloc(sizeof(threadedTree));
	root->leftchild = head;
	root->leftThread = 0;
	root->rightchild = root;
	root->rightThread = 0;
	head->leftchild = root;
	head->rightchild = root;
	head->leftThread = 1;
	head->rightThread = 1;
	char* arr_2;
	int size = 0;
	fscanf(fp_r, "%d", &size);
	int tree_1[50];
	for (int j = 0; j < 50; j++)
	{
		tree_1[j] = 0;
	}
	int i = 1;
	int count = 0;
	while (count < size)
	{
		int num = 0;
		fscanf(fp_r, "%d", &num);
		if (num == 0)
		{
			i++;
		}
		else
		{
			tree_1[i++] = num;
			count++;
		}
	}
	head->data = tree_1[1];
	int ch_size = size;
	arr_2 = (char*)malloc(ch_size * sizeof(char));
	for (int t = 0; t < ch_size; t++)
	{
		arr_2[t] = '\0';
	}
	int top = -1;
	int num = 1;
	for (int r = 1; r < 25; r++)
	{
		threadedPointer p = head;
		int q = r;
		if (tree_1[r] != 0)
		{
			while (q != 1)
			{
				if (q % 2 == 0)
				{
					q = q / 2;
					arr_2[++top] = 'l';
				}
				else
				{
					q = q / 2;
					arr_2[++top] = 'r';
				}
			}
			while (top != -1)
			{
				if (arr_2[top] == 'l')
				{
					p = p->leftchild;
					arr_2[top--] = '\0';
				}
				else
				{
					p = p->rightchild;
					arr_2[top--] = '\0';
				}
			}
			if (tree_1[r * 2] == 0)
			{

			}
			else
			{
				head = insertLeft(head, p, tree_1[r * 2]);
				num++;
			}
			if (tree_1[r * 2 + 1] == 0)
			{

			}
			else
			{
				head = insertRight(head, p, tree_1[r * 2 + 1]);
				num++;
			}
		}
		if (num == size)
		{
			break;
		}
	}
	char a = '\0';
	char delete = '\0';
	int place = 0;
	while (1)
	{
		a = fgetc(fp_r);
		if (a == '\n' || a == ' ')
		{

		}
		else if (a == '-')
		{
			delete = a;
			break;
		}
	}
	fscanf(fp_r, "%d", &place);
	threadedPointer del_child = t_inorder(head, place);
	threadedPointer parent = par_inorder(head, del_child);
	head = del_node(head, root, parent, del_child);
	printf("Inorder traversal of threaded binary tree : ");
	tinorder(root);
	fclose(fp_r);
	free(root);
	free(head);
	free(arr_2);

	return 0;
}

void inorder(threadedPointer head)
{
	if (head)
	{
		inorder(head->leftchild);
		printf("%d ", head->data);
		inorder(head->rightchild);
	}
}

threadedPointer insertRight(threadedPointer head, threadedPointer parent, int data)
{
	threadedPointer child = (threadedPointer)malloc(sizeof(threadedTree));
	threadedPointer temp;
	child->data = data;
	child->rightchild = parent->rightchild;
	child->rightThread = parent->rightThread;
	child->leftchild = parent;
	child->leftThread = 1;
	parent->rightchild = child;
	parent->rightThread = 0;
	if (!child->rightThread)
	{
		temp = insucc(child);
		temp->leftchild = child;
	}
	return head;
}

threadedPointer insertLeft(threadedPointer head, threadedPointer parent, int data)
{
	threadedPointer child = (threadedPointer)malloc(sizeof(threadedTree));
	threadedPointer temp;
	child->data = data;
	child->leftchild = parent->leftchild;
	child->leftThread = parent->leftThread;
	child->rightchild = parent;
	child->rightThread = 1;
	parent->leftchild = child;
	parent->leftThread = 0;
	if (!child->leftThread)
	{
		temp = child->leftchild;
		while (!temp->rightThread)
		{
			temp = temp->rightchild;
		}
		temp->rightchild = child;
	}
	/*if (!child->leftThread)
	{
		temp = insucc(child);
		temp->rightchild = child;
	}*/
	return head;
}

void tinorder(threadedPointer tree)
{
	threadedPointer temp = tree;
	for (;;)
	{
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%d ", temp->data);
	}
}

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightchild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftchild;
	return temp;
}

threadedPointer in_succ(threadedPointer ptr)
{
	if (ptr->rightThread == 1)
	{
		return ptr->rightchild;
	}
	else
	{
		ptr = ptr->rightchild;
		while (ptr->leftThread == 0)
		{
			ptr = ptr->leftchild;
		}
		return ptr;
	}
}

threadedPointer t_inorder(threadedPointer root, int value)
{
	threadedPointer ptr;
	ptr = root;
	while (ptr->leftThread == 0)
	{
		ptr = ptr->leftchild;
	}
	while (ptr != NULL)
	{
		if (ptr->data == value)
		{
			return ptr;
		}
		ptr = in_succ(ptr);
	}
	return NULL;
}

threadedPointer par_inorder(threadedPointer root, threadedPointer child)
{
	threadedPointer ptr;
	ptr = root;
	while (ptr->leftThread == 0)
	{
		ptr = ptr->leftchild;
	}
	while (ptr != NULL)
	{
		if (ptr->leftThread == 0 && ptr->leftchild == child)
		{
			return ptr;
		}
		else if (ptr->rightThread == 0 && ptr->rightchild == child)
		{
			return ptr;
		}
		ptr = in_succ(ptr);
	}
	return NULL;
}

void p_inorder(threadedPointer root)
{
	threadedPointer ptr;
	if (root == NULL)
	{
		printf("Tree is empty");
		return;
	}
	ptr = root;
	while (ptr->leftThread == 0)
		ptr = ptr->leftchild;
	while (ptr != NULL)
	{
		printf("%d ", ptr->data);
		ptr = in_succ(ptr);
	}
}

threadedPointer del_node(threadedPointer root, threadedPointer head, threadedPointer par, threadedPointer ptr)
{
	if (ptr->leftThread == 0 && ptr->rightThread == 0)
	{
		root = case_c(root, head, par, ptr);
	}
	else if (ptr->leftThread == 0)
	{
		root = case_b(root, par, ptr);
	}
	else if (ptr->rightThread == 0)
	{
		root = case_b(root, par, ptr);
	}
	else
	{
		root = case_a(root, par, ptr);
	}
	return root;
}

threadedPointer case_a(threadedPointer root, threadedPointer par, threadedPointer ptr)
{
	if (par == NULL)
		root = NULL;
	else if (ptr == par->leftchild)
	{
		par->leftThread = 1;
		par->leftchild = ptr->leftchild;
	}
	else
	{
		par->rightThread = 1;
		par->rightchild = ptr->rightchild;
	}
	free(ptr);
	return root;
}
threadedPointer case_b(threadedPointer root, threadedPointer par, threadedPointer ptr)
{
	threadedPointer child, s, p;
	if (ptr->leftThread == 0)
		child = ptr->leftchild;
	else
		child = ptr->rightchild;
	if (par == NULL)
		root = child;
	else if (ptr == par->leftchild)
		par->leftchild = child;
	else
		par->rightchild = child;
	s = in_succ(ptr);
	p = in_pred(ptr);
	if (ptr->leftThread == 0)
		p->rightchild = s;
	else
	{
		if (ptr->rightThread == 0)
			s->leftchild = p;
	}
	free(ptr);
	return root;
}
threadedPointer case_c(threadedPointer root, threadedPointer head, threadedPointer par, threadedPointer ptr)
{
	threadedPointer suc, parsuc;
	parsuc = ptr;
	suc = ptr->rightchild;
	while (suc->leftThread != 1)
	{
		parsuc = suc;
		suc = suc->leftchild;
	}
	int temp = ptr->data;
	ptr->data = suc->data;
	suc->data = temp;
	if (suc->leftThread == 1 && suc->rightThread == 1)
		root = case_a(root, parsuc, suc);
	else
		root = case_b(root, parsuc, suc);
	return root;
}

threadedPointer in_pred(threadedPointer ptr)
{
	if (ptr->leftThread == 1)
		return ptr->leftchild;
	else
	{
		ptr = ptr->leftchild;
		while (ptr->rightThread == 0)
			ptr = ptr->rightchild;
		return ptr;
	}
}