#pragma once
#include "headfile.h"
void Gameboard_debugout(int** s);
void Gameboard_Print(int** arr_out, int** arr_in);
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