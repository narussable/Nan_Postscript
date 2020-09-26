#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <iostream>
#include <vector>
#include <cmath>

class VectorND{	
	private:
		double  * V;
		double norm;
		int       n;

		void updateNorm(void);
		void initMem(int=0);

	public:
		VectorND (std::initializer_list<double>);
		VectorND (double *, int n);
		VectorND (int=0);
		~VectorND(void);

		void       changeDim(int);
		int       dim(void) const;
		double        norma(void);
		double d(const VectorND&);            

		double&   operator [] (int);
		double    operator [] (int) const;
		VectorND& operator =  (const VectorND&);
};

void VectorND::updateNorm(void){
	double sum = 0.0;
	for(int index=0; index<this->n; ++index)
		sum += this->V[index]*this->V[index];
	this->norm = sqrt(sum);
}

void VectorND::initMem(int dim){
	this->V = (double*) malloc (dim*sizeof(double));
	this->n = dim;
}

VectorND::VectorND(int dim)
{   this->initMem(dim);	  }

VectorND::VectorND(std::initializer_list<double> _list){
	this->n = _list.size();
	this->initMem(_list.size());
	for(int index=0; index<_list.size(); ++index)
		this->V[index] = _list.begin()[index];
}

VectorND::VectorND(double * _list, int dim){
	this->n = dim;
	this->initMem(dim);
	for(int index=0; index<dim; ++index)
		this->V[index] = _list[index];
}

VectorND::~VectorND(void)
{ 	free(this->V); 	}

void VectorND::changeDim(int dim){
	this->n = dim;
	this->V = (double*) realloc (this->V,dim*sizeof(double));
}

double VectorND::norma(void){
	this->updateNorm();
	return this->norm;
}

double VectorND::d(const VectorND& v){
	double sum = 0.0;
	if(this->n==v.dim()){
		for(int index=0; index<v.dim(); ++index)
			sum += this->V[index]-v[index];
		return sqrt(sum);
	}	
	else
		std::cout << "ERROR --- Dimension problems in v1.d(v2)" << std::endl;
}
	
int VectorND::dim(void) const
{ 	return this->n;  	}

double&   VectorND::operator [] (int index)
{ 	return this->V[index%this->n]; 	}

double    VectorND::operator [] (int index) const
{ 	return this->V[index%this->n]; 	}

VectorND& VectorND::operator = (const VectorND& copy_vector){
	this->n = copy_vector.dim();
	this->initMem(copy_vector.dim());
	for(int index=0; index<copy_vector.dim(); ++index)
		this->V[index] = copy_vector[index];
	return *this;
}

VectorND operator + (const VectorND& v1, const VectorND& v2){
	VectorND output(0);
	if(v1.dim()==v2.dim()){
		output.changeDim(v1.dim());
		for(int index=0; index<v1.dim(); ++index)
			output[index] = v1[index] + v2[index];
	}
	else
		std::cout << " ERROR --- Dimension problems with + operator" << std::endl;
	return output;
}

VectorND operator - (const VectorND& v1, const VectorND& v2){
	VectorND output(0);
	if(v1.dim()==v2.dim()){
		output.changeDim(v1.dim());
		for(int index=0; index<v1.dim(); ++index)
			output[index] = v1[index] - v2[index];
	}
	else
		std::cout << " ERROR --- Dimension problems with - operator" << std::endl;
	return output;
}

VectorND operator * (double r, const VectorND& v){
	VectorND out(v.dim());
	for(int index=0; index<v.dim(); ++index)
		out[index] = r * v[index];
	return out;
}

double operator * (const VectorND& v1, const VectorND& v2){	
	double sum = 0.0;
	if(v1.dim()==v2.dim()){
		for(int index=0; index<v1.dim(); ++index)
			sum += v1[index] * v2[index];
	}
	else
		std::cout << " ERROR --- Dimension problems with - operator" << std::endl;
	return sum;
}

std::ostream& operator << (std::ostream& out, const VectorND& v){
	out << '<';
	for(int index=0; index<v.dim(); ++index)
		(index!=v.dim()-1) ? out << v[index] << ',' : out << v[index] << '>';
	return out;
}

class Vec3D : public VectorND{
	public:
		Vec3D(double=0,double=0,double=0);
};

Vec3D::Vec3D(double x, double y, double z) : VectorND{x,y,z}{}

Vec3D operator % (const Vec3D& v1, const Vec3D& v2){
	Vec3D output;
	output[0] = v1[1]*v2[2] - v1[2]*v2[1];
	output[1] = v1[2]*v2[0] - v1[0]*v2[2];
	output[2] = v1[0]*v2[1] - v1[1]*v2[0];
	return output;
}

#endif