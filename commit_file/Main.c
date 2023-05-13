#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Game_over_lose -1;
#define Game_In_progress 0;
#define Game_over_win 1;
struct opt {
	int model;
	int row, col;
};
int Col;//列
int Row;//行
int Game_state;//游戏状态
struct opt Opt;//用户操作
int** Gameboard_setup_in();
int** game_board_in_init();
int** game_board_out_init();
int** game_board_tmp_init(int** arr_out);
int Count_mine(int** arr);
int MineNumber(int** s, int row, int col);
void Gameboard_init(int** arr);

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

void Gameboard_input(int** s);
void Get_User_Operatian();

int State_judge(int** arr_out, int** arr_in, int mine);
int Mine_judge(int** arr_out, int** arr_in, int mine);

void Gameboard_debugout(int** s);
void Gameboard_Print(int** arr_out, int** arr_in);
void Gameboard_Print_out(int** arr_out, int** arr_in);
void Gameover_print(int state, int Operation_number, int mine, int** Game_board_out, int** Game_board_in);
/****************************************************************
	@Author:zhaofei
	@Mail:zf4869@qq.com
*****************************************************************/
int main()
{
	int Operation_number = 0;//操作次数
	int Mine_number = 0;
	int Mine_remain = 0;
	Operation_number = 0;
	int** Game_board_in;
	int** Game_board_out;
	Game_board_in = game_board_in_init();
	Game_board_out = game_board_out_init();
	//printf("%d\n",Game_board[Row+1][Col+1]);
	//Gameboard_debugout(Game_board_out);
	Mine_number = Count_mine(Game_board_in);
	/*Gameboard_debugout(Game_board_in);*/
	//1 1 9会出问题，待进一步测试-
	//5.7 改完了，op1加减号没都换完，血压高了，另外有空可以重构一下，加个循环看起来顺眼
	//双击似乎不能打开后再输出，需要提前加一个判断
	//游戏模式待补充，样例过了，就差一些特殊情况了，周围全是标记的0等
	//特殊的直接不穿过，改个判据就ok了，似乎没什么问题了
	while (!Game_state)
	{
		Get_User_Operatian();
		User_Operation(Game_board_out, Game_board_in);
		Mine_remain = Mine_judge(Game_board_out, Game_board_in, Mine_number);
		Operation_number++;
		Game_state = State_judge(Game_board_out, Game_board_in, Mine_number);

		//打印提示
		if (Game_state != 0)
			break;
		printf("Game in prograss\n");
		printf("%d %d\n", Operation_number, Mine_remain);
		Gameboard_Print(Game_board_out, Game_board_in);
	}
	//输出结束后提示
	Gameover_print(Game_state, Operation_number, Mine_remain, Game_board_out, Game_board_in);
	Gameboard_free(Game_board_in);
	Gameboard_free(Game_board_out);
	return 0;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     游戏初识化的主函数
// 参数说明     
// 返回参数     返回创建好的游戏盘的主地址
// 使用示例     
// 备注信息		只是游戏内盘，外盘额外创建
//-------------------------------------------------------------------------------------------------------------------
int** game_board_in_init()
{
	int modle = 0;
	int mine = 0;
	Game_state = Game_In_progress;

	int** s;
	scanf("%d", &modle);
	if (modle == 1)
	{
		Col = 9;
		Row = 9;
	}
	else if (modle == 2)
	{
		Col = 16;
		Row = 16;
	}
	else if (modle == 3)
	{
		Col = 30;
		Row = 16;
	}
	else
	{
		scanf("%d", &Row);
		scanf("%d", &Col);
		scanf("%d", &mine);
	}

	s = Gameboard_setup_in();
	Gameboard_input(s);
	Gameboard_init(s);
	return s;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     游戏盘的建立
// 参数说明     无
// 返回参数     二维动态数组的头地址
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int** Gameboard_setup_in()
{
	int** arr;
	int i = 0;
	arr = (int**)malloc(sizeof(int*) * Row + 2);
	for (; i < Row + 2; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * (Col + 2));
	}
	return arr;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     内盘初识化
// 参数说明     arr-内盘数组指针
// 返回参数     无
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_init(int** arr)
{
	int i, j;
	for (i = 1; i < Row + 1; i++)
	{
		for (j = 1; j < Col + 1; j++)
		{
			if (arr[i][j] != 9)
			{
				arr[i][j] = MineNumber(arr, i, j);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     单元格雷数统计
// 参数说明     s-内盘头地址，row，行数，col，列数
// 返回参数     该格8邻域内的雷数
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int MineNumber(int** s, int row, int col)
{
	int number = 0;
	if (s[row - 1][col - 1] == 9)
	{
		number++;
	}
	if (s[row - 1][col] == 9)
	{
		number++;
	}
	if (s[row - 1][col + 1] == 9)
	{
		number++;
	}
	if (s[row][col - 1] == 9)
	{
		number++;
	}
	if (s[row][col + 1] == 9)
	{
		number++;
	}
	if (s[row + 1][col - 1] == 9)
	{
		number++;
	}
	if (s[row + 1][col] == 9)
	{
		number++;
	}
	if (s[row + 1][col + 1] == 9)
	{
		number++;
	}
	return number;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     游戏外盘的建立
// 参数说明     无
// 返回参数     二维动态数组的头地址
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int** game_board_out_init()
{
	int** arr;
	arr = Gameboard_setup_in();
	int i, j;
	for (i = 0; i < Row + 2; i++)
	{
		for (j = 0; j < Col + 2; j++)
		{
			if (i == 0 || j == 0 || i == Row + 1 || j == Col + 1)
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}
	return arr;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     计算游戏总雷数
// 参数说明     arr游戏内盘地址
// 返回参数     游戏总雷数
// 使用示例     
// 备注信息		用于游戏胜利的判断
//-------------------------------------------------------------------------------------------------------------------
int Count_mine(int** arr)
{
	int i, j;
	int num = 0;
	for (i = 1; i < Row + 1; i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr[i][j] == 9)
				num++;
		}
	return num;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     游戏外盘的建立
// 参数说明     无
// 返回参数     二维动态数组的头地址
// 使用示例     
// 备注信息		内部调用
//-------------------------------------------------------------------------------------------------------------------
int** game_board_tmp_init(int** arr_out)
{
	int** arr;
	arr = Gameboard_setup_in();
	int i, j;
	for (i = 0; i < Row + 2; i++)
	{
		for (j = 0; j < Col + 2; j++)
		{
			if (i == 0 || j == 0 || i == Row + 1 || j == Col + 1)
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
			if (arr_out[i][j] == 2)
				arr[i][j] = 2;
			else if (arr_out[i][j] == 3)
			{
				arr[i][j] = 3;
			}
		}
	}
	return arr;
}
//
//
//
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     用于游戏结束后释放内存
// 参数说明     s为待释放内存头地址
// 返回参数     无
// 使用示例     
// 备注信息		似乎还有点问题
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_free(int** s)
{
	int i;
	for (i = 0; i < Row + 2; i++)
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
int Operation1(int** arr_out, int** arr_in)
{
	if (arr_out[Opt.row][Opt.col] == 0)
	{
		return 0;
	}
	else if (arr_out[Opt.row][Opt.col] == 1)
	{
		if (arr_in[Opt.row][Opt.col] != 0)
		{
			arr_out[Opt.row][Opt.col] = 0;
		}
		else
		{
			eightzoneSweep(Opt.row, Opt.col, arr_out, arr_in);
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
	int num = Flag_number(Opt.row, Opt.col, arr_out);
	int judge = 0;
	if (num != arr_in[Opt.row][Opt.col])
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
void eightzoneSweep(int row, int col, int** arr_out, int** arr_in)
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
	if (arr_out[row - 1][col - 1] == 1)
	{

		if (arr_in[row - 1][col - 1] == 0 && (outNumber(row - 1, col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col - 1, arr_out, arr_in);
		}
		if (arr_out[row - 1][col - 1] == 1)
		{
			arr_out[row - 1][col - 1] = 0;
		}
	}

	if (arr_out[row - 1][col] == 1)
	{
		if (arr_in[row - 1][col] == 0 && (outNumber(row - 1, col, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row - 1, col, arr_out, arr_in);
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
		if (arr_out[row - 1][col + 1] == 1)
			arr_out[row - 1][col + 1] = 0;

	}


	if (arr_out[row][col - 1] == 1)
	{
		if (arr_in[row][col - 1] == 0 && (outNumber(row, col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row, col - 1, arr_out, arr_in);
		}
		if (arr_out[row][col - 1] == 1)
			arr_out[row][col - 1] = 0;

	}



	if (arr_out[row][col + 1] == 1)
	{
		if (arr_in[row][col + 1] == 0 && (outNumber(row, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row, col + 1, arr_out, arr_in);
		}
		if (arr_out[row][col + 1] == 1)
			arr_out[row][col + 1] = 0;

	}


	if (arr_out[row + 1][col - 1] == 1)
	{
		if (arr_in[row + 1][col - 1] == 0 && (outNumber(row + 1, col - 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col - 1, arr_out, arr_in);
		}
		if (arr_out[row + 1][col - 1] == 1)
			arr_out[row + 1][col - 1] = 0;

	}

	if (arr_out[row + 1][col] == 1)
	{
		if (arr_in[row + 1][col] == 0 && (outNumber(row + 1, col, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col, arr_out, arr_in);
		}
		if (arr_out[row + 1][col] == 1)
			arr_out[row + 1][col] = 0;

	}

	if (arr_out[row + 1][col + 1] == 1)
	{
		if (arr_in[row + 1][col + 1] == 0 && (outNumber(row + 1, col + 1, arr_out, arr_in) > 0))
		{
			eightzoneSweep(row + 1, col + 1, arr_out, arr_in);
		}
		if (arr_out[row + 1][col + 1] == 1)
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
int outNumber(int row, int col, int** arr_out, int** arr_in)
{
	int num = 0;
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
int Flag_number(int row, int col, int** arr_out)
{
	int i, j;
	int num = 0;
	for (i = row - 1; i < row + 2; i++)
		for (j = col - 1; j < col + 2; j++)
		{

			if (arr_out[i][j] == 2 && (i != row || j != col))
				num++;
		}
	return num;
}
//
//
//
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
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读入用户操作
// 参数说明     无，直接操作全局结构体变量
// 返回参数     无
// 使用示例     
// 备注信息		getchar读走空格？（
//-------------------------------------------------------------------------------------------------------------------
void Get_User_Operatian()
{
	scanf("%d", &Opt.model);
	getchar();
	scanf("%d", &Opt.row);
	getchar();
	scanf("%d", &Opt.col);
}

//
//
//

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     判断游戏的结束与否，是否踩雷
// 参数说明     arr_out为外盘地址，arr_in为内盘地址
// 返回参数     游戏状态
// 使用示例     
// 备注信息		
//-------------------------------------------------------------------------------------------------------------------
int State_judge(int** arr_out, int** arr_in, int mine)
{
	int i, j, num2 = 0, number1 = 0;
	int num = Col * Row;//num为格数
	for (i = 1; i < Row + 1; i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 0 && arr_in[i][j] == 9)
			{
				return -1;//踩雷返回结束标志
			}
			if (arr_out[i][j] == 2 && arr_in[i][j] == 9)
			{
				number1++;
			}
			if (arr_out[i][j] == 0 && arr_in[i][j] != 9)
			{
				num2++;
			}
		}
	if (num2 == (num - mine))
		return 1;//打开的非雷格数已经等于格数减有雷格数，返回游戏胜利标志
	else
		return 0;
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     返回游戏提示的剩余雷数
// 参数说明     arr_out为外盘地址，arr_in为内盘地址，mine为游戏总雷数
// 返回参数     剩余雷数
// 使用示例     
// 备注信息		外部调用
//-------------------------------------------------------------------------------------------------------------------
int Mine_judge(int** arr_out, int** arr_in, int mine)
{
	int i, j, number1 = 0;
	for (i = 1; i < Row + 1; i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 2)
			{
				number1++;
			}
		}
	return mine - number1;
}

//
//
//
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     输出游戏内盘函数
// 参数说明     s-游戏盘头地址
// 返回参数     无
// 使用示例     
// 备注信息		调试用显示内盘函数
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_debugout(int** s)
{
	int i, j;
	for (i = 1; i < Row + 1; i++)
	{
		for (j = 1; j < Col + 1; j++)
		{
			printf("%d ", s[i][j]);
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

void Gameover_print(int state, int Operation_number, int mine, int** arr_out, int** arr_in)
{
	if (state == -1)
	{
		printf("Hit mine, you lose。\n");
	}
	else
	{
		printf("Game over, you win\n");
	}
	printf("%d %d\n", Operation_number, mine);
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