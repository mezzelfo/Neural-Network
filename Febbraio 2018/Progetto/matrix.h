#include <iostream>
#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



class matrix
{
private:
	std::vector<double> data_matrix;
public:
	int rows;
	int columns;
	//Empty constructor
	matrix();
	//Parametrized constructor
	matrix(int r, int c);
	//Destructor
	~matrix();

	//get and set
	double get_at(int r, int c);
	void set_at(int r, int c, double var);
	void reset_to(double var);
	void reset_to_random();


	//display matrix
	void print();
	void print_dim();

	//operators
	matrix& operator=(matrix R);
	friend matrix operator+(matrix A, matrix B);
	friend matrix operator-(matrix A, matrix B);
	friend matrix operator*(matrix A, matrix B);
	friend matrix operator*(matrix A, double x);
	friend matrix operator*(double x, matrix A);
	friend matrix operator!(matrix A);

	friend matrix element_wise_product(matrix A, matrix B);
};