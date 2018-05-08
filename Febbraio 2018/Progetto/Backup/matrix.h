#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include <stdlib.h>


struct pair
{
	int first, second;
};


class matrix
{
	int rows, columns;
	double* data;
public:
	matrix();
	matrix(int x, int y);
	matrix(char nome_file[80]);
	
	matrix& operator=(matrix& O)
	{
		printf("Assegnazione tramite LucaNet = nelle matrici\n");
		rows = O.dimension().first;
		columns = O.dimension().second;
		delete [] data;
		data = new double[rows*columns];
		
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				double var = O.get_at(i,j);
				set_at(i,j,var);
			}
		}
		return *this;
	}
	//matrix& operator=(matrix& original); //copy constructor

	

	double get_at(int x, int y);
	bool set_at(int x, int y, double var);
	pair dimension();
	void display();
	void reset_to(double var);
	void reset_to_random();
	void print_dimension();

	friend matrix operator+(matrix A, matrix B);

};

matrix matrix_addition(matrix A, matrix B);
matrix matrix_subtraction(matrix A, matrix B);
matrix matrix_product(matrix A, matrix B);
matrix matrix_elementwise_product(matrix A, matrix B);
matrix matrix_scalar_product(matrix A, double lambda);
matrix matrix_transpose(matrix A);