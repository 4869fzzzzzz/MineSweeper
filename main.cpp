#pragma once
#include "headfile.h"
int Col;//��
int Row;//��
int Game_state;//��Ϸ״̬
struct opt Opt;//�û�����

/****************************************************************
	@Author:zhaofei
	@Mail:zf4869@qq.com
*****************************************************************/
int main()
{
	int Operation_number=0;//��������
	int Mine_number=0;
	int Mine_remain = 0;
	Operation_number = 0;
	int** Game_board_in;
	int** Game_board_out;
	Game_board_in=game_board_in_init();
	Game_board_out = game_board_out_init();
	//printf("%d\n",Game_board[Row+1][Col+1]);
	//Gameboard_debugout(Game_board_out);
	Mine_number = Count_mine(Game_board_in);
	Gameboard_debugout(Game_board_in);
	//1 1 9������⣬����һ������-
	//5.7 �����ˣ�op1�Ӽ���û�����꣬Ѫѹ���ˣ������пտ����ع�һ�£��Ӹ�ѭ��������˳��
	while (!Game_state)
	{
		Get_User_Operatian();
		User_Operation(Game_board_out,Game_board_in);
		Mine_remain = Mine_judge(Game_board_out, Game_board_in, Mine_number);
		Operation_number++;
		Game_state=State_judge(Game_board_out, Game_board_in,Mine_number);
		
		//��ӡ��ʾ
		if (Game_state != 0)
			break;
		printf("Game in prograss\n");
		printf("%d %d\n",Operation_number,Mine_remain);
		Gameboard_Print(Game_board_out,Game_board_in);
	}
	//�����������ʾ-������
	printf("ssssssss\n");
	Gameboard_free(Game_board_in);
	Gameboard_free(Game_board_out);
	return 0;
}