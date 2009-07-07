/*
 * Uniform.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#define UNIFORM_FLOAT 1
#define UNIFORM_INT 2
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <string>
using std::ostream;
using std::string;



/**
 * @brief
 *     Container for GLSL uniform variables.
 * @ingroup core
 */
class Uniform {
	
	
	public :
		
		Uniform(string name, string type, GLfloat value);
		Uniform(string name, GLfloat value);
		Uniform(string name, GLint value);
		
		friend ostream& operator<<(ostream &stream, const Uniform &uniform);
		
		string getName() const {return name;}
		int getType() const {return type;}
		GLfloat getValue() const {return value;}
		void getValue(GLfloat &value) const {value = this->value;}
		void getValue(GLint &value) const {value = int(this->value);}
	
	
	private :
		
		GLfloat value;
		int type;
		string name;
};


#endif
