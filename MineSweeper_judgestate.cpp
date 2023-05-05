#pragma once
#include "headfile.h"
int State_judge(int** arr_out, int** arr_in,int mine);
int Mine_judge(int** arr_out, int** arr_in,int mine);
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断游戏的结束与否，是否踩雷
// 参数说明     arr_out为外盘地址，arr_in为内盘地址
// 返回参数     游戏状态
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int State_judge(int** arr_out, int** arr_in,int mine)
{
	int i, j,number1=0,num2=0;
	int num = Col * Row;
	for(i=1;i<Row+1;i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 0&&arr_in[i][j]==9)
			{
				return -1;
			}
			/*if (arr_out[i][j] == 2 && arr_in[i][j] == 9)
			{
				number1++;
			}*/
			if (arr_out[i][j] == 0&&arr_in[i][j]!=9)
			{
				num2++;
			}
		}
	if (num2 == (num - mine))
		return 1;
	else
		return 0;
}

int Mine_judge(int** arr_out, int** arr_in,int mine)
{
	int i, j, number1 = 0;
	for (i = 1; i < Row + 1; i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 2 && arr_in[i][j] == 9)
			{
				number1++;
			}
		}
	return mine-number1;
}