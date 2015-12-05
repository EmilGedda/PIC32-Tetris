#include "block.h"
#include "input.h"

void run(void)
{
	struct block *curr = next_block();
	while(true)
	{
		int* inputs = inputloop();
		handle_input(inputs, *curr);
	}
}

void handle_input(int *inputs, struct block *blk)
{
	void (*f[4])(struct block) = {
		rotate_right(blk),
	       	rotate_left(blk),
		move_right(blk),
		move_left(blk)
	}

	for(int i = 0; i < 4; i++)
		if ((*inputs)[i])
			f[i](blk);
}
