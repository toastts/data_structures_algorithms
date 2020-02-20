#ifndef TNODE_H_
#define TNODE_H_


class tnode {
    public:
        tnode(char d, tnode *l, tnode *r);
        tnode(char d);
        tnode* left;
        tnode* right;
        bool eval();
        char data;
        unsigned int pre();
        bool isbool();
        ~tnode();
};

#endif