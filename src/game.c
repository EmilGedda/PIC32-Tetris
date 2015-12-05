#include "block.h"
#include "input.h"
#include "board.h"

static struct block *curr; 
void handle_input(int *inputs, struct block *blk);

static void (*f[4])(struct block *blk) = {
		rotate_right,
		rotate_left,
		move_right,
		move_left
};

void run(void)
{
	curr = next_block(); 
	for(;;)
	{
		int *inputs = inputloop();
		handle_input(inputs, curr);
	}
}

void handle_input(int *inputs, struct block *blk)
{
	for(int i = 0; i < 4; i++)
		if (inputs[i])
			f[i](blk);
}

void on_tick()
{
	if (can_move_down(curr)) {
		move_down(curr);
	} else {
		merge_with_board(curr);
		curr = next_block();
	}
	update_board(curr);
}
