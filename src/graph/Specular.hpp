/*
 * Specular.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SPECULAR_HPP
#define SPECULAR_HPP
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Light.hpp"
#include "LightColor.hpp"
#include "Tag.hpp"


/**
 * @ingroup graph
 * @brief
 *     Part of the light that creates a bright hotspot on the surface.
 */
class Specular : public LightColor {
	
	public:
		
		Specular(const Tag &tag);
	
	protected:
		
		virtual void initType();
};


#endif
