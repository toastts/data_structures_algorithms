#ifndef RBTREE_H
#define RBTREE_H

#include "node.hpp"
#include <cstdlib>
#include <utility>

class rbtree
{
    private:
        node *root;
    public:
        void rotateL(node *&);
        void rotateR(node *&);
        void adjustInsert(node *&);
        void adjustDelete(node *&);
        int getColor(node *&);
        void setColor(node *&, int);
        node *minVal(node *&);
        node *maxVal(node *&);
        node* insertBST(node *&, node *&);
        node* deleteBST(node *&, int);
        int bHeight(node *);
        rbtree();
        void insertValue(int);
        void deleteValue(int);
        void inOrder(node *bruh);
        bool isLeaf(node *bruh);
        void preorderBST(node *&);
        void preorder();

    };


#endif