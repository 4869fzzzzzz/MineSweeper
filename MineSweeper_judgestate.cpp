#pragma once
#include "headfile.h"
int State_judge(int** arr_out, int** arr_in);
int Mine_judge(int** arr_out, int** arr_in);
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断游戏的结束与否，是否踩雷
// 参数说明     arr_out为外盘地址，arr_in为内盘地址
// 返回参数     游戏状态
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int State_judge(int** arr_out, int** arr_in)
{
	/*int i, j,number1;
	for(i=1;i<Row+1;i++)
		for (j = 1; j < Col + 1; j++)
		{
			if(arr_out[][])
		}*/
	return 0;
}

int Mine_judge(int** arr_out, int** arr_in)
{
	return 1;
}