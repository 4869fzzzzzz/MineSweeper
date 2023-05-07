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
	int Operation_number=0;//操作次数
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
	//1 1 9会出问题，待进一步测试-
	//5.7 改完了，op1加减号没都换完，血压高了，另外有空可以重构一下，加个循环看起来顺眼
	while (!Game_state)
	{
		Get_User_Operatian();
		User_Operation(Game_board_out,Game_board_in);
		Mine_remain = Mine_judge(Game_board_out, Game_board_in, Mine_number);
		Operation_number++;
		Game_state=State_judge(Game_board_out, Game_board_in,Mine_number);
		
		//打印提示
		if (Game_state != 0)
			break;
		printf("Game in prograss\n");
		printf("%d %d\n",Operation_number,Mine_remain);
		Gameboard_Print(Game_board_out,Game_board_in);
	}
	//输出结束后提示-待补充
	printf("ssssssss\n");
	Gameboard_free(Game_board_in);
	Gameboard_free(Game_board_out);
	return 0;
}