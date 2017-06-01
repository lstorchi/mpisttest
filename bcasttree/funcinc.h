#ifndef _PRV_INC_BCAST_ 
#define _PRV_INC_BCAST_

void bcast (int myrank, int rootrank, int size, double * sbuf, 
    int bufdim);

void bcast_tree (int myrank, int size, double * sbuf, int bufdim);
#endif
