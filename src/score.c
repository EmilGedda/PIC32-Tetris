/*
 * Score.c handles the scoring-logic behind the scenes
 * lineclears(int) and increment(void) should be called when necessary
 */

#include "score.h"
#include "display.h"
#include <pic32mx.h>

static int level = 0;
static int score = 0;

int pointsperline(int amnt)
{
        switch(amnt)
        {
        case 2:
                return 100;
        case 3:
                return 300;
        case 4:      
                return 1200;  
        case 1:
                return 40;
	case 0:
		return 0;
        }
}

int lineclears(int nums)
{
        score += pointsperline(nums) * (level + 1);
}

void exit_game()
{
	IEC(0) = ~0xFFFF;
	display_string(0, "                ");
	display_string(1, "   Game Over    "); 

	char str[16] = "  Score: ";
	char *scr = itoaconv(score);
	for(int i = 9; *scr; str[i] = *scr++, i++);
	display_string(2, str);
						
	display_update_text();	
	for(;;);
}

int getScore(void)
{
        return score;
}

int getLevel(void)
{
        return level;
}

void incrementLevel(void)
{
        level++;
}
