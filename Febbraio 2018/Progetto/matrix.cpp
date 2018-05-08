#include "matrix.h"

//Empty constructor
matrix::matrix()
{
	rows = 1;
	columns = 1;
	data_matrix.clear();
	data_matrix.resize(1,0);
}
//Parametrized constructor
matrix::matrix(int r, int c)
{
	rows = r;
	columns = c;
	data_matrix.clear();
	data_matrix.resize(r*c,0);
}
//Destructor
matrix::~matrix()
{
	//Deallocate vector
	data_matrix.clear();
}

//get and set
double matrix::get_at(int r, int c)
{
	int linear_position = r*columns +c;
	return data_matrix.at(linear_position);
}
void matrix::set_at(int r, int c, double var)
{
	int linear_position = r*columns +c;
	data_matrix.at(linear_position) = var;
	return;
}
void matrix::reset_to(double var)
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			set_at(r, c, var);
		}
	}
	return;
}
void matrix::reset_to_random()
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			double var = rand() / double(RAND_MAX);
			set_at(r, c, var);
		}
	}
	return;
}

//display matrix
void matrix::print()
{
	std::cout<<"Stampo matrice di dimensione ("<<rows<<", "<<columns<<")"<<std::endl;
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			std::cout<<get_at(r,c)<<"\t";
		}
		std::cout<<std::endl;
	}
	return;
}
void matrix::print_dim()
{
	std::cout<<"Stampo matrice di dimensione ("<<rows<<", "<<columns<<")"<<std::endl;
	return;
}

//operators
matrix& matrix::operator=(matrix R)
{
	rows = R.rows;
	columns = R.columns;
	data_matrix.clear();
	data_matrix.resize(rows*columns,0);
	for (int r = 0; r < R.rows; ++r)
	{
		for (int c = 0; c < R.columns; ++c)
		{
			double var = R.get_at(r,c);
			set_at(r, c, var);
		}
	}
	return *this;
}
matrix operator+(matrix A, matrix B)
{
	//Check dimension
	if((A.rows != B.rows) or (A.columns != B.columns))
	{
		std::cerr	<<"FATAL Error. Adding two non-compatible matrix: "
					<<"("<<A.rows<<", "<<A.columns<<") and "
					<<"("<<B.rows<<", "<<B.columns<<")"<<std::endl;
		exit(EXIT_FAILURE);

	}

	matrix R(A.rows, A.columns);
	for (int r = 0; r < A.rows; ++r)
	{
		for (int c = 0; c < A.columns; ++c)
		{
			double var = A.get_at(r,c) + B.get_at(r, c);
			R.set_at(r, c, var);
		}
	}
	return R;
}
matrix operator-(matrix A, matrix B)
{
	//Check dimension
	if((A.rows != B.rows) or (A.columns != B.columns))
	{
		std::cerr	<<"FATAL Error. Subtracting two non-compatible matrix: "
					<<"("<<A.rows<<", "<<A.columns<<") and "
					<<"("<<B.rows<<", "<<B.columns<<")"<<std::endl;
		exit(EXIT_FAILURE);

	}

	matrix R(A.rows, A.columns);
	for (int r = 0; r < A.rows; ++r)
	{
		for (int c = 0; c < A.columns; ++c)
		{
			double var = A.get_at(r,c) - B.get_at(r, c);
			R.set_at(r, c, var);
		}
	}
	return R;
}
matrix operator*(matrix A, matrix B)
{
	//if A is nXm and B is mXp -> AB=nXp
	//Check dimension
	if((A.columns != B.rows))
	{
		std::cerr	<<"FATAL Error. Multiplying two non-compatible matrix: "
					<<"("<<A.rows<<", "<<A.columns<<") and "
					<<"("<<B.rows<<", "<<B.columns<<")"<<std::endl;
		exit(EXIT_FAILURE);
	}

	matrix R(A.rows, B.columns);
	for (int i = 0; i < A.rows; ++i)
	{
		for (int j = 0; j < B.columns; ++j)
		{
			double res = 0.0;
			for (int k = 0; k < A.columns; ++k)
			{
				res += (A.get_at(i,k)*B.get_at(k,j));
			}
			R.set_at(i, j, res);
		}
	}
	return R;
}
matrix operator*(matrix A, double x)
{
	//Check dimension not needed
	matrix R(A.rows, A.columns);
	for (int r = 0; r < A.rows; ++r)
	{
		for (int c = 0; c < A.columns; ++c)
		{
			double var = x * A.get_at(r,c);
			R.set_at(r, c, var);
		}
	}
	return R;
}
matrix operator*(double x, matrix A)
{
	matrix R = A*x;
	return R;
}
matrix operator!(matrix A)
{
	//Transpose
	matrix R(A.columns, A.rows);
	for (int i = 0; i < A.rows; ++i)
	{
		for (int j = 0; j < A.columns; ++j)
		{
			double var = A.get_at(i, j);
			R.set_at(j, i, var);
		}
	}

	return R;
}
matrix element_wise_product(matrix A, matrix B)
{
	//Check dimension
	if((A.rows != B.rows) or (A.columns != B.columns))
	{
		std::cerr	<<"FATAL Error. Multiplying element-wise two non-compatible matrix: "
					<<"("<<A.rows<<", "<<A.columns<<") and "
					<<"("<<B.rows<<", "<<B.columns<<")"<<std::endl;
		exit(EXIT_FAILURE);

	}

	matrix R(A.rows, A.columns);
	for (int r = 0; r < A.rows; ++r)
	{
		for (int c = 0; c < A.columns; ++c)
		{
			double var = A.get_at(r,c) * B.get_at(r, c);
			R.set_at(r, c, var);
		}
	}
	return R;
}