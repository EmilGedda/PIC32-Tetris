#include "block.h"
#include "display.h"
#include "board.h"

static char board[64][16];

void _copyarray(char (*from)[16], char (*to)[16]);
void merge(struct block *blk, char (*b)[16]);


void merge_with_board(struct block *blk)
{
	merge(blk, board);
}

void merge(struct block *blk, char (*b)[16])
{
	for (int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			int global_x = blk->pos_x + i;
			int global_y = blk->pos_y + j;
			if (blk->dim[i][j])
				b[global_x][global_y] = 1;
		}	
	}
}

void update_board(struct block *blk)
{
	static char tmp[64][16];
	_copyarray(board, tmp);
	merge(blk, tmp);
	display_game(tmp);
}


char can_move_left(struct block *blk)
{
	if (blk->pos_x <= 0) return 0;

	for (int i = 0; i < 4; i++) {
		int global_x = blk->pos_x; 
		if (blk->dim[0][i] && board[global_x][i])
			return 0;
	}
	
	return 1;	
}

void _copyarray(char (*from)[16], char (*to)[16])
{ 
	for (int i = 0; i < 64; ++i)
        {
        	for (int j = 0; j < 16; ++j)
                {
             		to[i][j] = from[i][j];
                }
	}       
}

