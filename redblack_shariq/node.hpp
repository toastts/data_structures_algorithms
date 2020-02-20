#ifndef node_h /* node_h */
#define node_h /* node_h */

#include <cstdlib>

using namespace std;

enum Color {RED, BLACK, DOUBLE_BLACK};

struct node {
    int data, color;
    node *left, *right, *parent;
    
    
    node(int value)
    {
        this->data = value;
        this->right = NULL;
        this->left = NULL;
        this->parent = NULL;
        this->color = RED;
    }
};

#endif /* node_h */