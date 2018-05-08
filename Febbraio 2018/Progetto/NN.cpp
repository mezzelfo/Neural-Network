#include "NN.h"

//Empty constructor
NN::NN()
{
	std::cerr<<"FATAL Error. Trying to create a not-well defined neural network."<<std::endl;
	exit(EXIT_FAILURE);
}
//Parametrized constructor
NN::NN(std::vector<int> s)
{
	structure_of_nn.clear();
	structure_of_nn = s;

	number_of_layer = structure_of_nn.size();
	number_of_weights_matrix = number_of_layer - 1;
	
	//Generating appropriate weights matrix
	weights.clear();
	for (int i = 0; i < number_of_weights_matrix; ++i)
	{
		int dim_preceding_layer = structure_of_nn.at(i);
		int dim_succeeding_layer = structure_of_nn.at(i+1);
		matrix W(dim_preceding_layer, dim_succeeding_layer);
		W.reset_to_random();
		weights.push_back(W);
	}

	//Generating appropriate layers matrix
	layers_not_activated.clear();
	for (int i = 0; i < number_of_layer; ++i)
	{
		matrix L(structure_of_nn.at(i),1);
		L.reset_to(0);
		layers_not_activated.push_back(L);
	}

	return;
}
//Destructor
NN::~NN()
{
	structure_of_nn.clear();
	weights.clear();
	layers_not_activated.clear();
}

//Activation Function
double NN::activation_function(double x)
{
	double var = 1.0/(1.0 + exp(-1.0*x));
	return var;
}
double NN::activation_function_derivative(double x)
{
	double ex = exp(x);
	double var = ex/((ex+1)*(ex+1));
	return var;
}
matrix NN::activate(matrix layer)
{
	matrix R = layer;
	for (int r = 0; r < layer.rows; ++r)
	{
		for (int c = 0; c < layer.columns; ++c)
		{
			R.set_at(r, c, activation_function(layer.get_at(r,c)));
		}
	}
	return R;
}
matrix NN::activate_derivative(matrix layer)
{
	matrix R = layer;
	for (int r = 0; r < layer.rows; ++r)
	{
		for (int c = 0; c < layer.columns; ++c)
		{
			R.set_at(r, c, activation_function_derivative(layer.get_at(r,c)));
		}
	}
	return R;
}

//propagate
matrix NN::propagate_example(matrix input)
{
	for (int i = 0; i < (number_of_layer); ++i)
	{
		if(i==0)
		{
			layers_not_activated.at(0) = input;
		}else if(i==1)
		{
			layers_not_activated.at(1) = !(!layers_not_activated.at(0) * weights.at(0));
		}
		else
		{
			layers_not_activated.at(i) = !((!(activate(layers_not_activated.at(i-1)))) * weights.at(i-1));
		}
	}
	return layers_not_activated.at(number_of_layer-1);
}

//Error Function
double NN::evaluate_error_example(matrix input, matrix output_expected)
{
	matrix deltaE = propagate_example(input) - output_expected;
	matrix E = ((!deltaE) * deltaE)*0.5;
	if((E.rows!=1)or(E.columns!=1))
	{
		std::cerr	<<"FATAL Error. Cannot get the error for the delta matrix: "
					<<"("<<E.rows<<", "<<E.columns<<")"<<std::endl;
		exit(EXIT_FAILURE);
	}
	return E.get_at(0,0);
}



//Train and Backpropagation
std::vector<matrix> NN::backpropagation_example(matrix input, matrix output_expected)
{
	std::vector<matrix> upgrades;
	upgrades.clear();
	for (int i = 0; i < number_of_weights_matrix; ++i)
	{
		int dim_preceding_layer = structure_of_nn.at(i);
		int dim_succeeding_layer = structure_of_nn.at(i+1);
		matrix U(dim_preceding_layer, dim_succeeding_layer);
		U.reset_to(0.0);
		upgrades.push_back(U);
	}
	//primo passo ovvero ultimi pesi
	matrix deltaE = !(propagate_example(input) -  output_expected);
	upgrades.at(number_of_layer-2) = (activate(layers_not_activated.at(number_of_layer-1-1))) * deltaE;
	//passi intermedi
	matrix T = !deltaE;
	for (int i = number_of_layer-2; i > 1; --i)
	{
		T = element_wise_product((weights.at(i) * T), activate_derivative(layers_not_activated.at(i)));
		upgrades.at(i-1) = (!(T * !(activate(layers_not_activated.at(i-1)))));
	}

	//Ultimo passo
	T = element_wise_product(weights.at(1) * T, activate_derivative(layers_not_activated.at(1)));
	upgrades.at(0) = (!(T * (!layers_not_activated.at(0))));
	

	//Check dimension
	/*
	for (int i = 0; i < number_of_weights_matrix; ++i)
	{
		std::cout<<"Dim Weight at "<<i<<std::endl;
		weights.at(i).print_dim();
		upgrades.at(i).print_dim();

	}
	*/

	return upgrades;
}
std::vector<std::vector<matrix> > NN::backpropagation(std::vector<matrix> input, std::vector<matrix> output_expected)
{
	std::vector<std::vector<matrix> > upgrades;
	upgrades.clear();
	for (int i = 0; i < input.size(); ++i)
	{
		upgrades.push_back(backpropagation_example(input.at(i),output_expected.at(i)));
	}
	return upgrades;
}