/*
 * Uniform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "Node.hpp"
#include "Program.hpp"
#include "Tag.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
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
		
		enum MatrixType{MODELVIEW, PROJECTION, MODELVIEW_PROJECTION};
		
		bool isMatrix;
		GLenum valueType;
		MatrixType matrixType;
		GLfloat matrix[16], value;
		GLint location;
		Program *program;
		static set<string> types;
		string link, name, type;
		
		void applyAsMatrix();
		void applyAsValue();
		void init();
		void initAsMatrix();
		static void initTypes();
		bool isSampler();
		static bool isSupported(string type);
		void loadMatrix();
		void verify();
};


#endif
