/*
 * LightColor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LIGHTCOLOR_HPP
#define LIGHTCOLOR_HPP
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Light.hpp"
#include "Node.hpp"
#include "Tag.hpp"


/**
 * @ingroup graph
 * @brief
 *     Color component of a Light.
 * 
 * Abstract base class for a light color, which provides the ability to install
 * itself into the light when the scene is prepared.
 * 
 * @see Ambient
 * @see Diffuse
 * @see Specular
 */
class LightColor : public Node {
	
	public :
		
		LightColor(const Tag &tag);
		virtual string toString() const;
	
	protected :
		
		float r, g, b;
		GLenum type;
		
		virtual void associate();
		virtual void initType() = 0;
};


#endif
