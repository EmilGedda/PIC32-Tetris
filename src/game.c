#include "block.h"
#include "input.h"
#include "board.h"
#include <pic32mx.h>
#include "random.h"
static struct block *curr; 
void handle_input(int *inputs);

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
	int inputs[4];
	for(;;)
	{
		inputloop(inputs);
		handle_input(inputs);
	}
}

void handle_input(int *inputs)
{
	char set = 0;
	for(int i = 0; i < 4; i++) {
		if (inputs[i]) {
			f[i](curr);
			set = 1;
		}
	}
	if(set)
		update_board(curr);
}

void on_tick()
{
	static int cnt = 0;
	if (can_move_left(curr)) {
		move_left(curr);
	} else {
		merge_with_board(curr);
		curr = next_block();
		if(!can_move_left(curr))
			exit_game();
	}
	update_board(curr);
	
	PORTE = ++cnt;
	
}
