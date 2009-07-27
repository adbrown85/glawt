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
class Uniform : public Node {
	
	
	public :
		
		Uniform(string type,
		        string name,
		        GLfloat value);
		void associate();
		void finalize();
		void print() const;
		
		friend ostream& operator<<(ostream &stream,
		                           const Uniform &uniform);
	
	
	private :
		
		GLfloat value;
		Program *program;
		string name, type;
		
		static set<string> types;
		
		Uniform();
		void initSupportedTypes();
		void install();
		
		static void initTypes();
		static bool isSupported(string type);
};


#endif
