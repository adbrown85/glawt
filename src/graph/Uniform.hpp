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
#include <sstream>
#include <string>
#include "Node.hpp"
#include "Program.hpp"
#include "Tag.hpp"
#include "Texture.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Container for GLSL uniform variables.
 */
class Uniform : public Node,
                public Applicable {
	
	public :
		
		Uniform(string type,
		        string name,
		        GLfloat value,
		        string link="");
		Uniform(const Tag &tag);
		void associate();
		void apply();
		void finalize();
		void remove();
		string toString() const;
		
		friend ostream& operator<<(ostream &stream,
		                           const Uniform &uniform);
	
	private :
		
		bool isMatrix;
		GLenum valueType;
		GLenum matrixType;
		GLfloat value, matrix[16];
		GLint location;
		Program *program;
		static set<string> types;
		string link, name, type;
		
		void init();
		void initAsMatrix();
		static void initTypes();
		bool isSampler();
		static bool isSupported(string type);
		void loadMatrix();
		void verify();
};


#endif
