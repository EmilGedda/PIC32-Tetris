#ifndef DISPLAY_H       
#define DISPLAY_H

/* Initializes chipKIT Basic I/O Shield OLED display. */
void display_init(void);

/* Displays a bitmap on OLED display, use for hard coded bitmaps */
void display_bitmap(const char *bmp);

/* Scales game graphics accordingly and displays them on OLED display */
void display_game(char *arr);

#endif
