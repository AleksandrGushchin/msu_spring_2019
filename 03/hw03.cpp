#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <new>

using namespace std;

class Column
{
    int len;
    int *arr;
public:

    Column(int c)
        :len(c)
    {
        arr = new int[c];
    }

    int& operator [](int x)
    {
        if(x >= len)
            throw out_of_range("");
        return arr[x];
    }

    const int& operator [](int x) const
    {
        if(x >= len)
            throw out_of_range("");
        return arr[x];
    }
    ~Column()
    {
        delete[] arr;
    }
};

class Matrix
{
private:
    Column *mat;
    int rows, columns;

public:
    Matrix(int r, int c)
        :rows(r),
         columns(c)
    {
        mat = static_cast<Column*>(operator new[] (r * sizeof(Column)));
        for (int i = 0; i < r; i++)
        {
              new (mat + i) Column(c);
        }
    }

    int getRows() const
    {
        return rows;
    }

    int getColumns() const
    {
        return columns;
    }

    bool operator ==(const Matrix& other) const
    {
        if(columns != other.getColumns() || rows != other.getRows())
            return false;
        if(this == &other)
            return true;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j  < columns; j++)
                if((*this)[i][j] != other[i][j])
                    return false;
        }
        return true;
    }

    bool operator !=(const Matrix& other) const
    {
        return !(*this == other);
    }

    Matrix& operator *=(int x){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++)
                (*this)[i][j] = x * (*this)[i][j];
        }
        return *this;
    }

    Column& operator [](int x)
    {
        if(x >= rows)
            throw out_of_range("");
        return mat[x];
    }

    const Column& operator [](int x) const
    {
        if(x >= rows)
            throw out_of_range("");
        //return const_cast<Column&>(mat[x]);
        return mat[x];
    }
    ~Matrix()
    {
        delete[] (mat);
    }
};
