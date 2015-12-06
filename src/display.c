/* Insert comment about file display.c here */

#include <stdint.h>
#include <pic32mx.h>
#include "font.h"
#include "display.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define ITOA_BUFSIZ 24

char textbuffer[4][16];

uint8_t spi_send_recv(uint8_t data) {
        while (!(SPI2STAT & 0x08));	/* SPI Transmit Buffer Empty Status bit, 1 = empty */
        SPI2BUF = data;			/* SPI Transmit and Receive Buffer Register */
        while (!(SPI2STAT & 1));	/* SPI Receive Buffer Full Status bit, 1 = full, */
        return SPI2BUF;  	     	/* cleared when SPI2BUF is written to */
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

	/* display_init */
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        sleep(10);
        DISPLAY_ACTIVATE_VDD;
        sleep(10000000);
        
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

void display_update(char (*bmp)[128][4]) {
        int c;
        for (int i = 0; i < 4; i++) {
                DISPLAY_CHANGE_TO_COMMAND_MODE;

                spi_send_recv(0x22);
                spi_send_recv(i);
                
                spi_send_recv(0x0);
                spi_send_recv(0x10);
                
                DISPLAY_CHANGE_TO_DATA_MODE;
                
                for (int j = 0; j < 128; j++) {
			spi_send_recv((*bmp)[j][i]);
                }
        }
}

void scale_array(char (*bmp)[64][16], char (*scaledbmp)[128][32]) {
        for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 32; j++) {
                        (*scaledbmp)[i][j] = (*bmp)[i/2][j/2];
                }
        }
}

void to_bitmap(char (*bmp)[128][4], char (*in)[128][32])
{
	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 4; j++) {
			char x;
			for (int k = 0; k < 8; k++) {
				x = (x << 1) | (*in)[i][k+j*8];
			}
			(*bmp)[i][j] = x;
		}
	}
}

void display_string(int line, char *s) {
        if (line < 0 || line >= 4 || !s) return;
        
        for (int i = 0; i < 16; i++)
                if (*s) {
                        textbuffer[line][i] = *s;
                        s++;
                } else {
                        textbuffer[line][i] = ' ';
                }
}

void display_game(char (*arr)[64][16]) {
	char scaledbmp[128][32];
	char bmp[128][4];
      	scale_array(arr, &scaledbmp);
	to_bitmap(&bmp, &scaledbmp);
	display_update(&bmp);
}

char* itoaconv(int num) {
        register int i, sign;
        static char itoa_buffer[ITOA_BUFSIZ];
        static const char maxneg[] = "-2147483648";

        itoa_buffer[ITOA_BUFSIZ - 1] = 0;   /* Insert the end-of-string marker. */
        sign = num;                         /* Save sign. */
        if (num < 0 && num - 1 > 0) {       /* Check for most negative integer */
                for (i = 0; i < sizeof(maxneg); i += 1)
                        itoa_buffer[i + 1] = maxneg[i];
                i = 0;
        } else {
                if (num < 0) num = -num;            /* Make number positive. */
                        i = ITOA_BUFSIZ - 2;        /* Location for first ASCII digit. */
                do {
                        itoa_buffer[i] = num % 10 + '0';        /* Insert next digit. */
                        num = num / 10;                         /* Remove digit from number. */
                        i -= 1;                                 /* Move index to next empty position. */
                } while (num > 0);
                        if (sign < 0) {
                                itoa_buffer[i] = '-';
                                i -= 1;
                        }
        }
        /* Since the loop always sets the index i to the next empty position,
         * we must add 1 in order to return a pointer to the first occupied position. */
        return(&itoa_buffer[ i + 1 ]);
}
