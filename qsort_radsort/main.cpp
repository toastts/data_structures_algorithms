#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <fstream>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <random>


using namespace std;



void quickSort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      //partition array, doesn't matter from where since it's already shuffled
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}






int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
}

void countSort(int arr[], int n, int exp) 
{
    int output[n]; // output array 
    int i, count[10] = {0}; 

    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 

    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 

    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--;
    } 

    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 





void radixsort(int arr[], int n, int BASE) 
{
    int m = getMax(arr, n); 

    for (int exp = 1; m/exp > 0; exp *= BASE) 
        countSort(arr, n, exp); 
}

//https://www.totalregistration.net/AP-Exam-Registration-Service/AP-Exam-Score-Distributions.php?year=2016 comparative government
//even distribution of test data, identical keys, low digit number, favors radixsort
void createData1(int arr[], int n){
    for (int i = 0; i < n/5; i++){
       arr[i] = 1;
    }
    for(int i = n/5; i < (2*n / 5); i++){
        arr[i] = 2;
    }
    for(int i = (2*n/5); i < (3*n / 5); i++){
        arr[i] = 3;
    }
    for(int i = (3*n/5); i < (4*n / 5); i++){
        arr[i] = 4;
    }
    for(int i = (4*n/5); i < n; i++){
        arr[i] = 5;
    }

}

//https://datausa.io/profile/geo/chandler-az/, age data for chandler, identical, low digits, favors radix
void createData2(int arr[], int n) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(35-10, 35 + 10); // define the range
    
    for (int i=0; i < n; i++){
        
        arr[i] = distr(eng);
    }
}

void createData3(int arr[], int n) {
    std::ifstream infile("/Users/toast/Downloads/usable_id_data.txt");
    int a;
    int count = 0;
    while (infile >> a)
    {
        arr[count] = a;
        count++;
    }
    
}

void createData4(int arr[], int n) {
    std::ifstream infile("/Users/toast/Downloads/usable_revenue_data.txt");
    int a;
    int count = 0;
    while (infile >> a)
    {
        arr[count] = a;
        count++;
    }
    
}



template<typename RandomAccessIterator>
void knuthShuffle(RandomAccessIterator begin, RandomAccessIterator end) {
  for(unsigned int n = end - begin - 1; n >= 1; --n) {
    unsigned int k = rand() % (n + 1);
    if(k != n) {
      std::iter_swap(begin + k, begin + n);
    }
  }
}


int main(int argc, const char * argv[]) {

    int arrSize = 500000;
    
    int data[arrSize];

    //createData2(data, arrSize);
    
    //createData{putnumber](data, arrSize);

    std::random_shuffle(data, data + arrSize);
    
    using namespace std::chrono;
    
    auto t1 = chrono::high_resolution_clock::now();
    
    
    
    //radixsort(data, arrSize, 15);
    quickSort(data, 0, arrSize - 1);
    
    
    
    auto t2 = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
    
//    for (int j = 0; j < arrSize; j++) {
//        cout << data[j] << endl;
//     }


      cout << duration << endl;

    return 0;

}
