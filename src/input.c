/*
 * input.c handles all input including buttons
 * used for controlling the game.
 *
 * Buttons 1-4 on the chipKIT Basic I/O Shield:
 * BTN   PIN     PIC32sign Bitrange
 * 1     4       RF1       17/1
 * 2     34      RD5       21/5
 * 3     36      RD6       22/6
 * 4     37      RD7       23/7
 */

#include "input.h"
#include "pic32mx.h"

#define COOLDOWN 1000

struct button {
        int cooldown;
        int (*port)(int);
        int shift;
};

/* Note how BTN1 uses a different port than 2, 3, and 4 and thus requires a separate function */
int get_portf(int shift) {
        return (PORTF >> shift) & 1;
}

int get_portd(int shift) {
        return (PORTD >> shift) & 1;
}

static struct button buttons[4];

/* Initialises button structs for each button and configures the
 * relevant I/O port pins as inputs. */
void inputinit(void)
{
        /* TRISx: Data Direction register for the module x */
        TRISFSET = 0x1;  /* BTN1 */
        TRISDSET = 0x70; /* BTN2, BTN3, and BTN4 */

        /* Create struct for BTN 1 */
        struct button btn_one = {
                .cooldown = COOLDOWN,
                .port = &get_portf,
                .shift = 1
        };
        buttons[0] = btn_one;

        /* Create struct for BTN1, BTN2, and BTN3 */
        for (int i = 1; i < 4; i++) {
                struct button btn = {
                        .cooldown = COOLDOWN,
                        .port = &get_portd,
                        .shift = i+4
                };
                buttons[i] = btn;
        }
}

int* inputloop(void)
{
        int arr[4];
        for (int i = 0; i < sizeof(buttons); i++) {
                struct button btn = buttons[i];
                int ispressed = btn.port(btn.shift);
                btn.cooldown = !btn.cooldown && ispressed ? 
                        COOLDOWN : btn.cooldown - 1;              
                arr[i] = ispressed;
        }
        return arr;
}
