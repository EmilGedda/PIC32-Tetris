
#include "random.h"
#include "block.h"

void shuffle(struct block (*bag)[7], int size);
void copyarray(char (*from)[4][4], char (*to)[4][4]);

static char dims[7][4][4] = {  
{  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {0, 0, 0, 0},
        {1, 1, 1, 1}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {0, 1, 1, 0},
        {0, 1, 1, 0}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {0, 1, 0, 0},
        {1, 1, 1, 0}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {0, 1, 1, 0},
        {1, 1, 0, 0}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {1, 1, 0, 0},
        {0, 1, 1, 0}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {1, 0, 0, 0},
        {1, 1, 1, 0}
}, {  
        {0, 0, 0, 0},
        {0, 0, 0, 0},  
        {0, 0, 1, 0},
        {1, 1, 1, 0}
}};

struct block *next_block()
{
        static struct block blocks[7];
        static int count = 7;
        static char tmp[7][4][4];

        if (count > 6) {
		for(int i = 0; i < 7; i++){
                	copyarray(&dims[i], blocks[i].dim);
			blocks[i].pos_x = 0;
			blocks[i].pos_y = 0;
		}
	       shuffle(&blocks, 7);	

        }		
        return &blocks[count++];
}

void copyarray(char (*from)[4][4], char (*to)[4][4])
{ 
	for(int i = 0; i < 4; ++i)
        {
        	for(int j = 0; j < 4; ++j)
                {
             		*to[i][j] = *from[i][j];
                }
	}       
}
void shuffle(struct block (*bag)[7], int size)
{
	for(int i = 0; i < 7; i++)
	{
		int j = rand() % (i + 1);
		struct block curr = *bag[i];
		*bag[i] = *bag[j];
		*bag[j] = *bag[i];
	}
}
void move_right(struct block *b)
{
        //TODO: Add validation
        b->pos_x++;
}
void move_left(struct block *b)
{
        //TODO: Add validation
        b->pos_x--;
}

void move_down(struct block *b)
{
        b->pos_y++;
}
