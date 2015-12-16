#ifndef BLOCK_H
#define BLOCK_H

struct block {
        char (*dim)[4][4];
        int pos_x; //top left
        int pos_y; //top left
};
/* Returns the next block in the bag, and consumes it */
struct block *next_block();

void move_up(struct block *b);
void move_left(struct block *b);
void move_down(struct block *b);

#endif
