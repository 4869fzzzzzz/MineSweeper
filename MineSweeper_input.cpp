#pragma once
#include "headfile.h"
void Gameboard_input(int** s);
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     游戏内盘雷区的输入
// 参数说明     s-游戏内盘头地址
// 返回参数     无
// 使用示例     
// 备注信息		仅输入地雷位置，无其他处理
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_input(int** s)
{
	int i, j;

	char ch;
	for (i = 0; i < Row + 2; i++)
	{
		for (j = 0; j < Col + 2; j++)
		{
			if (i == 0 || j == 0 || i == Row + 1 || j == Col + 1)
			{
				s[i][j] = 0;
			}
			else
			{
				scanf("%c", &ch);
				if (ch == '*')
				{
					s[i][j] = 9;
				}
				else
				{
					s[i][j] = 0;
				}
			}

		}
		if (i != Row + 1) {
			getchar();
		}
	}
}