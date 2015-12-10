#include "block.h"
#include "input.h"
#include "board.h"
#include <pic32mx.h>
#include "random.h"
static struct block *curr; 
void handle_input(int *inputs, struct block *blk);

static void (*f[4])(struct block *blk) = {
		rotate_right,
		rotate_left,
		move_down,
		move_up
};

void run(void)
{
	curr = next_block(); 
	TRISESET = ~0xFF;
	
	for(;;)
	{
		int inputs[4];
		inputloop(inputs);
		handle_input(inputs, curr);
	}
}

void handle_input(int *inputs, struct block *blk)
{
	for(int i = 0; i < 4; i++) {
		if (inputs[i]) {
			//f[i](blk);
			move_down(blk);
		}
	}
}

void on_tick()
{
	static int cnt = 0;
	if (can_move_left(curr)) {
		move_left(curr);
//		move_down(curr);
	} else {
		merge_with_board(curr);
		curr = next_block();
	}
	update_board(curr);
	
	PORTE = ++cnt;
	
}
