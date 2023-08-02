#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int stringToInt(char* key);
int find_pn(int num);

typedef struct hash {
	int key;
	char keyword[10];
} hash;

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int total = 0;
	fscanf(fp, "%d", &total);
	int dict = find_pn(total);
	hash* c_hash = (hash*)malloc(dict * sizeof(hash));
	for (int i = 0; i < dict; i++)
	{
		c_hash[i].key = i;
		strcpy(c_hash[i].keyword, "0");
	}
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
				if (strcmp(c_hash[value].keyword, "0") != 0)
				{
					for (int s = 1; s < dict; s++)
					{
						int lp = (value + s) % dict;
						if (strcmp(c_hash[lp].keyword, "0") == 0)
						{
							strcpy(c_hash[lp].keyword, cp_word);
							break;
						}
					}
				}
				else
				{
					strcpy(c_hash[value].keyword, cp_word);
				}
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
		if (strcmp(c_hash[value].keyword, scan) != 0)
		{
			int find = 0;
			for (int u = 1; u < dict; u++)
			{
				int lp = (value + u) % dict;
				if (strcmp(c_hash[lp].keyword, scan) == 0)
				{
					printf("> 버킷 주소 %d에 저장된 %s입니다.\n\n", lp, scan);
					find = 1;
				}
			}
			if (find == 0)
			{
				printf("> 키워드가 존재하지 않습니다.\n\n");
			}
		}
		else if (strcmp(c_hash[value].keyword, scan) == 0)
		{
			printf("> 버킷 주소 %d에 저장된 %s입니다.\n\n", value, scan);
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

int find_pn(int num)
{
	int hasDiv = 0;
	int i = 1;
	for (i; i < 100; i++)
	{
		for (int div = 2; div <= sqrt(num + i); div++)
		{
			if ((num + i) % div == 0)
			{
				hasDiv = 1;
				break;
			}
		}
		if (hasDiv == 0)
		{
			break;
		}
		hasDiv = 0;
	}
	return (num + i);
}