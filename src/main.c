#include "game.h"
#include <pic32mx.h>
#include "random.h"

int main(void)
{
	rseed(1337);
	run();
}

void user_isr(void)
{
	if (!(IFS(0) & 0x100)) return;	/* Poll time-out event flag */
    	IFS(0) &= ~0x100;		/* Clear IFS */
	on_tick();
}

