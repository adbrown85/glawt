/*
 * Diffuse.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "Light.hpp"
#include "LightColor.hpp"
#include "Tag.hpp"


/**
 * @ingroup graph
 * @brief
 *     Part of the light that creates smooth shading across the entire surface.
 */
class Diffuse : public LightColor {
	
	public:
		
		Diffuse(const Tag &tag);
	
	protected:
		
		virtual void initType();
};


#endif
