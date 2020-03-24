#ifndef graph_hpp
#define graph_hpp

#include <vector>
#include <iostream>
#include <math.h>
#include "point.hpp"

class graph {
private:
    double min_dist;
    vector<vector<int> > *adjmat;
    vector<point> *vertices;
    double nEdges;
    vector<bool> *helper_checker;
    int n;
public:
    graph(double d);
    double get_nEdges();
    void addp();
    void fix_adjacency(double d);
    void dfirstSearch(int x);
    bool connectivity();
};

#endif
