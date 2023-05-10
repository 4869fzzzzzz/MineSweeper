#pragma once
#include "headfile.h"
void Gameboard_debugout(int** s);
void Gameboard_Print(int** arr_out, int** arr_in);
void Gameboard_Print_out(int** arr_out, int** arr_in);
void Gameover_print(int state, int Operation_number,int mine, int** Game_board_out, int** Game_board_in);
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     输出游戏内盘函数
// 参数说明     s-游戏盘头地址
// 返回参数     无
// 使用示例     
// 备注信息		调试用显示内盘函数
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_debugout(int**s)
{
	int i, j;
	for (i = 1; i < Row+1; i++)
	{
		for (j = 1; j < Col+1; j++)
		{
			printf("%d ",s[i][j]);
		}
		printf("\n");
	}
}

void Gameboard_Print(int** arr_out, int** arr_in)
{
	int i, j;
	for (i = 1; i < Row + 1; i++)
	{
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 0)
			{
				if (j != Col)
					printf("%d", arr_in[i][j]);
				else
					printf("%d\n",arr_in[i][j]);
			}
			else if(arr_out[i][j]==1)
			{
				if (j != Col)
					printf(".");
				else
					printf(".\n");
			}
			else if (arr_out[i][j] == 2)
			{
				if (j != Col)
					printf("!");
				else
					printf("!\n");
			}
			else if (arr_out[i][j] == 3)
			{
				if (j != Col)
					printf("?");
				else
					printf("?\n");
			}
		}
		
	}
}

void Gameover_print(int state,int Operation_number,int mine, int**arr_out,int** arr_in)
{
	if (state == -1)
	{
		printf("Hit mine, you lose。\n");
	}
	else
	{
		printf("Game over, you win\n");
	}
	printf("%d %d\n",Operation_number,mine);
	Gameboard_Print_out(arr_out, arr_in);
}

void Gameboard_Print_out(int** arr_out, int** arr_in)
{
	int i, j;
	for (i = 1; i < Row + 1; i++)
	{
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_in[i][j] == 9)
			{
				if (j != Col)
					printf("*");
				else
					printf("*\n");
			}
			else {
				if (arr_out[i][j] == 0)
				{
					if (j != Col)
						printf("%d", arr_in[i][j]);
					else
						printf("%d\n", arr_in[i][j]);
				}
				else if (arr_out[i][j] == 1)
				{
					if (j != Col)
						printf(".");
					else
						printf(".\n");
				}
				else if (arr_out[i][j] == 2)
				{
					if (j != Col)
						printf("!");
					else
						printf("!\n");
				}
				else if (arr_out[i][j] == 3)
				{
					if (j != Col)
						printf("?");
					else
						printf("?\n");
				}
			}
		}

	}
}