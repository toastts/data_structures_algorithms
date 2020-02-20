#include "dHeap.hpp"
#include <fstream>

using namespace std;

void test(int d) {
    dheap testcase(d);

    ifstream infile("/Users/toast/Desktop/usable_mortality_data.txt");
    int a;
    while (infile >> a) {
        testcase.insert(a);
    }
    
//    testcase.printHeap();
//    cout << endl;
//    cout << testcase.getSize() << endl;
    
    int n = testcase.getSize();
    
    for(int i = 0; i < n-1; i++){
        testcase.pop();
    }
    
}


int main(int argc, const char* argv[]) {
    

    using namespace std::chrono;

    auto t1 = chrono::high_resolution_clock::now();
    
    //put test code here, should read csv and put it into a heap
    
    
    test(20);
    
    
    
    auto t2 = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

    cout << duration << endl;

    return 0;
}
