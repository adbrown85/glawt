/*
 * Light.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LIGHT_HPP
#define LIGHT_HPP
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
 * @ingroup graph
 * @brief
 *     %Light in the scene.
 * 
 * @see Position
 * @see Ambient
 * @see Diffuse
 * @see Specular
 */
class Light : public Node,
              public Applicable {
	
	public :
		
		Light(const Tag &tag);
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
		
		GLenum getHandle() const {return handle;}
		
		static Light* find(Node *node);
	
	private:
		
		GLenum handle;
		
		static int active_lights;
		
		virtual void associate();
};


#endif
