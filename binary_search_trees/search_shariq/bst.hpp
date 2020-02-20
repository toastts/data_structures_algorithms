
#ifndef bst_hpp
#define bst_hpp

#include <stdio.h>
#include "node.h"

class bst {
private:
    node* root;
public:
    bst();
    node * search(int);
    void insert(node *, int);
    void insert(int);
    bool del(node *, node *, int);
    bool del(int);
    node* nextDeletion(node *);
    node* min();
    node* max();
    node* successor(node *);
    node* predecessor(node *);
    void print(node* root);
    void display();
    void rotateLeft();
    void rotateRight();
};

#endif /* bst_hpp */
