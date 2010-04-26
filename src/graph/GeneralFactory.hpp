/*
 * GeneralFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GENERALFACTORY_HPP
#define GENERALFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Cube.hpp"
#include "Cull.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Octree.hpp"
#include "Program.hpp"
#include "Scale.hpp"
#include "Shader.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translation.hpp"
#include "Target.hpp"
using namespace std;


class GeneralFactory : public Factory {
	
	public :
		
		Node *create(const Tag &tag);
};


#endif
