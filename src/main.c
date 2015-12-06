#include "game.h"
#include <pic32mx.h>
#include "display.h"
#include "random.h"

int main(void)
{
	rseed(0);
	char tmp[16][64];
	display_init();
	display_game(&tmp);
	//run();
}

void user_isr(void)
{
	if (!(IFS(0) & 0x100)) return;	/* Poll time-out event flag */
    	IFS(0) &= ~0x100;		/* Clear IFS */
//	on_tick();
}

