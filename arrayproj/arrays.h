#ifndef ARRAYS
#define ARRAYS

#include <iostream>


using namespace std;

template <typename type> class array {
public:
    array();
    array(int);
    T get(int);
    void set(int, type);
    void sort();
    bool is_sorted():
    virtual ~array();
private:
    T *arr;
    int size;
    };

template <typename type> array<type>::~array() {
    free (arr);
    }

template <typename type> array<type>::array() {
    }

template <typename type> array<type>::array(int s) {
    size = s;
    arr = (type)malloc(sizeof(type) * s);
    }

template <typename type> type array<type>::get(int index) {
    return *(arr + index);
    }

template <typename type> void array<type>::set(int index, type value) {
    *(arr + index) = value;
    }

template <typename type> void array<type>::sort() {
    cout << "uhhhh yeah sure your array is sorted" << endl;
}

template <typename type> bool array<type>::is_sorted() {
    for (int i = 1; i < size; i++) {
        if (*(arr) > *(arr + i)){
            cout << "not is_sorted" << endl; 
            return false;
        }
        else {
            cout << "is is_sorted" << endl; 
            return true;
        }
    }



}








#endif