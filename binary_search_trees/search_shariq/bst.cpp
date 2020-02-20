#include "bst.hpp"
#include <iostream>

using namespace std;

node * bst::search(int key)
{
    node *current = root;
    while (current)
    {
        if (current->data == key)
            break;
        if (key > current->data)
            current = current->right;
        else
            current = current->left;
    }
    return current;
}



void bst::insert(node *root, int key)
{
    
    if (key > root->data)
    {
        if (!root->right)
            root->right = new node(key);
        else
            insert(root->right, key);
    }
    else
    {
        if (!root->left)
            root->left = new node(key);
        else
            insert(root->left, key);
    }
}



void bst::insert(int key)
{
    if (!root){
        root = new node(key);
    }
    else
    {
        this->insert(root, key);
    }
}



node* bst::nextDeletion(node *Node)
{
    // Start with the right node
    node *nextLarger = Node->right;
    
    // Get left node while it's not null
    while (nextLarger->left)
    {
        nextLarger = nextLarger->left;
    }
    
    return nextLarger;
}



bool bst::del(node *parent, node *current, int key)
{
    if (!current)
    {
        return false;
    }
    if (current->data == key)
    {
        if (!current->left && !current->right)
        {
            
            if (parent->right == current)
                parent->right = NULL;
            else
                parent->left = NULL;
            delete current;
            current = NULL;
            return true;
        }
        else if (!current->left || !current->right)
        {
            node *child = current->left;
            if (!child)
                child = current->right;
            
            
            if (!parent)
            {
                this->root = child;
            }
            else
            {
                if (child->data > parent->data)
                    parent->right = child;
                else
                    parent->left = child;
            }
            delete current;
            current = NULL;
        }
        
        else
        {
            
            node *nextLargernode = nextDeletion(current);
            current->data = nextLargernode->data;
            delete nextLargernode;
            nextLargernode = NULL;
        }
        return true;
    }
    
    if (key > current->data){
        return remove(current, current->right, key);
    }else {
        return remove(current, current->left, key);
    }
}



bool bst::del(int value)
{
    return del(NULL, root, value);
}



node* bst::max()
{
    node *max = root;
    while (max->right)
    {
        max = max->right;
    }
    return max;
}




node* bst::min()
{
    node *min = root;
    while (min->left)
    {
        min = min->left;
    }
    return min;
}



node* bst::successor(node* p){
    while(p && p->left!=NULL)
        p=p->left;
    return p;
}



node* bst::predecessor(node* p){
    while(p && p->right!=NULL)
        p=p->right;
    return p;
}



void bst::print(node *root)
{
    if (!root)
        return;
    print(root->left);
    cout<<root->data<<' ';
    print(root->right);
}



void bst::display()
{
    if(!root)
        return;
    print(root);
    cout << endl;
}
