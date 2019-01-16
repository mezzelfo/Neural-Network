#ifndef NN_H
#define NN_H

#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.h"

typedef double (*nonLinearFuncPTR)(double);

template<unsigned dim>
Vettore<dim,double> NLTransform(Vettore<dim,double> v, nonLinearFuncPTR f)
{
    for(unsigned i = 0; i < dim; i++) v(i) = f(v(i));
    return v;
}

double Sigmoid(double t)
{
    return 1.0/(1.0+exp(-t));
}

template<unsigned Input, unsigned Hidden, unsigned Output>
class ThreeLayerNN
{
    Matrix<Hidden,Input,double> matrix1;
    Matrix<Output,Hidden,double> matrix2;
public:
    ThreeLayerNN()
    {
        matrix1.fill(0.0);
        matrix2.fill(0.0);
    }

    Vettore<Output,double> apply(Vettore<Input,double> inputVector)
    {
        return matrix2*NLTransform(matrix1*inputVector, Sigmoid);
    }
};



#endif