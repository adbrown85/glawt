/*
 * Cull.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CULL_HPP
#define CULL_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Applicable.hpp"
#include "Node.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief
 *     Removes back or front-facing polygons.
 */
class Cull : public Node,
             public Applicable {
	
	public :
		
		Cull(const Tag &tag);
		void apply();
		void remove();
		string toString() const;
	
	private:
		
		bool enabled;
		GLenum faces;
		string facesString;
};


#endif
