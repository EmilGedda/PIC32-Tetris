#ifndef DISPLAY_H       
#define DISPLAY_H

/* Initializes chipKIT Basic I/O Shield OLED display. */
void display_init(void);

/* Displays a bitmap on OLED display, use for hard coded bitmaps */
void display_bitmap(int x, const char *bmp);

/* Scales game graphics accordingly and displays them on OLED display */
void display_game(char (*arr)[64][16]);

void display_update_text(void);

char* itoaconv(int num); 
#endif
