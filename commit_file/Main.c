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
int Col;//��
int Row;//��
int Game_state;//��Ϸ״̬
struct opt Opt;//�û�����
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
	int Operation_number = 0;//��������
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
	//1 1 9������⣬����һ������-
	//5.7 �����ˣ�op1�Ӽ���û�����꣬Ѫѹ���ˣ������пտ����ع�һ�£��Ӹ�ѭ��������˳��
	//˫���ƺ����ܴ򿪺����������Ҫ��ǰ��һ���ж�
	//��Ϸģʽ�����䣬�������ˣ��Ͳ�һЩ��������ˣ���Χȫ�Ǳ�ǵ�0��
	//�����ֱ�Ӳ��������ĸ��оݾ�ok�ˣ��ƺ�ûʲô������
	while (!Game_state)
	{
		Get_User_Operatian();
		User_Operation(Game_board_out, Game_board_in);
		Mine_remain = Mine_judge(Game_board_out, Game_board_in, Mine_number);
		Operation_number++;
		Game_state = State_judge(Game_board_out, Game_board_in, Mine_number);

		//��ӡ��ʾ
		if (Game_state != 0)
			break;
		printf("Game in prograss\n");
		printf("%d %d\n", Operation_number, Mine_remain);
		Gameboard_Print(Game_board_out, Game_board_in);
	}
	//�����������ʾ
	Gameover_print(Game_state, Operation_number, Mine_remain, Game_board_out, Game_board_in);
	Gameboard_free(Game_board_in);
	Gameboard_free(Game_board_out);
	return 0;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��Ϸ��ʶ����������
// ����˵��     
// ���ز���     ���ش����õ���Ϸ�̵�����ַ
// ʹ��ʾ��     
// ��ע��Ϣ		ֻ����Ϸ���̣����̶��ⴴ��
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
// �������     ��Ϸ�̵Ľ���
// ����˵��     ��
// ���ز���     ��ά��̬�����ͷ��ַ
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ���̳�ʶ��
// ����˵��     arr-��������ָ��
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ��Ԫ������ͳ��
// ����˵��     s-����ͷ��ַ��row��������col������
// ���ز���     �ø�8�����ڵ�����
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ��Ϸ���̵Ľ���
// ����˵��     ��
// ���ز���     ��ά��̬�����ͷ��ַ
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ������Ϸ������
// ����˵��     arr��Ϸ���̵�ַ
// ���ز���     ��Ϸ������
// ʹ��ʾ��     
// ��ע��Ϣ		������Ϸʤ�����ж�
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
// �������     ��Ϸ���̵Ľ���
// ����˵��     ��
// ���ز���     ��ά��̬�����ͷ��ַ
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ������Ϸ�������ͷ��ڴ�
// ����˵��     sΪ���ͷ��ڴ�ͷ��ַ
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		�ƺ����е�����
//-------------------------------------------------------------------------------------------------------------------
void Gameboard_free(int** s)
{
	int i;
	for (i = 0; i < Row + 2; i++)
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
// �������     ����ĳ����Χδ�򿪵ĸ���
// ����˵��     row-�У�col-�У�arr_out-���̣�arr_in-����
// ���ز���     ��Χδ�򿪸���
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     �ж���Χ��������
// ����˵��     row�У�col�У�arr_out����
// ���ز���     ������
// ʹ��ʾ��     
// ��ע��Ϣ		�ڲ�����
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
// �������     ��Ϸ��������������
// ����˵��     s-��Ϸ����ͷ��ַ
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		���������λ�ã�����������
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
// �������     �����û�����
// ����˵��     �ޣ�ֱ�Ӳ���ȫ�ֽṹ�����
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		getchar���߿ո񣿣�
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
// �������     �ж���Ϸ�Ľ�������Ƿ����
// ����˵��     arr_outΪ���̵�ַ��arr_inΪ���̵�ַ
// ���ز���     ��Ϸ״̬
// ʹ��ʾ��     
// ��ע��Ϣ		
//-------------------------------------------------------------------------------------------------------------------
int State_judge(int** arr_out, int** arr_in, int mine)
{
	int i, j, num2 = 0, number1 = 0;
	int num = Col * Row;//numΪ����
	for (i = 1; i < Row + 1; i++)
		for (j = 1; j < Col + 1; j++)
		{
			if (arr_out[i][j] == 0 && arr_in[i][j] == 9)
			{
				return -1;//���׷��ؽ�����־
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
		return 1;//�򿪵ķ��׸����Ѿ����ڸ��������׸�����������Ϸʤ����־
	else
		return 0;
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ������Ϸ��ʾ��ʣ������
// ����˵��     arr_outΪ���̵�ַ��arr_inΪ���̵�ַ��mineΪ��Ϸ������
// ���ز���     ʣ������
// ʹ��ʾ��     
// ��ע��Ϣ		�ⲿ����
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
// �������     �����Ϸ���̺���
// ����˵��     s-��Ϸ��ͷ��ַ
// ���ز���     ��
// ʹ��ʾ��     
// ��ע��Ϣ		��������ʾ���̺���
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
		printf("Hit mine, you lose��\n");
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