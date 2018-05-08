#include "NN.h"

NN::NN(int* dim, int l)
{
	struttura_nn = dim;
	num_layer = l;
	delete [] pesi;
	delete [] correzioni_dopo_train;
	delete [] layer;

	pesi = new matrix[num_layer-1];
	correzioni_dopo_train = new matrix[num_layer-1];
	layer = new matrix[num_layer];

	for (int i = 0; i < num_layer-1; ++i)
	{
		matrix temp_pesi(dim[i], dim[i+1]);
		temp_pesi.reset_to(1);
		pesi[i] = temp_pesi;

		correzioni_dopo_train[i] = temp_pesi;
		correzioni_dopo_train[i].reset_to(0);
	}

	for (int i = 0; i < num_layer; ++i)
	{
		matrix temp_layer(1,dim[i]);
		temp_layer.reset_to(0.5);
		layer[i] = temp_layer;
	}
}

void NN::random_pesi()
{
	for (int i = 0; i < num_layer; ++i)
	{
		pesi[i].reset_to_random();
		//pesi[i].reset_to(0.5);
	}
}

matrix NN::activate(matrix L)
{
	matrix R = L;
	for (int i = 0; i < L.dimension().first; ++i)
	{
		for (int j = 0; j < L.dimension().second; ++j)
		{
			double val = L.get_at(i, j);

			//Logistic function
			//val = val;
			val = 1.0/(1.0+exp(-1*val));

			//End logistic function

			R.set_at(i, j, val);
		}
	}
	return R;
}

matrix NN::activate_derivative(matrix L)
{
	matrix R = L;
	for (int i = 0; i < L.dimension().first; ++i)
	{
		for (int j = 0; j < L.dimension().second; ++j)
		{
			double val = L.get_at(i, j);

			//Logistic function derivative
			//val = 1;
			val = (exp(-val))/( (1.0+exp(-1.0*val)) * (1.0+exp(-1.0*val)) );
			//End logistic function derivative

			R.set_at(i, j, val);
		}
	}
	return R;
}

matrix NN::propagate_singolo(matrix input)
{
	
	for (int i = 0; i < (num_layer); ++i)
	{

		if(i==0)
		{
			layer[0] = input;
		}else if(i==1)
		{
			layer[1] = matrix_product(layer[0], pesi[0]);
		}
		else
		{
			//layer[i] = matrix_product(activate(layer[i-1]), pesi[i-1]);
			layer[i] = layer[i-1];
			layer[i] = activate(layer[i]);
			layer[i] = matrix_product(layer[i], pesi[i-1]);
		}
	}
	return layer[num_layer-1];
}

void NN::addestra_singolo(matrix input, matrix output_espected)
{
	matrix correzioni[num_layer-1];
	
	//Inizio caloclo derivate
	matrix deltaE = matrix_transpose(matrix_subtraction(propagate_singolo(input), output_espected));
	//deltaE = propagate_singolo(input);
	//deltaE = matrix_subtraction(deltaE, output_espected);
	//deltaE = matrix_transpose(deltaE);

	

	//primo passo ovvero ultimi pesi
	//correzioni[num_layer-1-1] = matrix_transpose(matrix_product(deltaE, activate(layer[num_layer-1-1])));
	matrix temporaneo;
	//temporaneo = activate(layer[num_layer-1-1]);
	//temporaneo = matrix_product(deltaE,temporaneo);
	//correzioni[num_layer-1-1] = matrix_transpose(temporaneo);
	
	
	//passi intermedi
	matrix T = deltaE;
	for (int i = num_layer-2; i > 1; --i)
	{
		T = matrix_product(pesi[i], T);

		//T = matrix_elementwise_product(T, matrix_transpose(activate_derivative(layer[i])));
		temporaneo = activate_derivative(layer[i]);
		temporaneo = matrix_transpose(temporaneo);
		T = matrix_elementwise_product(T, temporaneo);


		//correzioni[i-1] = matrix_transpose(matrix_product(T,activate(layer[i-1])));
		temporaneo = activate(layer[i-1]);
		temporaneo = matrix_product(T,temporaneo);
		correzioni[i-1] = matrix_transpose(temporaneo);
	}

	//ultimo passo ovvero primi pesi
	T = matrix_product(pesi[1], T);

	//T = matrix_elementwise_product(T, matrix_transpose(activate_derivative(layer[1])));
	temporaneo = activate_derivative(layer[1]);
	temporaneo = matrix_transpose(temporaneo);
	T = matrix_elementwise_product(T, temporaneo);


	//correzioni[0] = matrix_transpose(matrix_product(T,layer[0]));
	temporaneo = matrix_product(T,layer[0]);
	correzioni[0] = matrix_transpose(temporaneo);


	//Memorizzo le correzioni
	for (int i = 0; i < num_layer-1; ++i)
	{
		//std::cout<<"Dim correzione num. "<<i<<": (";
		//correzioni[i].print_dimension();
		//std::cout<<std::endl;
		correzioni_dopo_train[i] = correzioni[i];
	}
	return;
}

