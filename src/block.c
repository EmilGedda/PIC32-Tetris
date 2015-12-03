static struct Iblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {0, 0, 0, 0},
                {1, 1, 1, 1}
        };
};

static struct Oblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {0, 1, 1, 0},
                {0, 1, 1, 0}
        };
};

static struct Tblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {0, 1, 0, 0},
                {1, 1, 1, 0}
        };
};

static struct Sblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {0, 1, 1, 0},
                {1, 1, 0, 0}
        };
};

static struct Jblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {1, 0, 0, 0},
                {1, 1, 1, 0}
        };
};

static struct Lblock {
        char dim[4][4] = {  
                {0, 0, 0, 0},
                {0, 0, 0, 0},  
                {0, 0, 1, 0},
                {1, 1, 1, 0}
        };
};
