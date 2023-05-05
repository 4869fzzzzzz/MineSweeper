#pragma once
#include "headfile.h"
void Gameboard_free(int** s);
void User_Operation(int** arr_out, int** arr_in);
int outNumber(int row, int col, int** arr_out, int** arr_in);
void eightzoneSweep(int row, int col, int** arr_out, int** arr_in);
int Operation1(int** arr_out, int** arr_in);
int Operation2(int** arr_out, int** arr_in);
int Operation3(int** arr_out, int** arr_in);
int Operation4(int** arr_out, int** arr_in);
int Operation9(int** arr_out, int** arr_in);
//-------------------------------------------------------------------------------------------------------------------
// �������     ������Ϸ�������ͷ��ڴ�
// ����˵��     sΪ���ͷ��ڴ�ͷ��ַ
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		�ƺ����е�����
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_free(int**s)
{
	int i;
	for (i = 0; i < Row+2; i++)
		free(s[i]);
	//free(s);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ִ���û������ĺ��ĺ���
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		
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
		printf("�������Ϸ�\n");
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ִ���û�����1�����
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ִ���û�����2���һ������ױ��
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		
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
// �������     ִ���û�����3���һ����ʺ�
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		
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
// �������     ִ���û�����4���һ���ȡ�����
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		
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
// �������     ִ���û�����9���һ��������Χ3x3
// ����˵��     arr_out���������ַ,arr_in���������ַ
// ���ز���     ���Կ��ǰѲ����ɹ�����
// ʹ��ʾ��     
// ��ע��Ϣ		
//-------------------------------------------------------------------------------------------------------------------
int Operation9(int** arr_out, int** arr_in)
{
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ����ø���Χ3x3,�ɵݹ�
// ����˵��     row����������������col����������������arr_out���������ַ,arr_in���������ַ
// ���ز���     ��
// 
// ʹ��ʾ��     
// ��ע��Ϣ		|(-1,-1)|(-1,0)|(-1,+1)|�ڲ�����
//				|(0��-1)|(0,0) |(0,+1) |
//              |(+1,-1)|(+1,0)|(+1,+1)|Ҫ�ȵ㿪����0,0������Ȼ�ݹ���ظ�
//				�ƺ��޷�����㿪����Χȫ�Ǳ�ǵ����
//				Ҫ�����ټ�һ��������
//-------------------------------------------------------------------------------------------------------------------
void eightzoneSweep(int row,int col,int**arr_out,int**arr_in)
{
	if (arr_out[row][col] == 1)
	{
		/*if (arr_in[row][col] == 0 && (outNumber(row, col, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row, col, arr_out, arr_in);
		}*/
		arr_out[row][col] = 0;

	}
	if (arr_out[row - 1][col - 1] !=0)
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

	if (arr_out[row - 1][col ] != 0)
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

	if (arr_out[row - 1][col + 1] != 0)
	{
		if (arr_in[row - 1][col + 1] == 0 && (outNumber(row - 1, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col + 1, arr_out, arr_in);
		}
		if(arr_out[row-1][col+1]==1)
		arr_out[row - 1][col + 1] = 0;

	}


	if (arr_out[row ][col - 1]!= 0)
	{
		if (arr_in[row ][col - 1] == 0 && (outNumber(row , col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row , col - 1, arr_out, arr_in);
		}
		if(arr_out[row][col - 1] == 1)
		arr_out[row ][col - 1] = 0;

	}

	

	if (arr_out[row][col+1] != 0)
	{
		if (arr_in[row][col + 1] == 0 && (outNumber(row , col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row, col + 1, arr_out, arr_in);
		}
		if(arr_out[row][col+1]==1)
		arr_out[row ][col + 1] = 0;

	}


	if (arr_out[row + 1][col - 1] != 0)
	{
		if (arr_in[row + 1][col - 1] == 0 && (outNumber(row + 1, col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col - 1, arr_out, arr_in);
		}
		if(arr_out[row+1][col-1]==1)
		arr_out[row + 1][col - 1] = 0;

	}

	if (arr_out[row + 1][col ] != 0)
	{
		if (arr_in[row - 1][col ] == 0 && (outNumber(row - 1, col , arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col , arr_out, arr_in);
		}
		if(arr_out[row+1][col]==1)
		arr_out[row + 1][col ] = 0;

	}

	if (arr_out[row + 1][col + 1] != 0)
	{
		if (arr_in[row + 1][col + 1] == 0 && (outNumber(row + 1, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col + 1, arr_out, arr_in);
		}
		if(arr_out[row+1][col+1]==1)
		arr_out[row + 1][col + 1] = 0;

	}
	
}


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

	if (arr_out[row][col] == 1)
	{
		num++;
	}

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