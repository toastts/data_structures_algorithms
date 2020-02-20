 // Driver Program for Red Black Tree

#include <iostream>
#include "rbtree.hpp"

using namespace std;

int main() {
    int data;
    rbtree rbTree1;

    cin >> data;
    while (data != 0)
    {
        rbTree1.insertValue(data);
        cin >> data;
    }

    rbTree1.preorder();

    return 0;
}
 