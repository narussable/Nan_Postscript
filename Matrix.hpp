#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

class Matrix{
	private:
		double * (*M);
		int      m, n;

		void initMem(int=0,int=0);
	public:
		Matrix(int,int);
};

void Matrix::initMem(int _m, int _n){
	this->m  = _m;
	this->n  = _n;
	this->M = (double**) malloc (_m * sizeof(double*));
	for(double * array : this->M)
		array = (double*) malloc (n * sizeof(double));
}

Matrix::Matrix(int m, int n)
{ 	this->initMem(m,n); 	}

#endif