#include "matrix.h"

matrix::matrix()
{
	rows = 1;
	columns = 1;
	data = new double[1];
	data[0] = 0;
}

matrix::matrix(int x, int y)
{
	rows = x;
	columns = y;
	//data = (double *)malloc((rows*columns) * sizeof (double));
	data = new double[rows*columns];
	return;
}

bool matrix::set_at(int x, int y, double var)
{
	if((x>=0)and(x<rows))
	{
		if((y>=0)and(y<columns))
		{
			data[columns * x + y] = var;
			return true;
		}
	}
	std::cerr<<"Errore nella scrittura in "<<x<<", "<<y<<" nella matrice "<<rows<<", "<<columns<<std::endl;
	exit(-1);
	return false;
}

double matrix::get_at(int x, int y)
{
	if((x>=0)and(x<rows))
	{
		if((y>=0)and(y<columns))
		{
			return data[columns * x + y];
		}
	}
	std::cerr<<"Errore nella lettura in "<<x<<", "<<y<<" nella matrice "<<rows<<", "<<columns<<std::endl;
	exit(-1);
	return false;
}

pair matrix::dimension()
{
	pair dim;
	dim.first=rows;
	dim.second=columns;
	return dim;
}

void matrix::print_dimension()
{
	std::cout<<"("<<rows<<", "<<columns<<")";
	return;
}

void matrix::display()
{
	std::cout<<"Stampo Matrice "<<rows<<" x "<<columns<<std::endl;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			std::cout<<std::setprecision(3)<<std::fixed<<data[columns * i + j]<<"\t";
		}
		std::cout<<std::endl;
	}
}

matrix::matrix(char nome_file[80])
{
	FILE* f = fopen(nome_file, "r");
	float d;
	int r,c;
	if(f != NULL)
	{
		fscanf(f,"DIM %d%d",&r,&c);
		rows = r;
		columns = c;
		data = (double *)malloc((rows*columns) * sizeof (double));
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				fscanf(f, "%f", &d);
				set_at(i, j, d);
			}
		}
	}

	fclose(f);
	return;
}

void matrix::reset_to(double var)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			set_at(i, j, var);
		}
	}
	return;
}

void matrix::reset_to_random()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			double r = ((double) rand() / (RAND_MAX));
			set_at(i, j, r);
		}
	}
	return;
}
/*
matrix matrix::operator=(matrix original)
{
	printf("Assegnazione tramite LucaNet = nelle matrici\n");
	int original_rows = original.dimension().first;
	int original_columns = original.dimension().second;
	matrix R(original_rows, original_columns);
	
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			int var = original.get_at(i,j);
			R.set_at(i, j, var);
		}
	}
	return R;
}
*/


/*
matrix::matrix(matrix& original)
{
	
	int original_rows = original.dimension().first;
	int original_columns = original.dimension().second;
	rows = original_rows;
	columns = original_columns;
	data = new double[rows*columns];
	
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			double var = original.get_at(i,j);
			set_at(i, j, var);
		}
	}
}
*/





matrix matrix_addition(matrix A, matrix B)
{
	matrix r(A.dimension().first, A.dimension().second);
	//Controllo dimensioni
	if((A.dimension().first == B.dimension().first) and (A.dimension().second == B.dimension().second))
	{
		for (int i = 0; i < A.dimension().first; ++i)
		{
			for (int j = 0; j < A.dimension().second; ++j)
			{
				double a = A.get_at(i,j);
				double b = B.get_at(i,j);
				r.set_at(i, j, a+b);
			}
		}
	}else
	{
		std::cerr<<"Errore, addizione non avvenuta"<<std::endl;
		std::cerr<<"Dim A: ("<<A.dimension().first<<", "<<A.dimension().second<<")\tDIM B: ("<<B.dimension().first<<", "<<B.dimension().second<<")"<<std::endl;
		exit(-1);
		//Controllo degli errori
	}
	return r;
}


