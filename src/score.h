#ifndef SCORE_H
#define SCORE_H

/*
 * Should be called whenever a line clear happens, 
 * with the parameter nums set to the amount of rows cleared 
 */
int lineclears(int nums);

/* Returns the current score */
int getScore(void);

/* Increments the current (score-)level by one */
void incrementLevel(void);

/* Returns the current level */
int getLevel(void);

#endif