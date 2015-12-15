/*
 * Score.c handles the scoring-logic behind the scenes
 * lineclears(int) and increment(void) should be called when necessary
 */

#include "score.h"

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
