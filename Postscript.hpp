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

#endif
