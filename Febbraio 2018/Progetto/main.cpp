#include "NN.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <stdlib.h>
using namespace std;

double f(double x)
{
	return ((cos(x*2*3.1415)+1)*2.0/5.0)+0.1;
}

int main()
{
	srand(1);

	int vv[] = {2,3,3,1};
	vector<int> structure_of_nn (vv, vv + sizeof(vv) / sizeof(int) );

	//Genero coppie di input e output
	int num_of_samples = 10;
	vector<matrix> input_train;
	vector<matrix> output_train;
	input_train.clear();
	output_train.clear();
	for (int i = 0; i < num_of_samples; ++i)
	{
		double x = double(i)/num_of_samples;
		matrix I(2,1);
		I.set_at(0,0,x);
		I.set_at(1,0,1);
		matrix O(1,1);
		O.set_at(0,0,f(x));
		input_train.push_back(I);
		output_train.push_back(O);
	}
	NN nn(structure_of_nn);


	std::cout<<"Inizio addestramento."<<std::endl;
	
	vector<matrix> upgrades_mean = nn.weights;
	for (int t = 0; t < 10000; ++t)
	{
		if ((t%1000)==0)
		{
			std::cout<<"Epoch "<<t<<std::endl;
		}
		
		std::vector<std::vector<matrix> > x = nn.backpropagation(input_train, output_train);
		
		//Meaning trought exapmles
		for (int i = 0; i < nn.number_of_weights_matrix; ++i)
		{
			upgrades_mean.at(i).reset_to(0);
		}
		
		for (int i = 0; i < num_of_samples; ++i)
		{
			for (int j = 0; j < nn.number_of_weights_matrix; ++j)
			{
				upgrades_mean.at(j) = upgrades_mean.at(j) + x.at(i).at(j);
			}
		}
		for (int i = 0; i < nn.number_of_weights_matrix; ++i)
		{
			upgrades_mean.at(i) = upgrades_mean.at(i) * (1.0/double(num_of_samples));
			
		}

		for (int i = 0; i < nn.number_of_weights_matrix; ++i)
		{
			nn.weights.at(i) = nn.weights.at(i) - upgrades_mean.at(i);
		}
	}

	std::cout<<"Fine addestramento."<<std::endl;
	std::cout<<"Stampo i punti che ho appreso."<<std::endl;
	
	std::cout<<"Input\tf(x)\tNN\tDelta\tErr.Rel"<<std::endl;
	for (int i = 0; i < num_of_samples; ++i)
	{
		double x_train = input_train.at(i).get_at(0,0);
		double y_train = output_train.at(i).get_at(0,0);
		double y_nn = nn.propagate_example(input_train.at(i)).get_at(0,0);

		double delta = y_train-y_nn;
		double errore_relativo = 100.0*delta/y_train;

		std::cout<<std::setprecision(3)<<std::fixed
	 	<<x_train<<"\t"
	 	<<y_train<<"\t"
	 	<<y_nn<<"\t"
	 	<<delta<<"\t"
	 	<<errore_relativo<<"%"
	 	<<std::endl;
	}
	
	

	double sum = 0;
	double max = 0;
	for (double x = 0; x <= 1; x+=0.01)
	{
		matrix I(2,1);
		I.set_at(0,0,x);
		I.set_at(1,0,1);
		matrix O(1,1);
		O.set_at(0,0,f(x));
		double err = nn.evaluate_error_example(I,O);
		if(err>max) max=err;
		sum += err;
	}
	std::cout<<"Lo scarto quadratico medio è: "<<sum<<std::endl;
	std::cout<<"L'errore massimo è: "<<max<<std::endl;
	

	return 0;
}

