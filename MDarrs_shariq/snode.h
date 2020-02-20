#ifndef SNODE_H_
#define SNODE_H_

struct snode {
    float data;
    unsigned int col;
    snode *next;
};


#endif