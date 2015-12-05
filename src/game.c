#include "block.h"
#include "input.h"
#include "board.h"

static struct block *curr; 

static const void (*f[4])(struct block) = {
		rotate_right(blk),
		rotate_left(blk),
		move_right(blk),
		move_left(blk)
}

void run(void)
{
	curr = next_block(); 
	while(true)
	{
		int* inputs = inputloop();
		handle_input(inputs, curr);
	}
}

void handle_input(int *inputs, struct block *blk)
{
	for(int i = 0; i < 4; i++)
		if ((*inputs)[i])
			f[i](blk);
}

void on_tick()
{
	if (can_move_down(curr)) {
		move_down(curr);
	} else {
		merge_board(curr);
		curr = next_block();
	}
}
