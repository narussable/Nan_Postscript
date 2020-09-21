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
		bool d(const VectorND&);

		double&   operator [] (int);
		double    operator [] (int) const;
		VectorND& operator += (const VectorND&);
		VectorND& operator -= (const VectorND&);
};

// ------------------------------------------------
// ------------- PRIVATE - METHODS ----------------
// ------------------------------------------------

void VectorND::updateNorm(void){
    double sum = 0.0;
    for(int index=0; index<this->n; ++index)
        sum += this->V[index];
    this->norma = sqrt(sum);
}

// ------------------------------------------------
// ---------- CONSTRUCTOR - DESTRUCTOR ------------
// ------------------------------------------------

//This is a fast constructor for VectorND, where you give
// the entries of the vector. The syntaxis is the following:
//          VectorND <name_vector> {1,0.4,0.3}
VectorND::VectorND(std::initializer_list<double> array){
    this->n = array.size();
    for(int index=0; index<array.size(); ++index)
        this->V[index] = array.begin()[index];
}

//This constructor does the same as the last one, nevertheless
// this is build with dynamic memory. The syntaxis to use it is:   
//          VectorND <name_vector> (<double_pointer>,<int_dimension>) 
VectorND::VectorND(double * array, int dim){
    this->n = dim; 
    for(int index=0; index<dim; ++index)
        this->V[index] = array[index];
}

//This constructor is used just when you don't want to define itself in that
// moment, but you know you will need it. This sets just the dimension of the
// vector. The syntaxis is:
//          VectorND <name_vector> (<int_dimension>)
VectorND::VectorND(int dim)
{   this->n = dim;    }

// ------------------------------------------------
// --------------- PUBLIC METHODS -----------------
// ------------------------------------------------

int VectorND::dim(void) const
{   return this->n;     }

double VectorND::d(double p1, double p2)
{   return (p2-p1)<0 ? p1-p2 : p2-p1;   }

bool VectorND::d(const VectorND& s_vector){
    bool Same_Entries = true;
    if( this->n==s_vector.dim() ){
        double epsilon = 10E-6;
        for(int index=0; index<s_vector.dim(); ++index)
            std::cout << "perreo epstremo";
    }
    else
        std::cout << "Dimension problem in distance comparison" << std::endl;
    return Same_Entries;
}

// ------------------------------------------------
// --------------- PUBLIC METHODS -----------------
// ------------------------------------------------

//This operator returns a reference to an specific entry
// in the vector, so you can access (read/write). The 
// the syntaxis is the same as in an array in C:
//          <vector_name>[<int_index>]
double& VectorND::operator [] (int index)
{   return this->V[index%this->n];      }

double  VectorND::operator [] (int index) const
{   return this->V[index%this->n];      }

//This method takes a VectorND as a parameter, in order to use
// the cannonical addition. The syntaxis for this operator is:
//          <reference_vector> += <adding_vector>
VectorND& VectorND::operator += (const VectorND& sum_vector){
    if(this->n==sum_vector.dim()){
        for(int index=0; index<this->n; ++index)
            this->V[index] += sum_vector[index];
    }
    else
        std::cout << "Dimension error in += operator . . ." << std::endl;
    return *this;
}

//This method takes a VectorND as a parameter, in order to use
// the cannonical substraction. The syntaxis for this operator is:
//          <reference_vector> -= <adding_vector>
VectorND& VectorND::operator -= (const VectorND& sum_vector){
    if(this->n==sum_vector.dim()){
        for(int index=0; index<this->n; ++index)
            this->V[index] -= sum_vector[index];
    }
    else
        std::cout << "Dimension error in += operator . . ." << std::endl;
    return *this;
}

// ------------------------------------------------
// -------------- EXTERN OPERATORS ----------------
// ------------------------------------------------

bool operator == (VectorND& f_vector, VectorND& s_vector)
{   return f_vector.d(s_vector);   }

std::ostream& operator << (std::ostream& os, const VectorND& da_vector){
    os << '<';
    for(int index=0; index<da_vector.dim(); ++index)
        index!=(da_vector.dim()-1) ? os << da_vector[index] << ',' : os << da_vector[index] << '>';
    return os;
}

VectorND operator + (const VectorND& v1, const VectorND v2){
	VectorND out( v1.dim() );
	if( v1.dim()==v2.dim() ){
		for(int index=0; index<v1.dim(); ++index)
			out[index] = v1[index] + v2[index];
	}
	else
		std::cout << "Dimension problems in the + operator" << std::endl;
	return out;
}

VectorND operator - (const VectorND& v1, const VectorND v2){
	VectorND out( v1.dim() );
	if( v1.dim()==v2.dim() ){
		for(int index=0; index<v1.dim(); ++index)
			out[index] = v1[index] - v2[index];
	}
	else
		std::cout << "Dimension problems in the - operator" << std::endl;
	return out;
}

#endif
