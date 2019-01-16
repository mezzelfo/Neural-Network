#include <iostream>
#include "matrix.h"
#include "NN.h"

int main()
{
    ThreeLayerNN<2,4,3> nn;
    Vettore<2,double> v;
    v.fill(1);
    std::cout << v << "->\n" << nn.apply(v) << std::endl;
    return 0;
}


