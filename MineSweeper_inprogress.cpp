#pragma once
#include "headfile.h"
void Gameboard_free(int** s);
int Flag_number(int row, int col, int** arr_out);
void User_Operation(int** arr_out, int** arr_in);
int outNumber(int row, int col, int** arr_out, int** arr_in);
void eightzoneSweep(int row, int col, int** arr_out, int** arr_in);
int Operation1(int** arr_out, int** arr_in);
int Operation2(int** arr_out, int** arr_in);
int Operation3(int** arr_out, int** arr_in);
int Operation4(int** arr_out, int** arr_in);
int Operation9(int** arr_out, int** arr_in);
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     用于游戏结束后释放内存
// 参数说明     s为待释放内存头地址
// 返回参数     无
// 使用示例     
// 备注信息		似乎还有点问题
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_free(int**s)
{
	int i;
	for (i = 0; i < Row+2; i++)
		free(s[i]);
	//free(s);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作的核心函数
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
void User_Operation(int** arr_out, int** arr_in)
{
	if (Opt.row <= Row && Opt.col <= Col)
	{
		switch (Opt.model)
		{
		case 1:
			Operation1(arr_out, arr_in);
			break;
		case 2:
			Operation2(arr_out, arr_in);
			break;
		case 3:
			Operation3(arr_out, arr_in);
			break;
		case 4:
			Operation4(arr_out, arr_in);
			break;
		case 9:
			Operation9(arr_out, arr_in);
			break;
		default:
			printf("error\n");
			break;
		}
	}
	else
		printf("操作不合法\n");
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作1，左击
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int Operation1(int**arr_out,int**arr_in)
{
	if (arr_out[Opt.row][Opt.col] == 0)
	{
		return 0;
	}
	else if(arr_out[Opt.row][Opt.col]==1)
	{
		if (arr_in[Opt.row][Opt.col] != 0)
		{
			arr_out[Opt.row][Opt.col] = 0;
		}
		else
		{
			eightzoneSweep(Opt.row,Opt.col,arr_out,arr_in);
		}
		return 1;
	}
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作2，右击，地雷标记
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int Operation2(int** arr_out, int** arr_in)
{
	if (arr_out[Opt.row][Opt.col] == 0)
	{
		return 0;
	}
	else
	{
		arr_out[Opt.row][Opt.col] = 2;
	}
	return 1;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作3，右击，问号
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int Operation3(int** arr_out, int** arr_in)
{
	if (arr_out[Opt.row][Opt.col] == 0)
	{
		return 0;
	}
	else
	{
		arr_out[Opt.row][Opt.col] = 3;
	}
	return 1;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作4，右击，取消标记
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int Operation4(int** arr_out, int** arr_in)
{
	if (arr_out[Opt.row][Opt.col] == 2 || arr_out[Opt.row][Opt.col] == 3)
	{
		arr_out[Opt.row][Opt.col] = 1;
	}
	else
	{
		return 0;
	}
	return 1;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     执行用户操作9，右击，清除周围3x3
// 参数说明     arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     可以考虑把操作成功返回
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int Operation9(int** arr_out, int** arr_in)
{
	int num=Flag_number(Opt.row, Opt.col, arr_out);
	int judge = 0;
	if(num!=arr_in[Opt.row][Opt.col])
		return 0;
	else
	{
		int i, j;
		for (i = Opt.row - 1; i < Opt.row + 2; i++) 
		{
			for (j = Opt.col - 1; j < Opt.col + 2; j++)
			{
				if (arr_out[i][j] == 1 && arr_in[i][j] == 9)
				{
					judge++;
					arr_out[i][j] = 0;
				}
			}
		}
		
		 
			if (judge == 0) {
				

				for (i = Opt.row - 1; i < Opt.row + 2; i++)
					for (j = Opt.col - 1; j < Opt.col + 2; j++)
					{
						if (arr_out[i][j] == 1)
						{
							if (arr_in[i][j] != 0)
							{
								arr_out[i][j] = 0;
							}
							else
							{
								eightzoneSweep(i, j, arr_out, arr_in);
							}
						}
					}
				return 1;
			}

	}
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     清除该格周围3x3,可递归
// 参数说明     row，需清除格的行数，col，需清除格的列数，arr_out外盘数组地址,arr_in内盘数组地址
// 返回参数     无
// 
// 使用示例     
// 备注信息		|(-1,-1)|(-1,0)|(-1,+1)|内部调用
//				|(0，-1)|(0,0) |(0,+1) |
//              |(+1,-1)|(+1,0)|(+1,+1)|要先点开本格（0,0），不然递归会重复
//				似乎无法解决点开格周围全是标记的情况
//				要试试再加一个数组吗
//-------------------------------------------------------------------------------------------------------------------
void eightzoneSweep(int row,int col,int**arr_out,int**arr_in)
{
	/*int i, j;
	if (arr_out[row][col] == 1)
		arr_out[row][col] = 0;
	for (i = row - 1; i < row + 2; i++) {
		for (j = col - 1; j < row + 2; j++)
		{
			if (i != row || j != col)
			{
				if (arr_out[i][j] != 0)
				{
					if (arr_in[i][j] == 0 && (outNumber(i, j, arr_out, arr_in) > 0))
					{
						eightzoneSweep(i, j, arr_out, arr_in);
					}
					if (arr_out[i][j] == 1)
					{
						arr_out[i][j] = 0;
					}
				}
			}
		}
	}*/
	if (arr_out[row][col] == 1)
	{
		arr_out[row][col] = 0;
	}
	if (arr_out[row - 1][col - 1] ==1)
	{
		
		if (arr_in[row - 1][col - 1] == 0&&(outNumber(row-1,col-1,arr_out,arr_in)>0))
		{
			eightzoneSweep(row - 1, col - 1, arr_out, arr_in);
		}
		if (arr_out[row - 1][col - 1] == 1)
		{
			arr_out[row - 1][col - 1] = 0;
		}
	}

	if (arr_out[row - 1][col ] == 1)
	{
		if (arr_in[row - 1][col ] == 0 && (outNumber(row - 1, col , arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col , arr_out, arr_in);
		}
		if (arr_out[row - 1][col] == 1) 
		{
			arr_out[row - 1][col] = 0;
		}
	}

	if (arr_out[row - 1][col + 1] == 1)
	{
		if (arr_in[row - 1][col + 1] == 0 && (outNumber(row - 1, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col + 1, arr_out, arr_in);
		}
		if(arr_out[row-1][col+1]==1)
		arr_out[row - 1][col + 1] = 0;

	}


	if (arr_out[row ][col - 1]== 1)
	{
		if (arr_in[row ][col - 1] == 0 && (outNumber(row , col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row , col - 1, arr_out, arr_in);
		}
		if(arr_out[row][col - 1] == 1)
		arr_out[row ][col - 1] = 0;

	}

	

	if (arr_out[row][col+1] == 1)
	{
		if (arr_in[row][col + 1] == 0 && (outNumber(row , col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row, col + 1, arr_out, arr_in);
		}
		if(arr_out[row][col+1]==1)
		arr_out[row ][col + 1] = 0;

	}


	if (arr_out[row + 1][col - 1] == 1)
	{
		if (arr_in[row + 1][col - 1] == 0 && (outNumber(row + 1, col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col - 1, arr_out, arr_in);
		}
		if(arr_out[row+1][col-1]==1)
		arr_out[row + 1][col - 1] = 0;

	}

	if (arr_out[row + 1][col] == 1)
	{
		if (arr_in[row + 1][col] == 0 && (outNumber(row + 1, col , arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col , arr_out, arr_in);
		}
		if(arr_out[row+1][col]==1)
		arr_out[row + 1][col] = 0;

	}

	if (arr_out[row + 1][col + 1] == 1)
	{
		if (arr_in[row + 1][col + 1] == 0 && (outNumber(row + 1, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col + 1, arr_out, arr_in);
		}
		if(arr_out[row+1][col+1]==1)
		arr_out[row + 1][col + 1] = 0;

	}
	///*Gameboard_Print(arr_out, arr_in);*/
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     计算某格周围未打开的格数
// 参数说明     row-行，col-列，arr_out-外盘，arr_in-内盘
// 返回参数     周围未打开格数
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int outNumber(int row , int col,int** arr_out,int** arr_in)
{
	int num=0;
	if (row == 0 || col == 0 || col == Col + 1 || row == Row + 1)
		return 0;
	if (arr_out[row - 1][col - 1] == 1)
	{
		num++;
	}

	if (arr_out[row - 1][col] == 1)
	{
		num++;
	}

	if (arr_out[row - 1][col + 1] == 1)
	{
		num++;
	}


	if (arr_out[row][col - 1] == 1)
	{
		num++;
	}

	/*if (arr_out[row][col] == 1)
	{
		num++;
	}*/

	if (arr_out[row][col + 1] == 1)
	{
		num++;
	}


	if (arr_out[row + 1][col - 1] == 1)
	{
		num++;
	}

	if (arr_out[row + 1][col] == 1)
	{
		num++;
	}

	if (arr_out[row + 1][col + 1] == 1)
	{
		num++;
	}
	return num;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断周围旗帜数量
// 参数说明     row行，col列，arr_out外盘
// 返回参数     旗帜数
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int Flag_number(int row, int col,int** arr_out)
{
	int i, j;
	int num = 0;
	for(i=row-1;i<row+2;i++)
		for (j = col-1; j < col + 2; j++)
		{
			
			if (arr_out[i][j] == 2&&(i!=row||j!=col))
				num++;
		}
	return num;
}

