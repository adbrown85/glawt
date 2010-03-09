/*
 * Ambient.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef AMBIENT_HPP
#define AMBIENT_HPP
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Light.hpp"
#include "LightColor.hpp"
#include "Tag.hpp"


/**
 * @ingroup graph
 * @brief
 *     Part of the light that is always visible.
 */
class Ambient : public LightColor {
	
	public:
		
		Ambient(const Tag &tag);
	
	protected:
		
		virtual void initType();
};


#endif
