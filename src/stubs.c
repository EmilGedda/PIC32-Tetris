/* stubs.c
 * This file written 2015 by Axel Isaksson
 * This copyright notice added 2015 by F Lundevall

 * For copyright and licensing, see file COPYING */

/* Non-Maskable Interrupt; something bad likely happened, so hang */

#include "input.h"
#include "display.h"
#include <pic32mx.h>

void _nmi_handler() {
	for (;;) {
		PORTE = 0xFF;
	}

}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
	
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {
	inputinit();
	display_init();

	IEC(0) = 0x100;			/* Interrupt Enable Control */
	IPC(2) = 0b111110100;		/* Interrupt Priority Control */
	TMR2 = 0;			/* Reset Timer Value */
	PR2 = 31250;			/* Set period register */
	T2CON = 0b1000000001110000;	/* Set internal 16-bit timer. Prescaling 1:256 */
	__asm__ volatile("ei");		/* Enable interrupt */	
	
}
