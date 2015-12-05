#ifndef BOARD_H
#define BOARD_H

/* Merges the block the internal representation of the board */
void merge_with_board(struct block *blk);

/* Updates the visual view of the board */
void update_board(struct block *blk);

/* Rotates block clockwise  */
void rotate_right(struct block *blk);

/* Rotates block counterclockwise */
void rotate_left(struct block *blk);

/* Returns non zero value if the specified block has space below */
char can_move_down(struct block *blk);

#endif
