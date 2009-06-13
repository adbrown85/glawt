/*
 * Uniform.hpp
 *     Container for GLSL uniform variables.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#define UNIFORM_FLOAT 1
#define UNIFORM_INT 2
#include <GL/glut.h>
#include <iomanip>
#include <iostream>



class Uniform {
	
	
	public :
		
		Uniform(std::string name,
		        std::string type,
		        GLfloat value);
		Uniform(std::string name,
		        GLfloat value);
		Uniform(std::string name,
		        GLint value);
		
		friend std::ostream& operator<<(std::ostream &stream,
		                                const Uniform &uniform);
		
		std::string getName() const;
		int getType() const;
		GLfloat getValue() const;
		void getValue(GLfloat &value) const;
		void getValue(GLint &value) const;
	
	
	private :
		
		GLfloat value;
		int type;
		std::string name;
};


#endif
