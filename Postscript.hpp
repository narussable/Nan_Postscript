#ifndef POSTSCRIPT_HPP
#define POSTSCRIPT_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Vector.hpp"

class Postscript : public std::ofstream{
	private:
		double xp, yp;

	public:
		Postscript(const char* name);
		~Postscript(void);
	
		void move(double=0,double=0);
		void line(double=0,double=0);

		void fill(void);
		void setColor(double=0,double=0,double=0);
};

//------------------------------------------------------
//---------------- CONSTRUCTOR DESCTUCTOR --------------
//------------------------------------------------------

//This constructor takes a 'string' that will be the name of the 
// postscript file (<name_file>.ps) and writes down the main header
// for it. Scales the unit 1:1cm and sets the center of the page as
// the (0,0) coord.
Postscript::Postscript(const char * name) : std::ofstream(name){
	std::cerr << "Postscript editor open . . .\n";
	*this << "%PS\n\n"
		  << "8.5 2 div 72 mul\n"
	      << "11  2 div 72 mul\n"
		  << "translate\n\n"	  
		  << "72 2.54 div\n"	  
		  << "72 2.54 div\n"	  
		  << "scale\n\n"	  
		  << "0.02 setlinewidth\n";	  
	move();
}

Postscript::~Postscript(void){
	*this << "\nstroke\n"
		  << "showpage\n";
	std::cerr << "Postscript editor closed . . .\n";
}

//------------------------------------------------------
//---------------- 2D POSTSCIPT METHODS ----------------
//------------------------------------------------------

//This method interprets the two double, as the coordinates in the
// and move the pen (without painting).
void Postscript::move(double x, double y){
	this->xp = x;
	this->yp = y;
	*this << x << ' ' << y << " moveto\n";
}

//This method interprets the two double, as the coordinates in the
// and draw the pen (painting).
void Postscript::line(double x, double y){
	this->xp = x;
	this->yp = y;
	*this << x << ' ' << y << " lineto\n";
}

//------------------------------------------------------
//----------------- POSTSCIPT METHODS ------------------
//------------------------------------------------------

void Postscript::fill(void){
	*this << "\nstroke\n"
		  << "fill\n\n";
	this->move(this->xp,this->yp);
}

void Postscript::setColor(double _r, double _g, double _b){
	_r /= 100;
	_g /= 100; 
	_b /= 100;
	*this << "\nstroke\n" 
		  << _r << " " << _g << " " << _b << " setrgbcolor\n\n"; 
	this->move(this->xp,this->yp);
}

class Perspective : public Postscript{
	private:
		Vec3D screen;
		Vec3D    cam;
		double  fact;

	public:
		Perspective(double=60,double=30);

		VectorND Pers(const Vec3D&);
		void     move(const Vec3D&);
		void     line(const Vec3D&);
};

Perspective::Perspective(double _Zo, double _Zp) : Postscript("Perspective.ps"){
	screen = Vec3D(0,0,_Zp);
	cam    = Vec3D(0,0,_Zo);
}

VectorND Perspective::Pers(const Vec3D& v){
	double fact = this->cam.d(this->screen) / this->cam.d(VectorND{0,0,v[2]});
	return VectorND{fact*v[0],fact*v[1]};
}

void Perspective::move(const Vec3D& v){
	VectorND 3D_Pencil = this->Pers(v);
	Postscript::move(3D_Pencil[0],3D_Pencil[1]); 	
}

void Perspective::line(const Vec3D& v){
	VectorND 3D_Pencil = this->Pers(v);
	Postscript::line(3D_Pencil[0],3D_Pencil[1]); 	
}

#endif