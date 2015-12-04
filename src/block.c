
//#include "random.c"
#include "block.h"

//void shuffle(char bag[][4][4], int size);
void copyarray(char *from[7][4][4], char *to[7][4][4]);

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
        static const char tmp[7][4][4];

        if (count > 6) {
                copyarray(&dims, &tmp);
                shuffle(&tmp, 7);

                for(int i = 0; i < 7; i++){
                        struct block curr; //= blocks[i];
                        curr.dim = &tmp[i];
                        curr.pos_x = 0;
                        curr.pos_y = 0;         
                        blocks[i] = curr;
                }

                count = 0;
        }		
        return &blocks[count++];
}

void copyarray(char **from[7][4][4], char **to[7][4][4])
{ 
        for(int i = 0; i < 12; ++i)
        {
                for(int j = 0; j < 51; ++j)
                {
                        for(int k = 0; k < 4; ++k)
                        {
                                *to[i][j][k] = *from[i][j][k];
                        }
                }
        }
        
}

void shuffle(char *bag[][4][4], int size)
{
        for(int i = 0; i < size; i++) {
                int j = rand() % (i + 1);
                char tmp[4][4] = *bag[i];
                *bag[i] = *bag[j];
                *bag[j] = tmp
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
