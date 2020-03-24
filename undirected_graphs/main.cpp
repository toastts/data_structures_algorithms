#include <iostream>
#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "point.hpp"

using namespace std;

void edgesVdist(){
    int tests = 100;
    int nVerts = 100; // PLEASE DO NOT RUN THIS AS 100 ON YOUR FIRST RUN DO SOMETHING LIKE 30 OR LESS
    int max_dist = 30; //with box of 20x20, corner distance is 28.something, putting 30 to get that nice asymptote demonstration
    
    double edge_arr[max_dist];
    for(int j = 0; j < max_dist; j++){
        edge_arr[j] = 0;
    }
    
    for(int t = 1; t <= tests; t++) {
            for(int d = 0; d <= max_dist; d ++) {
                //initializes a graph with the min_dist that is currently being tested
                graph tgraph = graph(d);
                for(int i = 0; i < nVerts; i++) {
                    //points are added to the graph, fix_edges() handles connectivity with the adjacency matrix
                    tgraph.addp();
                }
                //we want all of our stuff to be plotted on one chart so we divide by the max number of edges for the given set
                //of vertices so that everything is just a fraction of 1 when it's being plotted
                edge_arr[d] += tgraph.get_nEdges() / ((nVerts * (nVerts - 1)) / 2);
            }
        }
        ofstream ofs;
        ofs.open("./data/eVdist/E" + to_string(nVerts) + ".txt");
        for(int c = 0; c < max_dist; c++) {
            //divides by the total number of tests so that we can get an average for every single time it ran through
            ofs << c << " " << edge_arr[c] / (double) tests << "\n";
        }
        cout << endl;

    }




void pconVdist(int numpoints) {
    int tests = 5; //total number of tests
    int dtests = 50; //tests for infividual dist values
    int max_d = 29; //same max dist as the edge number test
    int nVerts = numpoints; //number of vertices being tested


    double arr[max_d + 1];
    for(int j = 0; j < max_d + 1; j++) {
        arr[j] = 0;
    }

    double conn = 0;
    for(int t = 0; t < tests; t++) {
        for(int d = 0; d < max_d; d ++) {
            conn = 0;
            for(int h = 0; h < dtests; h++) {
                graph tgraph = graph(d);
                for(int i = 0; i < nVerts; i++) {
                    tgraph.addp();
                }
                if(tgraph.connectivity()) {
                    conn++;
                }
            }
            //takes the aggregated times of connectedness over tests ran to get a percent
            arr[d] += conn / (double) dtests;
        }
        cout << "Test " << t+1 << " done" << endl;
    }
    ofstream ofs;
    ofs.open("./data/pconVdist/PC" + to_string(nVerts) + ".txt");
    for(int c = 0; c < max_d + 1; c++) {
        //takes the probability over all of the tests ran to get an average probability of connectedness
        ofs << c << " " << arr[c] / (double) tests << "\n";
    }
    cout << endl;

}



int main(int argc, const char * argv[]) {
    //edgesVdist();
    int numpoints;
    cout << "enter your number of points homie:";
    cin >> numpoints; //made it with user input because i realized how slow and inefficient i was on the first data sampling thing
    pconVdist(numpoints);
    return 0;
}
