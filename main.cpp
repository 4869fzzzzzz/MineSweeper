#pragma once
#include "headfile.h"
int Col;//列
int Row;//行
int Game_state;//游戏状态
struct opt Opt;//用户操作

/****************************************************************
	@Author:zhaofei
	@Mail:zf4869@qq.com
*****************************************************************/
int main()
{
	int Operation_number;//操作次数
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