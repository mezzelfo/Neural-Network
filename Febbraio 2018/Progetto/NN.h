#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.h"

class NN
{
public:
//private:
	int number_of_layer;
	int number_of_weights_matrix;
	std::vector<int> structure_of_nn;
	std::vector<matrix> weights;
	std::vector<matrix> layers_not_activated;
public:
	//Empty constructor
	NN();
	//Parametrized constructor
	NN(std::vector<int> s);
	//Destructor
	~NN();

	//Activation Function
	double activation_function(double x);
	double activation_function_derivative(double x);
	matrix activate(matrix layer);
	matrix activate_derivative(matrix layer);

	//propagate
	matrix propagate_example(matrix input);

	//Error Function
	double evaluate_error_example(matrix input, matrix output_expected);


	//Train and Backpropagation
	std::vector<matrix> backpropagation_example(matrix input, matrix output_expected);
	std::vector<std::vector<matrix> > backpropagation(std::vector<matrix> input, std::vector<matrix> output_expected);


};