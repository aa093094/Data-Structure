#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hash* hashpointer;
typedef struct element {
	int key;
	char keyword[10];
} element;
typedef struct hash {
	element data;
	hashpointer link;
} hash;

unsigned int stringToInt(char* key);
hashpointer goto_last(hashpointer head);
hashpointer insert_node(hashpointer head, char word[10]);

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int dict = 13;
	hashpointer c_hash[13];
	for (int i = 0; i < 13; i++)
	{
		c_hash[i] = (hashpointer)malloc(sizeof(hash));
		c_hash[i]->data.key = i;
		strcpy(c_hash[i]->data.keyword, "0");
		c_hash[i]->link = NULL;
	}
	int total = 0;
	fscanf(fp, "%d", &total);
	char b = fgetc(fp);
	char parse[100];
	memset(parse, '\0', sizeof(parse));
	fgets(parse, 100, fp);
	while (1)
	{
		char word[10];
		memset(word, '\0', sizeof(word));
		char a = '\0';
		int j = 0;
		int k = 0;
		a = parse[j++];
		while (1)
		{
			if (a != ' ' && a != '\n' && a != '\0')
			{
				word[k++] = a;
			}
			else
			{
				char cp_word[10];
				strcpy(cp_word, word);
				unsigned int key = stringToInt(word);
				int value = key % dict;
				c_hash[value] = insert_node(c_hash[value], cp_word);
				memset(word, '\0', sizeof(word));
				k = 0;
			}
			if (a == '\n' || a == '\0') break;
			a = parse[j++];
		}
		if (a == '\0') break;
		fgets(parse, 100, fp);
	}
	fclose(fp);
	while (1)
	{
		printf("> 검색할 키워드를 입력하시오...\n> ");
		char scan[10];
		memset(scan, '\0', sizeof(scan));
		scanf("%s", scan);
		if (strcmp(scan, "quit") == 0)
		{
			printf("> 종료합니다.");
			break;
		}
		unsigned int key = stringToInt(scan);
		int value = key % dict;
		hashpointer node;
		if (c_hash[value]->link)
		{
			node = c_hash[value]->link;
			if (strcmp(node->data.keyword, scan) != 0)
			{
				int find = 0;
				for (node; node != NULL; node = node->link)
				{
					if (strcmp(node->data.keyword, scan) == 0)
					{
						printf("> 버킷 주소 %d에 저장된 %s입니다.\n\n", value, scan);
						find = 1;
						break;
					}
				}
				if (find == 0)
				{
					printf("> 키워드가 존재하지 않습니다.\n\n");
				}
			}
			else if (strcmp(node->data.keyword, scan) == 0)
			{
				printf("> 버킷 주소 %d에 저장된 %s입니다.\n\n", value, scan);
			}
		}
		else
		{
			printf("> 키워드가 존재하지 않습니다.\n\n");
		}
	}

	return 0;
}

unsigned int stringToInt(char* key)
{
	int number = 0;
	while (*key)
	{
		number += *key++;
	}
	return number;
}

hashpointer goto_last(hashpointer head)
{
	hashpointer node = head;
	for (; node->link != NULL; node = node->link);
	return node;
}

hashpointer insert_node(hashpointer head, char word[10])
{
	hashpointer node = head;
	node = goto_last(node);
	hashpointer temp = (hashpointer)malloc(sizeof(hash));
	temp->data.key = node->data.key;
	strcpy(temp->data.keyword, word);
	temp->link = NULL;
	node->link = temp;
	return head;
}