double NN::mean_error_function_singolo(matrix input, matrix output_espected)
{
	double mean = 0.0;
	matrix output;
	output = propagate_singolo(input);
	for (int i = 0; i < output_espected.dimension().second; ++i)
	{
		mean += 0.5*(output.get_at(0,i) - output_espected.get_at(0,i))*(output.get_at(0,i) - output_espected.get_at(0,i));
	}
	return mean;
}
/*
void NN::train(matrix* input, matrix* output_espected, int times)
{
	for (int i = 0; i < times; ++i)
	{
		addestra_singolo(input, output_espected);
		for (int j = 0; j < num_layer-1; ++j)
		{
			pesi[j] = matrix_subtraction(pesi[j], correzioni_dopo_train[j]);
		}
		//std::cout<<"Errore al passo n. "<<i<<": "<<mean_error_function_singolo(input, output_espected)<<std::endl;
	}
	return;
}
*/
double NN::mean_error_function(matrix input[], matrix output_espected[], int dim)
{
	double errore_medio = 0.0;

	for (int j = 0; j < dim; ++j)
	{
		errore_medio += mean_error_function_singolo(input[j], output_espected[j]);
	}
	errore_medio = errore_medio/double(dim);

	return errore_medio;
}

void NN::train_v2(matrix input[], matrix output_espected[], int dim, int times)
{
	for (int t = 0; t < times; ++t)
	{
		addestra_singolo(input[0], output_espected[0]);
		matrix media_correzioni[num_layer-1];

		for (int i = 0; i < num_layer-1; ++i)
		{
			media_correzioni[i] = correzioni_dopo_train[i];
			media_correzioni[i].reset_to(0.0);
		}

		
	
		

		for (int c = 0; c < dim; ++c)
		{
			//printf("Campione numero %d\n", c);
			//printf("Input: %f \t -> %f aspettato\n", input[c].get_at(0,0),output_espected[c].get_at(0,0));
			//printf("Mentro ottengo:\n");
			//propagate_singolo(&(input[c])).display();
			//printf("Addestro:\n");
			
			addestra_singolo(input[c], output_espected[c]);
			


			for (int i = 0; i < num_layer-1; ++i)
			{
				media_correzioni[i] = matrix_addition(media_correzioni[i], correzioni_dopo_train[i]);
				//printf("Correzione dei pesi n.%d\n", i);
				//media_correzioni[i].display();
			}


			
			
		}

		for (int i = 0; i < num_layer-1; ++i)
		{
			media_correzioni[i] = matrix_scalar_product(media_correzioni[i], double(1.0/dim));
		}

		for (int j = 0; j < num_layer-1; ++j)
		{
			pesi[j] = matrix_subtraction(pesi[j], media_correzioni[j]);
		}
	}
}


void NN::train_v3(matrix input[], matrix output_espected[], int num_campioni, int times)
{
	//Dichiaro delle matrici in cui tengo tutte le correzioni per ogni campione
	matrix correzioni_pesi[num_campioni][num_layer-1];
	for (int num_del_layer_peso = 0; num_del_layer_peso < num_layer-1; ++num_del_layer_peso)
	{
		matrix temp_m(struttura_nn[num_del_layer_peso],struttura_nn[num_del_layer_peso+1]);
		temp_m.reset_to(0);
		for (int camp = 0; camp < num_campioni; ++camp)
		{
			correzioni_pesi[camp][num_del_layer_peso] = temp_m;
		}
	}

	for (int camp = 0; camp < num_campioni; ++camp)
	{
		printf("girore\n");
		correzioni_dopo_train[0].display();
		printf("test\n");
		pesi[0].reset_to(0.5);
		correzioni_dopo_train[0].display();
		printf("fine test\n");
		exit(-2);

		addestra_singolo(input[camp],output_espected[camp]);
		correzioni_dopo_train[0].display();
	}

}




