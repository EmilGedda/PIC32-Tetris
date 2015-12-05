/* Insert comment about file display.c here */

#include "display.h"
#include <stdint.h>
#include <pic32mx.h>

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

uint8_t spi_send_recv(uint8_t data) {
        while (!(SPI2STAT & 0x08));
                SPI2BUF = data;
        while (!(SPI2STAT & 1));
                return SPI2BUF;
}

void sleep(int cyc) {
        int i;
        for (i = cyc; i > 0; i--);
}

void display_init(void) {
        /* Set up peripheral bus clock */
        /* OSCCONbits.PBDIV = 1; */
        OSCCONCLR = 0x100000; /* clear PBDIV bit 1 */
        OSCCONSET = 0x080000; /* set PBDIV bit 0 */

        /* Set up output pins */
        AD1PCFG = 0xFFFF;
        ODCE = 0x0;
        TRISECLR = 0xFF;
        PORTE = 0x0;

        /* Output pins for display signals */
        PORTF = 0xFFFF;
        PORTG = (1 << 9);
        ODCF = 0x0;
        ODCG = 0x0;
        TRISFCLR = 0x70;
        TRISGCLR = 0x200;

        /* Set up input pins */
        TRISDSET = (1 << 8);
        TRISFSET = (1 << 1);

        /* Set up SPI as master */
        SPI2CON = 0;
        SPI2BRG = 4;
        /* SPI2STAT bit SPIROV = 0; */
        SPI2STATCLR = 0x40;
        /* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
        /* SPI2CON bit MSTEN = 1; */
        SPI2CONSET = 0x20;
        /* SPI2CON bit ON = 1; */
        SPI2CONSET = 0x8000;

        DISPLAY_CHANGE_TO_COMMAND_MODE;
        sleep(10);
        DISPLAY_ACTIVATE_VDD;
        sleep(1000000);
        
        spi_send_recv(0xAE);
        DISPLAY_ACTIVATE_RESET;
        sleep(10);
        DISPLAY_DO_NOT_RESET;
        sleep(10);
        
        spi_send_recv(0x8D);
        spi_send_recv(0x14);
        
        spi_send_recv(0xD9);
        spi_send_recv(0xF1);
        
        DISPLAY_ACTIVATE_VBAT;
        sleep(10000000);
        
        spi_send_recv(0xA1);
        spi_send_recv(0xC8);
        
        spi_send_recv(0xDA);
        spi_send_recv(0x20);
        
        spi_send_recv(0xAF);
}
