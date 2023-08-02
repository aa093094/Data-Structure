#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void init_losertree(int nums[][10], int winnertree[], int losertree[]);
void make_winner(int losertree[], int winnertree[], int winner[]);
void update_tree1(int winnertree[], int losertree[], int winner[], int index[], int top_index, int nums[][10]);
void update_tree2(int winnertree[], int losertree[], int winner[], int index[], int top_index);
void update_tree3(int winnertree[], int losertree[], int winner[], int index[], int top_index);
int print_winner(int winnertree[], int losertree[], int winner[], int index[], int nums[][10]);

void init_losertree(int nums[][10], int winnertree[], int losertree[])
{
    for (int i = 16; i < 32; i++)
    {
        winnertree[i] = nums[i - 16][0];
        losertree[i] = nums[i - 16][0];
    }
}

void make_winner(int losertree[], int winnertree[], int winner[])
{
    for (int i = 16; i < 32; i += 2)
    {
        if (winnertree[i] < winnertree[i + 1])
        {
            winnertree[i / 2] = winnertree[i];
            losertree[i / 2] = winnertree[i + 1];
            winner[i / 2 - 8] = i - 16;
        }
        else
        {
            winnertree[i / 2] = winnertree[i + 1];
            losertree[i / 2] = winnertree[i];
            winner[i / 2 - 8] = i - 15;
        }
    }
    for (int j = 8; j < 16; j += 2)
    {
        if (winnertree[j] < winnertree[j + 1])
        {
            winnertree[j / 2] = winnertree[j];
            losertree[j / 2] = winnertree[j + 1];
            winner[j / 2 + 4] = winner[j - 8];
        }
        else
        {
            winnertree[j / 2] = winnertree[j + 1];
            losertree[j / 2] = losertree[j];
            winner[j / 2 + 4] = winner[j - 7];
        }
    }
    for (int k = 4; k < 8; k += 2)
    {
        if (winnertree[k] < winnertree[k + 1])
        {
            winnertree[k / 2] = winnertree[k];
            losertree[k / 2] = winnertree[k + 1];
            winner[k / 2 + 10] = winner[k + 4];
        }
        else
        {
            winnertree[k / 2] = winnertree[k + 1];
            losertree[k / 2] = winnertree[k];
            winner[k / 2 + 10] = winner[k + 5];
        }
    }
    int s = 2;
    if (winnertree[s] < winnertree[s + 1])
    {
        winnertree[s / 2] = winnertree[s];
        losertree[s / 2] = winnertree[s + 1];
        losertree[0] = winnertree[s];
        winner[s / 2 + 13] = winner[s + 10];
    }
    else
    {
        winnertree[s / 2] = winnertree[s + 1];
        losertree[s / 2] = winnertree[s];
        losertree[0] = winnertree[s + 1];
        winner[s / 2 + 13] = winner[s + 11];
    }
}

