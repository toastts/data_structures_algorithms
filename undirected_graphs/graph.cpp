#include "graph.hpp"

using namespace std;

graph::graph(double d){
    n = 0;
    vertices = new vector<point>();
    adjmat = new vector<vector<int> >();
    min_dist = d;
    nEdges = 0;
    helper_checker = new vector<bool>();
}

double graph::get_nEdges(){
    return nEdges;
}

void graph::addp(){
    vertices -> push_back(point());
    n++;
    helper_checker -> push_back(false);
    vector<int> x;
    for(int i = 0; i < n; i++) {
        x.push_back(0);
    }
    adjmat = new vector<vector<int> >();
    for(int j = 0; j < n; j++) {
        adjmat -> push_back(x);
    }
    fix_adjacency(min_dist);
}

void graph::fix_adjacency(double d){
    nEdges = 0;
    int a = 0;
    int b = 0;
    for(auto i = adjmat -> begin(); i != adjmat -> end(); i++) {
        b = 0;
        for(auto j = i -> begin(); j != i -> end(); j++) {
            if(a != b) {
                double x1 = (vertices -> at(a)).x;
                double x2 = (vertices -> at(b)).x;
                double y1 = (vertices -> at(a)).y;
                double y2 = (vertices -> at(b)).y;
                if(pow(pow(y2 - y1, 2) + pow(x2 - x1, 2), 0.5) <= d) {
                    *j = 1;
                    nEdges++;
                } else {
                    *j = 0;
                }
            }
            ++b;
        }
        ++a;
    }
    nEdges = nEdges / 2.0;
}

void graph::dfirstSearch(int x) {
    helper_checker -> at(x) = true;
    vector<int> lis = adjmat -> at(x);
    int j = 0;
    for(auto i = lis.begin(); i != lis.end(); i++) {
        if(*i == 1) {
            if(!(helper_checker -> at(j))) {
                dfirstSearch(j);
            }
        }
        j++;
    }
}

bool graph::connectivity() {
    for(auto i = helper_checker -> begin(); i != helper_checker -> end(); i++) {
        *i = false;
    }
    dfirstSearch(0);
    bool connected = true;
    for(auto j = helper_checker -> begin(); j != helper_checker -> end(); j++) {
        if(!*j) {
            connected = false;
        }
    }
    return connected;
}
