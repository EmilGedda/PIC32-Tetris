#include "block.h"
#include "display.h"
#include "board.h"

static char board[16][64];

void _copyarray(char (*from)[16][64], char (*to)[16][64]);
void merge(struct block *blk, char (*b)[16][64]);


void merge_with_board(struct block *blk)
{
	merge(blk, &board);
}

void merge(struct block *blk, char (*b)[16][64])
{
	for (int i = 3; i >= 0; i--) {
		for(int j = 0; j < 4; j++) {
			int global_y = blk->pos_y + i;
			int global_x = blk->pos_x + j;
			if (blk->dim[j][i])
				*b[global_x][global_y] = 1;
		}	
	}
}

void update_board(struct block *blk)
{
	static char tmp[16][64];
	_copyarray(&board, &tmp);
	merge(blk, &tmp);
	display_game(&tmp);
}


char can_move_down(struct block *blk)
{
	for (int i = 3; i >= 0; i--) {
		for(int j = 0; j < 4; j++) {
			int global_y = blk->pos_y + i;
			int global_x = blk->pos_x + j; 
			if (blk->dim[j][i] && board[global_x][global_y+1])
				return 0;
		}
	}
	
	return 1;	
}

void _copyarray(char (*from)[16][64], char (*to)[16][64])
{ 
	for (int i = 0; i < 16; ++i)
        {
        	for (int j = 0; j < 64; ++j)
                {
             		*to[i][j] = *from[i][j];
                }
	}       
}

