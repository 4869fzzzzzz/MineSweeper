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
	int Operation_number;//��������
	Operation_number = 0;
	int** Game_board_in;
	int** Game_board_out;
	Game_board_in=game_board_in_init();
	Game_board_out = game_board_out_init();
	//printf("%d\n",Game_board[Row+1][Col+1]);
	/*Gameboard_debugout(Game_board_out);
	Gameboard_debugout(Game_board_in);*/
	while (!Game_state)
	{
		Get_User_Operatian();
		User_Operation(Game_board_out,Game_board_out);
		//State_judge(Game_board_out, Game_board_in);
		Operation_number++;
		Gameboard_Print(Game_board_out,Game_board_in);
		
	}
	
	Gameboard_free(Game_board_in);
	Gameboard_free(Game_board_out);
	return 0;
}