#include "NN.h"
//#include "matrix.h"
#include <math.h>

double f(double x)
{
	//double r = ((13.0)*x*x*x) + ((-21.0)*x*x) + ((10.0)*x) +(-1);
	double r = ((cos(x*2*3.1415)+1)*2.0/5.0)+0.1;
	//double r = x/2;
	return r;
}


int main()
{

	matrix A(2,3);
	A.reset_to(0);
	matrix B, D;


	B = A;
	A.set_at(0, 0, 1);
	B.set_at(0, 0, 3);
	B.set_at(0, 1, 1);
	matrix C = matrix_transpose(matrix_addition(A, B));
	D = matrix_transpose(C);
	C.set_at(1, 1, -1);
	
	A.display();
	B.display();
	C.display();
	D.display();




	

	srand (time(NULL));

	const int num_coppie = 9;
	const int dimensione_input = 2;
	// const int dimensione_output = 1;

	// const int numero_cicli_apprendimento = 5000;
	// const double delta_spazio = 1.0/(num_coppie-1);

	// int nn_structure[] = {dimensione_input,4,dimensione_output};
	// int numero_layer = sizeof(nn_structure)/sizeof(*nn_structure);

	// //Genero coppie di input e output
	// matrix input_long[num_coppie];
	// matrix output_long[num_coppie];
	// for (int i = 0; i < num_coppie; ++i)
	// {
	// 	matrix temp_i(1,dimensione_input);
	// 	temp_i.set_at(0, 0, i*delta_spazio);
	// 	temp_i.set_at(0, 1, 1);


	// 	input_long[i] = temp_i;
	// 	//std::cout<<"Input num "<<i<<std::endl;
	// 	//input_long[i].display();

	// 	matrix temp_o(1,dimensione_output);
	// 	temp_o.set_at(0, 0, f(double(i*delta_spazio)));

	// 	output_long[i] = temp_o;
	// 	//std::cout<<"ouput num "<<i<<std::endl;
	// 	//output_long[i].display();
	// }

	
	
	// NN nn(nn_structure, numero_layer);
	// nn.random_pesi();


	// /*
	// pesi weight_input_hidden
	// [[ 4.60704495  8.58899016  0.31280627  5.04860568]
	//  [-3.15023424 -2.54448055  0.78958675 -3.39508441]]
	// pesi weight_hidden_output
	// [[ 5.0107944 ]
	//  [-8.59893029]
	//  [ 3.30526096]
	//  [ 5.17261515]]
	// */
	// matrix p1(2,4);
	// p1.set_at(0, 0, +4.60704495);
	// p1.set_at(0, 1, +8.58899016);
	// p1.set_at(0, 2, +0.31280627);
	// p1.set_at(0, 3, +5.04860568);
	// p1.set_at(1, 0, -3.15023424);
	// p1.set_at(1, 1, -2.54448055);
	// p1.set_at(1, 2, +0.78958675);
	// p1.set_at(1, 3, -3.39508441);
	// nn.pesi[0] = p1;


	// matrix p2(4,1);
	// p2.set_at(0, 0, +5.0107944);
	// p2.set_at(1, 0, -8.59893029);
	// p2.set_at(2, 0, +3.30526096);
	// p2.set_at(3, 0, +5.17261515);
	// nn.pesi[1] = p2;
	

	

	// std::cout<<std::endl<<"Errore prima del addestramento: "<<nn.mean_error_function(input_long, output_long, num_coppie)<<std::endl;
	// nn.train_v2(input_long, output_long, num_coppie, numero_cicli_apprendimento);
	// std::cout<<"Errore dopo del addestramento: "<<nn.mean_error_function(input_long, output_long, num_coppie)<<std::endl<<std::endl;
	



	
	// //Controllo se ho imparato
	// std::cout<<"Input\tf(i)\tNN\tDelta\tErr.Rel"<<std::endl;
	// for (int i = 0; i < num_coppie; ++i)
	// {
	// 	matrix temp_i = input_long[i];
		
	// 	matrix temporaneo;
	// 	temporaneo = nn.propagate_singolo(temp_i);
	// 	double output_nn = nn.activate(temporaneo).get_at(0, 0) ;
	// 	double output_conosciuto = output_long[i].get_at(0, 0);
	// 	double delta = fabsl(output_conosciuto-output_nn);
	// 	double errore_percentuale_relativo = fabsl(1.0-double(output_conosciuto/output_nn))*100;
	// 	std::cout<<std::setprecision(3)<<std::fixed
	// 	<<temp_i.get_at(0, 0)<<"\t"
	// 	<<output_conosciuto<<"\t"
	// 	<<output_nn<<"\t"
	// 	<<delta<<"\t"<<
	// 	errore_percentuale_relativo<<"%"<<std::endl;
	// }
	

	// /*
	// for (double i = 0; i < 1; i+=delta_spazio)
	// {
	// 	matrix temp_i = 
	// 	double output_nn = nn.propagate_singolo(&temp_i).get_at(0, 0);
	// 	double output_conosciuto = f(i);
	// 	double delta = fabsl(output_conosciuto-output_nn);
	// 	double errore_percentuale_relativo = fabsl(1.0-double(output_conosciuto/output_nn))*100;
	// 	std::cout<<std::setprecision(3)<<std::fixed
	// 	<<i<<"\t"
	// 	<<output_conosciuto<<"\t"
	// 	<<output_nn<<"\t"
	// 	<<delta<<"\t"<<
	// 	errore_percentuale_relativo<<"%"<<std::endl;
	// }
	// */

	// /*
	// //Valuto l'errore con degli esempi
	// std::cout<<"Input\tf(i)\tNN\tDelta\tErr.Rel"<<std::endl;
	// for (double i = 0.05; i < 1; i+=delta_spazio)
	// {
	// 	matrix temp_i(1,1);
	// 	temp_i.set_at(0, 0, i);
	// 	double output_nn = nn.propagate_singolo(&temp_i).get_at(0, 0);
	// 	double output_conosciuto = f(i);
	// 	double delta = fabsl(output_conosciuto-output_nn);
	// 	double errore_percentuale_relativo = fabsl(1.0-double(output_conosciuto/output_nn))*100;
	// 	std::cout<<std::setprecision(3)<<std::fixed
	// 	<<i<<"\t"
	// 	<<output_conosciuto<<"\t"
	// 	<<output_nn<<"\t"
	// 	<<delta<<"\t"<<
	// 	errore_percentuale_relativo<<"%"<<std::endl;
	// }
	// */
	

	return 0;
}

