#include "tnode.h"
#include <climits>

using namespace std;

tnode::tnode(char d, tnode *l, tnode *r) {
    left = l;
    right = r;
    data = d;
};

unsigned int tnode::pre() {
    switch(data) {
        case '&':  
            return 1;
        case '|':  
            return 1;
            break; 
        case '!':  
            return 0;
        case '>':
            return 2;
        case '^':
            return 1;
        case 'T':
            return -1;
        case 'F':
            return -1;
        default:
            return INT_MIN;
    }
};

bool tnode::eval() {
    switch (data) { 
        case '&':  
            return left -> eval() && right -> eval();
        case '|':  
            return left -> eval() || right -> eval();
            break; 
        case '!':  
            return !(left -> eval());
        case '>':
            return !(left -> eval()) || right -> eval();
        case '^':
            return (left -> eval() || right -> eval()) && (!(left -> eval()) && right -> eval());
        case 'T':
            return true;
        case 'F':
            return false;
        default:
            return false;
    }
};

bool tnode::isbool() { 
    if(data == 'T' || data == 'F') {
        return true;
    } else {
        return false;
    }
};

tnode::~tnode() {
    if(left != nullptr) {
        delete(left);
    }
    if(right != nullptr) {
        delete(right);
    }
};


tnode::tnode(char d) {
    data = d;
    left = nullptr;
    right = nullptr;
};