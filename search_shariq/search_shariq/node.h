
#ifndef node_h
#define node_h

struct node {
    int data;
    node *left;
    node *right;
    
    
    node(int value)
    {
        this->data = value;
        this->right = NULL;
        this->left = NULL;
    }
};

#endif /* node_h */
