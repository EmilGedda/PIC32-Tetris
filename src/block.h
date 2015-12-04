#ifndef BLOCK_H
#define BLOCK_H

struct block {
        int *dim[4][4];
        int pos_x; //top left
        int pos_y; //top left
};

struct block *next_block();
void move_right(struct block *b);
void move_left(struct block *b);
void move_down(struct block *b);

#endif