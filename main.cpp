#pragma once
#include "headfile.h"
int Col;//ÁÐ
int Row;//ÐÐ
/****************************************************************
	@Author:zhaofei
	@Mail:zf4869@qq.com
*****************************************************************/
int main()
{
	int** Game_board_in;
	Game_board_in=game_start();
	//printf("%d\n",Game_board[Row+1][Col+1]); 
	Gameboard_debugout(Game_board_in);
	return 0;
}