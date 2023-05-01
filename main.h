#pragma once
#define Game_over_lose -1;
#define Game_In_progress 0;
#define Game_over_win 1;
extern int Col;
extern int Row;
extern int Game_state;
extern int Operation_number;
struct opt {
	int model;
	int row, col;
};
extern opt Opt;