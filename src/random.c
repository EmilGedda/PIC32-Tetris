/*
 * Random.c returns a pseudo-random number according 
 * to the POSIX formula for a linear congruential generator
 * Since we only need very basic randomness we mod with 2^32
 * instead 
 */

#include "random.h"

static int state = 0;

void seed(int seed)
{
        state = seed;
}

int next(void)
{
        return state = (0x5DEECE66D * state + 11) & 2147483647;
}
