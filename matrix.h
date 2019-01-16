#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template<unsigned R, unsigned C, class T>
class Matrix
{
    T m[R*C];
    public:
    Matrix()
    {

    }

    void fill(T e)
    {
        for(unsigned i = 0; i < R*C; i++)
        {
            m[i] = e;
        }
    }

    T& operator()(unsigned i)
    {
        return m[i];
    }

    const T& operator()(unsigned i) const
    {
        return m[i];
    }

    T& operator()(unsigned i, unsigned j)
    {
        return m[i*C+j];
    }

    const T& operator()(unsigned i, unsigned j) const
    {
        return m[i*C+j];
    }

    T& at(unsigned i, unsigned j)
    {
        if ((i < R) && (j < C)) {
            return m[i*C+j];
        }
        throw "Requested indices out of bound\n";
    }

    const T& at(unsigned i, unsigned j) const
    {
        if ((i < R) && (j < C)) {
            return m[i*C+j];
        }
        throw "Requested indices out of bound\n";
    }
};


template<unsigned R, unsigned C, class T>
std::ostream& operator<<(std::ostream& out, const Matrix<R,C,T>& matrix)
{   
    for(unsigned i = 0; i < R; i++)
    {
        for(unsigned j = 0; j < C; j++)
        {
            out << matrix(i,j) << '\t';
        }
        out << '\n';
    }
    return out;    
}

template<unsigned R, unsigned C, class T>
Matrix<R,C,T> operator+(const Matrix<R,C,T>& matrix1, const Matrix<R,C,T>& matrix2)
{   
    Matrix<R,C,T> out;
    for(unsigned i = 0; i < R*C; i++)
    {
        out(i) = matrix1(i) + matrix1(i);
    }
    return out;    
}

template<unsigned dimA, unsigned dimB, unsigned dimC, class T>
Matrix<dimA,dimC,T> operator*(const Matrix<dimA,dimB,T>& matrix1, const Matrix<dimB,dimC,T>& matrix2)
{   
    Matrix<dimA,dimC,T> out;
    for(unsigned i = 0; i < dimA; i++)
    {
        for(unsigned j = 0; j < dimC; j++)
        {
            T sum = 0;
            for(unsigned k = 0; k < dimB; k++)
            {
                sum += matrix1(i,k)*matrix2(k,j);
            }
            out(i,j) = sum;
        }
    }
    return out;    
}

#endif
