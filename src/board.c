#include "block.c"
#include "display.h"
#include "board.h"

static char[16][64] board;
void copyarray(char (*from)[4][4], char (*to)[4][4]);

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
			*b[global_x][global_y] |= blk->dim[j][i];
		}
	}
}

void update_board(struct block *blk)
{
	static char tmp[16][64];
	copyarray(&board, &tmp);
	merge(blk, &tmp);
	display_game(&tmp);
}


char can_move_down(struct block *blk)
{
	char[4][4] blkdims = blk->dim;

	for (int i = 3; i >= 0; i--) {
		for(int j = 0; j < 4; j++) {
			int global_y = blk->pos_y + i;
			int global_x = blk->pos_x + j; 
			if (blkdims[j][i] && board[global_x][global_y+1])
				return 0;
		}
	}
	
	return 1;	
}

void copyarray(char (*from)[16][64], char (*to)[16][64])
{ 
	for (int i = 0; i < 16; ++i)
        {
        	for (int j = 0; j < 64; ++j)
                {
             		*to[i][j] = *from[i][j];
                }
	}       
}

