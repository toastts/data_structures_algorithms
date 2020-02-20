#ifndef SMATRIX_H_
#define SMATRIX_H_

#include "snode.h"
#include "dmatrix.h"


class smatrix {
    private:
        snode** arr_row;
        int row;
        int col;
    public:
        smatrix();
        smatrix(int, int);
        smatrix(const dmatrix &);
        smatrix convR2C() const;
        float get(int, int) const;
        int getRow() const;
        int getCol() const;
        snode** getPtr() const;
        void set(int, int, float);
        smatrix mult(const smatrix &) const;
        smatrix add(const smatrix &) const;
        void print() const;
        virtual ~smatrix();
};

#endif