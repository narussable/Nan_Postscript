#include "Postscript.hpp"

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
