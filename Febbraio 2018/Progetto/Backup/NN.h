#include "matrix.h"
#include <math.h>

class NN
{
public:
	matrix* pesi;
	matrix* correzioni_dopo_train;
	matrix* layer;
	int* struttura_nn;
	int num_layer;
//public:
	NN(int* dim, int l);
	void random_pesi();

	matrix activate(matrix L);
	matrix activate_derivative(matrix L);

	matrix propagate_singolo(matrix input);
	double mean_error_function_singolo(matrix input, matrix output_espected);
	void addestra_singolo(matrix input, matrix output_espected);

	//void train(matrix* input, matrix* output_espected, int times);


	double mean_error_function(matrix input[], matrix output_espected[], int dim);
	void train_v2(matrix input[], matrix output_espected[], int dim, int times);

	void train_v3(matrix input[], matrix output_espected[], int num_campioni, int times);



	
};


