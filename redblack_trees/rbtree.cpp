#include "rbtree.hpp"
#include <iostream>


using namespace std;

rbtree::rbtree() {
    root = nullptr;
}

int rbtree::getColor(node *&bruh) {
    if (bruh == nullptr)
        return BLACK;

    return bruh->color;
}

void rbtree::setColor(node *&bruh, int color) {
    if (bruh == nullptr)
        return;

    bruh->color = color;
}

node* rbtree::insertBST(node *&root, node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void rbtree::insertValue(int n) {
    node *bruh = new node(n);
    root = insertBST(root, bruh);
    adjustInsert(bruh);
}

void rbtree::rotateL(node *&ptr) {
    node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void rbtree::rotateR(node *&ptr) {
    node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void rbtree::adjustInsert(node *&ptr) {
    node *parent = nullptr;
    node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateL(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateR(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateR(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateL(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void rbtree::adjustDelete(node *&bruh) {
    if (bruh == nullptr)
        return;

    if (bruh == root) {
        root = nullptr;
        return;
    }

    if (getColor(bruh) == RED || getColor(bruh->left) == RED || getColor(bruh->right) == RED) {
        node *child = bruh->left != nullptr ? bruh->left : bruh->right;

        if (bruh == bruh->parent->left) {
            bruh->parent->left = child;
            if (child != nullptr)
                child->parent = bruh->parent;
            setColor(child, BLACK);
            delete (bruh);
        } else {
            bruh->parent->right = child;
            if (child != nullptr)
                child->parent = bruh->parent;
            setColor(child, BLACK);
            delete (bruh);
        }
    } else {
        node *sib = nullptr;
        node *parent = nullptr;
        node *ptr = bruh;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sib = parent->right;
                if (getColor(sib) == RED) {
                    setColor(sib, BLACK);
                    setColor(parent, RED);
                    rotateL(parent);
                } else {
                    if (getColor(sib->left) == BLACK && getColor(sib->right) == BLACK) {
                        setColor(sib, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sib->right) == BLACK) {
                            setColor(sib->left, BLACK);
                            setColor(sib, RED);
                            rotateR(sib);
                            sib = parent->right;
                        }
                        setColor(sib, parent->color);
                        setColor(parent, BLACK);
                        setColor(sib->right, BLACK);
                        rotateL(parent);
                        break;
                    }
                }
            } else {
                sib = parent->left;
                if (getColor(sib) == RED) {
                    setColor(sib, BLACK);
                    setColor(parent, RED);
                    rotateR(parent);
                } else {
                    if (getColor(sib->left) == BLACK && getColor(sib->right) == BLACK) {
                        setColor(sib, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sib->left) == BLACK) {
                            setColor(sib->right, BLACK);
                            setColor(sib, RED);
                            rotateL(sib);
                            sib = parent->left;
                        }
                        setColor(sib, parent->color);
                        setColor(parent, BLACK);
                        setColor(sib->left, BLACK);
                        rotateR(parent);
                        break;
                    }
                }
            }
        }
        if (bruh == bruh->parent->left)
            bruh->parent->left = nullptr;
        else
            bruh->parent->right = nullptr;
        delete(bruh);
        setColor(root, BLACK);
    }
}

node* rbtree::deleteBST(node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    node *temp = minVal(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

void rbtree::deleteValue(int data) {
    node *bruh = deleteBST(root, data);
    adjustDelete(bruh);
}


node *rbtree::minVal(node *&bruh) {

    node *ptr = bruh;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

node* rbtree::maxVal(node *&bruh) {
    node *ptr = bruh;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int rbtree::bHeight(node *bruh) {
    int blackheight = 0;
    while (bruh != nullptr) {
        if (getColor(bruh) == BLACK)
            blackheight++;
        bruh = bruh->left;
    }
    return blackheight;
}

void rbtree::inOrder(node *root)
{
    if(!root)
        return;
    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
 
}

bool rbtree::isLeaf(node *root)
{
    return !root->left && !root->right?1:0;
}

void rbtree::preorderBST(node *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void rbtree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}
