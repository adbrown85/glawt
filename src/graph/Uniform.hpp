/*
 * Uniform.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <string>
#include "Program.hpp"
using std::ostream;
using std::string;



/**
 * @brief
 *     Container for GLSL uniform variables.
 * @ingroup graph
 */
class Uniform {
	
	
	public :
		
		GLfloat value;
		char type;
		string name;
		
		Uniform(string name,
		        GLfloat value);
		Uniform(string name,
		        GLint value);
		Uniform(string name,
		        GLfloat value,
		        char type);
		void install(const Program &program);
		
		friend ostream& operator<<(ostream &stream,
		                           const Uniform &uniform);
};


#endif
