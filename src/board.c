#include "block.h"
#include "score.h"
#include "display.h"
#include "board.h"

static char board[64][16];

void _copyarray(char (*from)[64][16], char (*to)[64][16]);
void merge(struct block *blk, char (*b)[64][16]);


void merge_with_board(struct block *blk)
{
	merge(blk, &board);
	check_lineclears();
}

void merge(struct block *blk, char (*b)[64][16])
{
	char (*tmp)[4][4] = blk->dim;

	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++) {
		int global_x = blk->pos_x + i;
		int global_y = blk->pos_y + j;
		(*b)[global_x][global_y] |= (*tmp)[i][j];	
	}
}

void update_board(struct block *blk)
{
	static char tmp[64][16];
	_copyarray(&board, &tmp);
	merge(blk, &tmp);
	display_game(&tmp);
}

void shift_board_left(int column)
{
	for (int i = column; i < 64; i++)
	for (int j = 0; j < 16; j++) 
		board[i][j] = (i+1) < 64 ? board[i+1][j] : 0;
}

void check_lineclears(void)
{
	int lines = 0;
	for (int i = 0; i < 64; i++) {
		char full = 1;
		for (int j = 0; j < 16; j++) 
			full &= board[i][j];
		if (full) { 
			shift_board_left(i--);
			lines++;
		}
	}
	lineclears(lines); /* Update score */
}
char can_move_left(struct block *blk)
{
	int global_x = blk->pos_x;
	int global_y = blk->pos_y;
	char (*tmp)[4][4] = blk->dim;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if((*tmp)[j][i] && (board[global_x + j - 1][global_y + i] || ((global_x + j) <= 0)))
				return 0;
		}
	}
	
	return 1;	
}

void try_move_up(struct block *blk)
{
	int global_x = blk->pos_x;
	int global_y = blk->pos_y;
	char (*tmp)[4][4] = blk->dim;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((*tmp)[j][i] && global_y + i <= 0) 
				return;  
			if ((*tmp)[j][i] && board[global_x + j][global_y + i + 1])
				return;
		}
	}
	move_up(blk);	
}

void try_move_down(struct block *blk)
{
	int global_x = blk->pos_x;
	int global_y = blk->pos_y;
	char (*tmp)[4][4] = blk->dim;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((*tmp)[j][i] && global_y + i + 1 > 15) 
				return;  
			if ((*tmp)[j][i] && board[global_x + j][global_y + i + 1])
				return;
		}
	}
	move_down(blk);	
}

void _copyarray(char (*from)[64][16], char (*to)[64][16])
{ 
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 16; ++j) {
			(*to)[i][j] = (*from)[i][j];
		}
	}
}

