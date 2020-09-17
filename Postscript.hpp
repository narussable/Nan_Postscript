#ifndef POSTSCRIPT_HPP
#define POSTSCRIPT_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Nvector.hpp"

class Postscript : public std::ofstream{
	private:
		double xp, yp;

	public:
		Postscript(const char* name);
		~Postscript(void);
	
		void move(double=0,double=0);
		void line(double=0,double=0);
};

Postscript::Postscript(const char * name) : ofstream(name+".ps"){
	*this << "%PS\n\n"
		  << "8.5 2 div 72 mul\n"
	      << "11  2 div 72 mul\n"
		  << "translate\n\n"	  
		  << "72 2.54 div"	  
		  << "72 2.54 div"	  
		  << "scale\n\n"	  
		  << "0.02 setlinewidth\n";	  
	move();
}

void Postscript::move(double x, double y){
	this->xp = x;
	this->yp = y;
	*this << x << ' ' << y << " moveto\n";
}

void Postscript::line(double x, double y){
	this->xp = x;
	this->yp = y;
	*this << x << ' ' << y << " lineto\n";
}


#endif