matrix matrix_subtraction(matrix A, matrix B)
{
	matrix r(A.dimension().first, A.dimension().second);
	//Controllo dimensioni
	if((A.dimension().first == B.dimension().first) and (A.dimension().second == B.dimension().second))
	{
		for (int i = 0; i < A.dimension().first; ++i)
		{
			for (int j = 0; j < A.dimension().second; ++j)
			{
				double a = A.get_at(i,j);
				double b = B.get_at(i,j);
				r.set_at(i, j, a-b);
			}
		}
	}else
	{
		std::cerr<<"Errore, sottrazione non avvenuta"<<std::endl;
		std::cerr<<"Dim A: ("<<A.dimension().first<<", "<<A.dimension().second<<")\tDIM B: ("<<B.dimension().first<<", "<<B.dimension().second<<")"<<std::endl;
		exit(-1);
		//Controllo degli errori
	}
	return r;
}

matrix matrix_product(matrix A, matrix B)
{
	//if A is nXm and B is mXp -> AB=nXp
	matrix r(A.dimension().first, B.dimension().second);
	if(A.dimension().second == B.dimension().first)
	{
		for (int i = 0; i < A.dimension().first; ++i)
		{
			for (int j = 0; j < B.dimension().second; ++j)
			{
				double res = 0.0;
				for (int k = 0; k < A.dimension().second; ++k)
				{
					res += (A.get_at(i,k)*B.get_at(k,j));
				}
				r.set_at(i, j, res);
			}
		}
	}else
	{
		std::cerr<<"Errore dimensioni moltiplicazione incompatibili"<<std::endl;
		std::cerr<<"Dim A: ("<<A.dimension().first<<", "<<A.dimension().second<<")\tDIM B: ("<<B.dimension().first<<", "<<B.dimension().second<<")"<<std::endl;
		exit(-1);
	}

	return r;
}

matrix matrix_elementwise_product(matrix A, matrix B)
{
	matrix R(A.dimension().first, B.dimension().second);
	if((A.dimension().first == B.dimension().first)and(A.dimension().second == B.dimension().second))
	{
		for (int i = 0; i < A.dimension().first; ++i)
		{
			for (int j = 0; j < A.dimension().second; ++j)
			{
				R.set_at(i,j, A.get_at(i, j)*B.get_at(i, j));
			}
		}
	}else
	{
		std::cerr<<"Errore dimensioni moltiplicazione elementwise incompatibili"<<std::endl;
		std::cerr<<"Dim A: ("<<A.dimension().first<<", "<<A.dimension().second<<")\tDIM B: ("<<B.dimension().first<<", "<<B.dimension().second<<")"<<std::endl;
		exit(-1);
	}
	return R;
}

matrix matrix_scalar_product(matrix A, double lambda)
{
	matrix R(A.dimension().first, A.dimension().second);
	for (int i = 0; i < A.dimension().first; ++i)
	{
		for (int j = 0; j < A.dimension().second; ++j)
		{
			double var = A.get_at(i, j);
			var *= lambda;
			R.set_at(i, j, var);
		}
	}
	return R;
}


matrix matrix_transpose(matrix A)
{
	matrix R(A.dimension().second, A.dimension().first);
	for (int i = 0; i < A.dimension().first; ++i)
	{
		for (int j = 0; j < A.dimension().second; ++j)
		{
			R.set_at(j, i, A.get_at(i, j));
		}
	}

	return R;
}



matrix operator+(matrix A, matrix B)
{
	matrix r(A.dimension().first, A.dimension().second);
	//Controllo dimensioni
	if((A.dimension().first == B.dimension().first) and (A.dimension().second == B.dimension().second))
	{
		for (int i = 0; i < A.dimension().first; ++i)
		{
			for (int j = 0; j < A.dimension().second; ++j)
			{
				double a = A.get_at(i,j);
				double b = B.get_at(i,j);
				r.set_at(i, j, a+b);
			}
		}
	}else
	{
		std::cerr<<"Errore, addizione non avvenuta"<<std::endl;
		std::cerr<<"Dim A: ("<<A.dimension().first<<", "<<A.dimension().second<<")\tDIM B: ("<<B.dimension().first<<", "<<B.dimension().second<<")"<<std::endl;
		exit(-1);
		//Controllo degli errori
	}
	return r;
}