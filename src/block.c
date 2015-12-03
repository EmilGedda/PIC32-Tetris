#include "stdlib.h"
#include "random.c"

#define BLOCKSIZE 4

static char dims[7][BLOCKSIZE][BLOCKSIZE] = {  
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

struct block {
        int dim[BLOCKSIZE][BLOCKSIZE];
        int pos_x; //top left
        int pos_y; //top left
};

struct *block next_block()
{
        static int count = 7;

        if (count > 6) {
                shuffle(dims, 7);
                count = 0;
        }

        struct block *current = malloc(sizeof(struct block));

        *current = (struct block) {
                .dim = dims[count++];
        };

        return current;
}

void shuffle(char ***bag, int size)
{
        for(int i = 0; i < size; i++) {
                j = next() % (i + 1);
                swap(bag, i, j);
        }
}

void swap(char ***bag, int i, int j)
{
        struct block tmp = bag[i];
        bag[i] = bag[j];
        bag[j] = tmp;
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
