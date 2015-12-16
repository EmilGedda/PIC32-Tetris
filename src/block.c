
#include "random.h"
#include "block.h"

#define NUMBLOCKS 7

void shuffle(struct block (*bag)[NUMBLOCKS]);
void copyarray(char (*from)[4][4], char (*to)[4][4]);

/* Defines all the available blocks */
static char dims[NUMBLOCKS][4][4] = {  
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
        static struct block blocks[NUMBLOCKS];
        static int count = NUMBLOCKS;
        static char tmp[NUMBLOCKS][4][4];

        if (count > 6) {
		for (int i = 0; i < 7; i++){ //Re-init our bag of blocks
                	blocks[i].dim = &dims[i];
			blocks[i].pos_x = 58;
			blocks[i].pos_y = 6;
		}
	       //shuffle(&blocks); // Shuffle the bag
	       count = 0;
        }		

        return &blocks[count++];
}

/* Copies array from to the array to, must be 4x4 arrays */
void copyarray(char (*from)[4][4], char (*to)[4][4])
{ 
	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		(*to)[i][j] = (*from)[i][j];
}

//Shuffles a bag of blocks, Fisher-Yate style
void shuffle(struct block (*bag)[NUMBLOCKS])
{
	for (int i = 0; i < NUMBLOCKS; i++)
	{
		int j = rand() % (i + 1);
		struct block curr = *bag[i];
		*bag[i] = *bag[j];
		*bag[j] = *bag[i];
	}
}

void move_up(struct block *b)
{
        /* TODO: Add validation */
	b->pos_y--;
}

void move_left(struct block *b)
{
        b->pos_x--;
}

void move_down(struct block *b)
{
	b->pos_y++;
}

void transpose(char (*arr)[4][4])
{
        static char tmp[4][4];
        copyarray(arr, &tmp);
        for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
                (*arr)[i][j] = tmp[j][i];
}

void reverse(char (*arr)[4])
{
        int tmp = (*arr)[0];
	(*arr)[0] = (*arr)[3];
	(*arr)[3] = tmp;
	tmp = (*arr)[1];
	(*arr)[1] = (*arr)[2];
	(*arr)[2] = tmp;

}

void rotate_left(struct block *b)
{
	char (*tmp)[4][4] = b->dim;
        transpose(tmp);
	for(int i = 0; i < 4; i++)
		reverse(&((*tmp)[i]));
}

void rotate_right(struct block *b)
{
        for(int i = 0; i < 3; i++)
		rotate_left(b);
}


