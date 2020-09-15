#ifndef NVECTOR_HPP
#define NVECTOR_HPP

#include <initializer_list>
#include <iostream>
#include <vector>
#include <cmath>

class VectorND{
	private:
		double   *   V;
		double   norma;
		int          n;

		void updateNorm(void);
	public:
		VectorND(std::initializer_list<double>);
		VectorND(double*,int=3);
		VectorND(int=3);	

		int      dim(void) const;
		double d(double, double);
		double d(const VectorND&);

		double&   operator [] (int);
		double    operator [] (int) const;
		VectorND& operator += (const VectorND&);
		VectorND& operator -= (const VectorND&);
};

bool operator == (const VectorND&, const VectorND&);
bool operator != (const VectorND&, const VectorND&);

#endif
