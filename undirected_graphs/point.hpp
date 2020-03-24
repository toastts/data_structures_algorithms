#ifndef point_hpp
#define point_hpp

#include <cstdlib>
#include <time.h>
#include <random>

using namespace std;

class point {
public:
    double x;
    double y;
    
    point() {
        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_real_distribution<double> distr(0.0, 20.0);
        x = distr(generator);
        y = distr(generator);
    }
    
    point(double xval, double yval){
        x = xval;
        y = yval;
    }
};


#endif
