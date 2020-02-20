#include "smatrix.h"
#include <iostream>
#include "snode.h"

using namespace std;

smatrix::smatrix()
{
}

smatrix::smatrix(int r, int c)
{
    row = r;
    col = c;
    arr_row = new snode *[row];
    for (int i = 0; i < row; i++)
    {
        arr_row[i] = nullptr;
    }
}

smatrix::smatrix(const dmatrix &d)
{
    float **ptr = d.getArr();
    row = d.getRow();
    col = d.getCol();
    arr_row = new snode *[row];
    for (int x = 0; x < row; x++)
    {
        arr_row[x] = nullptr;
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            float val = ptr[i][j];
            if (val != 0)
            {
                snode *n = new snode();
                n->col = j;
                n->data = val;
                n->next = nullptr;
                if (arr_row[i] == nullptr)
                {
                    arr_row[i] = n;
                }
                else
                {
                    snode *temp = arr_row[i];
                    while (temp->next != nullptr)
                    {
                        temp = temp->next;
                    }
                    temp->next = n;
                }
            }
        }
    }
}

void smatrix::set(int r, int c, float value)
{
    if (r < row && c < col)
    {
        snode *n = new snode();
        n->col = c;
        n->data = value;
        if (arr_row[r] == nullptr)
        {
            n->next = nullptr;
            arr_row[r] = n;
        }
        else
        {
            if (arr_row[r]->next == nullptr)
            {
                if(arr_row[r] -> col > c) {
                    snode *temp_ptr = arr_row[r];
                    n -> next = temp_ptr;
                    arr_row[r] = n;
                } else {
                    n -> next = nullptr;
                    arr_row[r] -> next = n;
                }
            }
            else
            {

                snode *temp_ptr = arr_row[r];
                while (!(temp_ptr->next == nullptr) && temp_ptr->next->col < c)
                {
                    temp_ptr = temp_ptr->next;
                }
                snode *after_ptr = temp_ptr->next;
                temp_ptr->next = n;
                n->next = after_ptr;
            }
        }
    }
    else
    {
        cout << "no" << endl;
    }
}

float smatrix::get(int r, int c) const
{
    snode *p = arr_row[r];
    while (p != nullptr && p->col < c)
    {
        p = p->next;
    }
    if (p != nullptr && p->col == c)
    {
        return p->data;
    }
    else
    {
        return 0.0;
    }
}

int smatrix::getRow() const
{
    return row;
}

int smatrix::getCol() const
{
    return col;
}
void smatrix::dump() const
{
    for (int i = 0; i < row; i++)
    {
        snode *ptr = arr_row[i];
        for (int j = 0; j < col; j++)
        {
            if (ptr == nullptr)
            {
                cout << " - ";
            }
            else if (ptr->col > j)
            {
                cout << " - ";
            }
            else if (ptr->col == j)
            {
                cout << " " << ptr->data << " ";
                ptr = ptr->next;
            }
            else
            {
                cout << "NONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONONO. NO.";
            }
        }
        cout << endl;
    }
}
smatrix smatrix::add(const smatrix &other) const
{
    smatrix ret = smatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        snode *lp = arr_row[i];
        snode *rp = other.getPtr()[i];
        snode *psum = nullptr;
        while (lp != nullptr || rp != nullptr)
        {
            float rv = 0;
            unsigned int rc = 0;
            if (lp == nullptr)
            {
                rv = rp->data;
                rc = rp->col;
                rp = rp->next;
            }
            else
            {
                if (rp == nullptr || lp->col < rp->col)
                {
                    rv = lp->data;
                    rc = lp->col;
                    lp = lp->next;
                }
                else
                {
                    if (rp->col < lp->col)
                    {
                        rv = rp->data;
                        rc = rp->col;
                        rp = rp->next;
                    }
                    else
                    {
                        rv = lp->data + rp->data;
                        rc = lp->col;
                        rp = rp->next;
                        lp = lp->next;
                    }
                }
            }

            if (rv != 0)
            {
                snode *sum = new snode();
                sum->col = rc;
                sum->data = rv;
                sum->next = nullptr;
                if (psum == nullptr)
                {
                    ret.getPtr()[i] = sum;
                    psum = sum;
                }
                else
                {
                    psum->next = sum;
                    psum = sum;
                }
            }
        }
    }
    return ret;
}

smatrix smatrix::mult(const smatrix &other) const
{
    if (col != other.getRow())
    {
        cerr << "no" << endl;
        return smatrix();
    }
    smatrix *ret = new smatrix(row, other.getCol());

    smatrix otherC = other.convR2C();
    for (int i = 0; i < row; i++)
    {
        snode *pmult = nullptr;
        for (int j = 0; j < other.getCol(); j++)
        {
            snode *left_p = arr_row[i];
            snode *right_p = otherC.getPtr()[j];
            float return_val = 0;
            unsigned int return_col = j;
            while (left_p != nullptr && right_p != nullptr)
            {
                if (left_p->col < right_p->col)
                {
                    left_p = left_p->next;
                }
                else
                {
                    if (right_p->col < left_p->col)
                    {
                        right_p = right_p->next;
                    }
                    else
                    {
                        return_val += left_p->data * right_p->data;
                        left_p = left_p->next;
                        right_p = right_p->next;
                    }
                }
            }
            if (return_val != 0)
            {
                snode *mult = new snode();
                mult->col = return_col;
                mult->data = return_val;
                mult->next = nullptr;
                if (pmult == nullptr)
                {
                    ret->getPtr()[i] = mult;
                    pmult = mult;
                }
                else
                {
                    pmult->next = mult;
                    pmult = mult;
                }
            }
        }
    }
    return *ret;
}

smatrix smatrix::convR2C() const
{
    smatrix *product = new smatrix(col, row);
    for (int i = 0; i < row; i++)
    {
        snode *temp = arr_row[i];
        while (temp != nullptr)
        {
            snode *n = new snode();
            n->col = i;
            n->data = temp->data;
            if (product->getPtr()[temp->col] == nullptr)
            {
                n->next = nullptr;
                product->getPtr()[temp->col] = n;
            }
            else
            {
                snode *temp_ptr = product->getPtr()[temp->col];
                while (temp_ptr->next != nullptr)
                {
                    temp_ptr = temp_ptr->next;
                }
                n->next = nullptr;
                temp_ptr->next = n;
            }
            temp = temp->next;
        }
    }
    return *product;
}

snode **smatrix::getPtr() const
{
    return arr_row;
}

smatrix::~smatrix()
{
    delete arr_row;
}