void update_tree1(int winnertree[], int losertree[], int winner[], int index[], int top_index, int nums[][10])
{
    if (top_index == 0 || top_index == 1)
    {
        if (top_index == 0)
        {
            winnertree[16] = nums[0][index[0]];
        }
        else
        {
            winnertree[17] = nums[1][index[1]];
        }
        if (winnertree[16] < winnertree[17])
        {
            winnertree[8] = winnertree[16];
            losertree[8] = winnertree[17];
            winner[0] = 0;
        }
        else
        {
            winnertree[8] = winnertree[17];
            losertree[8] = winnertree[16];
            winner[0] = 1;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 2 || top_index == 3)
    {
        if (top_index == 2)
        {
            winnertree[18] = nums[2][index[2]];
        }
        else
        {
            winnertree[19] = nums[3][index[3]];
        }
        if (winnertree[18] < winnertree[19])
        {
            winnertree[9] = winnertree[18];
            losertree[9] = winnertree[19];
            winner[1] = 2;
        }
        else
        {
            winnertree[9] = winnertree[19];
            losertree[9] = winnertree[18];
            winner[1] = 3;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 4 || top_index == 5)
    {
        if (top_index == 4)
        {
            winnertree[20] = nums[4][index[4]];
        }
        else
        {
            winnertree[21] = nums[5][index[5]];
        }
        if (winnertree[20] < winnertree[21])
        {
            winnertree[10] = winnertree[20];
            losertree[10] = winnertree[21];
            winner[2] = 4;
        }
        else
        {
            winnertree[10] = winnertree[21];
            losertree[10] = winnertree[20];
            winner[2] = 5;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 6 || top_index == 7)
    {
        if (top_index == 6)
        {
            winnertree[22] = nums[6][index[6]];
        }
        else
        {
            winnertree[23] = nums[7][index[7]];
        }
        if (winnertree[22] < winnertree[23])
        {
            winnertree[11] = winnertree[22];
            losertree[11] = winnertree[23];
            winner[3] = 6;
        }
        else
        {
            winnertree[11] = winnertree[23];
            losertree[11] = winnertree[22];
            winner[3] = 7;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 8 || top_index == 9)
    {
        if (top_index == 8)
        {
            winnertree[24] = nums[8][index[8]];
        }
        else
        {
            winnertree[25] = nums[9][index[9]];
        }
        if (winnertree[24] < winnertree[25])
        {
            winnertree[12] = winnertree[24];
            losertree[12] = winnertree[25];
            winner[4] = 8;
        }
        else
        {
            winnertree[12] = winnertree[25];
            losertree[12] = winnertree[24];
            winner[4] = 9;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 10 || top_index == 11)
    {
        if (top_index == 10)
        {
            winnertree[26] = nums[10][index[10]];
        }
        else
        {
            winnertree[27] = nums[11][index[11]];
        }
        if (winnertree[26] < winnertree[27])
        {
            winnertree[13] = winnertree[26];
            losertree[13] = winnertree[27];
            winner[5] = 10;
        }
        else
        {
            winnertree[13] = winnertree[27];
            losertree[13] = winnertree[26];
            winner[5] = 11;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 12 || top_index == 13)
    {
        if (top_index == 12)
        {
            winnertree[28] = nums[12][index[12]];
        }
        else
        {
            winnertree[29] = nums[13][index[13]];
        }
        if (winnertree[28] < winnertree[29])
        {
            winnertree[14] = winnertree[28];
            losertree[14] = winnertree[29];
            winner[6] = 12;
        }
        else
        {
            winnertree[14] = winnertree[29];
            losertree[14] = winnertree[28];
            winner[6] = 13;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
    else
    {
        if (top_index == 14)
        {
            winnertree[30] = nums[14][index[14]];
        }
        else
        {
            winnertree[31] = nums[15][index[15]];
        }
        if (winnertree[30] < winnertree[31])
        {
            winnertree[15] = winnertree[30];
            losertree[15] = winnertree[31];
            winner[7] = 14;
        }
        else
        {
            winnertree[15] = winnertree[31];
            losertree[15] = winnertree[30];
            winner[7] = 15;
        }
        update_tree2(winnertree, losertree, winner, index, top_index);
    }
}

void update_tree2(int winnertree[], int losertree[], int winner[], int index[], int top_index)
{
    if (top_index == 0 || top_index == 1 || top_index == 2 || top_index == 3)
    {
        if (winnertree[8] < winnertree[9])
        {
            winnertree[4] = winnertree[8];
            losertree[4] = winnertree[9];
            winner[8] = winner[0];
        }
        else
        {
            winnertree[4] = winnertree[9];
            losertree[4] = winnertree[8];
            winner[8] = winner[1];
        }
        update_tree3(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 4 || top_index == 5 || top_index == 6 || top_index == 7)
    {
        if (winnertree[10] < winnertree[11])
        {
            winnertree[5] = winnertree[10];
            losertree[5] = winnertree[11];
            winner[9] = winner[2];
        }
        else
        {
            winnertree[5] = winnertree[11];
            losertree[5] = winnertree[10];
            winner[9] = winner[3];
        }
        update_tree3(winnertree, losertree, winner, index, top_index);
    }
    else if (top_index == 8 || top_index == 9 || top_index == 10 || top_index == 11) 
    {
        if (winnertree[12] < winnertree[13])
        {
            winnertree[6] = winnertree[12];
            losertree[6] = winnertree[13];
            winner[10] = winner[4];
        }
        else
        {
            winnertree[6] = winnertree[13];
            losertree[6] = winnertree[12];
            winner[10] = winner[5];
        }
        update_tree3(winnertree, losertree, winner, index, top_index);
    }
    else
    {
        if (winnertree[14] < winnertree[15])
        {
            winnertree[7] = winnertree[14];
            losertree[7] = winnertree[15];
            winner[11] = winner[6];
        }
        else
        {
            winnertree[7] = winnertree[15];
            losertree[7] = winnertree[14];
            winner[11] = winner[7];
        }
        update_tree3(winnertree, losertree, winner, index, top_index);
    }
}

void update_tree3(int winnertree[], int losertree[], int winner[], int index[], int top_index)
{
    if (top_index < 8)
    {
        if (winnertree[4] < winnertree[5])
        {
            winnertree[2] = winnertree[4];
            losertree[2] = winnertree[5];
            winner[12] = winner[8];
        }
        else
        {
            winnertree[2] = winnertree[5];
            losertree[2] = winnertree[4];
            winner[12] = winner[9];
        }
    }
    else
    {
        if (winnertree[6] < winnertree[7])
        {
            winnertree[3] = winnertree[6];
            losertree[3] = winnertree[7];
            winner[13] = winner[10];
        }
        else
        {
            winnertree[3] = winnertree[7];
            losertree[3] = winnertree[6];
            winner[13] = winner[11];
        }
    }
    if (winnertree[2] < winnertree[3])
    {
        winnertree[1] = winnertree[2];
        losertree[1] = winnertree[3];
        losertree[0] = winnertree[2];
        winner[14] = winner[12];
    }
    else
    {
        winnertree[1] = winnertree[3];
        losertree[1] = winnertree[2];
        losertree[0] = winnertree[3];
        winner[14] = winner[13];
    }
}

int print_winner(int winnertree[], int losertree[], int winner[], int index[], int nums[][10])
{
    int top = 0;
    top = losertree[0];
    int top_index = winner[14];
    index[top_index]++;
    update_tree1(winnertree, losertree, winner, index, top_index, nums);
    return top;
}

int main() 
{
    FILE* fp;
    fp = fopen("input.txt", "r");
    int total = 0, runs = 0;
    fscanf(fp, "%d %d", &total, &runs);
    int rows = total / runs + 2;
    int nums[16][10];
    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            nums[i][k] = 10000;
        }
    }
    for (int j = 0; j < runs; j++)
    {
        for (int s = 0; s < rows; s++)
        {
            int num = 0;
            fscanf(fp, "%d", &num);
            nums[j][s] = num;
            char a = fgetc(fp);
            if (a == '\n' || a == EOF)
            {
                break;
            }
        }
    }
    int index[16] = { 0 };
    int winnertree[32] = { 0 };
    int losertree[32] = { 0 };
    init_losertree(nums, winnertree, losertree);
    int winner[15] = { 0 };
    make_winner(losertree, winnertree, winner);
    for (int p = 0; p < total; p++)
    {
        int b = print_winner(winnertree, losertree, winner, index, nums);
        printf("%d ", b);
    }

    return 0;
}