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
#include "Node.hpp"
#include "Program.hpp"
using std::ostream;
using std::string;



/**
 * @brief
 *     Container for GLSL uniform variables.
 * @ingroup graph
 */
class Uniform : public Node {
	
	
	public :
		
		Uniform(string name,
		        GLfloat value,
		        char type);
		void associate();
		void finalize();
		void print() const;
		
		friend ostream& operator<<(ostream &stream,
		                           const Uniform &uniform);
	
	
	private :
		
		char type;
		GLfloat value;
		Program *program;
		string name;
		
		Uniform();
		void install();
};


#endif
