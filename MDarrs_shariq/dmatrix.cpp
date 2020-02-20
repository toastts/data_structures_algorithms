#include "dmatrix.h"
#include <iostream>

using namespace std;


int dmatrix::getRow() const{
    return rows;
}

float** dmatrix::getArr() const {
    return arr;
}

int dmatrix::getCol() const {
    return cols;
}

int dmatrix::getSize() const {
    return rows * cols;
}

float dmatrix::get(int i, int j) const {
    if(i >= 0 && i < rows && j >= 0 && j < cols) {
        return  arr[i][j];
    } else {
        cout << "no" << endl;
        return 0;
    }
}

void dmatrix::set(int i, int j, float value) {
    if(i  >= 0 && i < rows && j >= 0 && j < cols) {
        arr[i][j] = value;
    } else {
        cout << "no" << endl; 
    }
}
dmatrix::dmatrix() {
    rows = 0;
    cols = 0;
}

dmatrix::dmatrix(int row, int col) {
    arr = new float*[row];
    for(int i = 0; i < row; i++) {
        arr[i] = new float[col];
    }
    rows = row;
    cols = col;
}
dmatrix dmatrix::multiply(const dmatrix &b) {
    if(getCol() != b.getRow()) {
        cout << "no" << endl;
        dmatrix a = dmatrix(getRow(), getCol());
        return a;
    }
    dmatrix* ret = new dmatrix(getRow(), b.getCol());
    for(int i = 0; i < getRow(); i++) {
        for(int j = 0; j < b.getCol(); j++) {
            float value = 0;
            for(int k = 0; k < b.getRow(); k++) {
                value += get(i, k) * b.get(k, j);
            }
            ret -> set(i, j, value);
        }
    }
    return *ret;
}

dmatrix::dmatrix(const dmatrix &original) {
    rows= original.getRow();
    cols = original.getCol();
    arr = new float*[rows];
    for(int i = 0; i < rows; i++) {
        arr[i] = new float[cols];
    }
    float** ptr = original.getArr();
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            arr[row][col] = ptr[row][col];
        }
    }
}

void dmatrix::print() const {
    for(int x = 0; x < rows; x++) {
        for(int y = 0; y < cols; y++) {
            cout << get(x, y) << " ";
        }
        cout << endl;
    }
}

dmatrix::~dmatrix() {
    delete[] arr;
}