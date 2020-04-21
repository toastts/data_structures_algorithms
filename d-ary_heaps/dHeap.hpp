#ifndef DHEAP_H
#define DHEAP_H

#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <locale>
#include <queue>
#include <vector>
#include <cmath>
#include <utility>
#include <functional>
#include <algorithm>
#include <limits>
#include <list>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <unistd.h>
#include <time.h>
#include <random>
#include <array>

using namespace std;

class dheap {
private:
    vector<int> vecHeap;
    int d;
    void siftUp(int);
    void siftDown(int, int);
    int first(int);
    int last(int);
    int parent(int);
public:
    dheap(vector<int>, int);
    dheap(int);
    vector<int> getHeap();
    int getMin();
    bool empty();
    void insert(int);
    void pop();
    void printHeap();
    void dump();
    int getSize();
};

#endif /* DHEAP_H_ */
