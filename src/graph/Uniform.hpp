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
#include <set>
#include <string>
#include "Node.hpp"
#include "Program.hpp"
#include "Texture.hpp"
using namespace std;



/**
 * @brief
 *     Container for GLSL uniform variables.
 * @ingroup graph
 */
class Uniform : public Node,
                public Applicable {
	
	
	public :
		
		Uniform(string type,
		        string name,
		        GLfloat value,
		        string link="");
		void associate();
		void apply();
		void finalize();
		void print() const;
		void remove();
		
		friend ostream& operator<<(ostream &stream,
		                           const Uniform &uniform);
	
	
	private :
		
		GLenum valueType;
		GLfloat value;
		GLint location;
		Program *program;
		static set<string> types;
		string link, name, type;
		
		Uniform();
		static void initTypes();
		bool isSampler();
		static bool isSupported(string type);
		void verify();
};


#endif
