/*
 * TextureFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREFACTORY_HPP
#define TEXTUREFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Octree.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
using namespace std;


class TextureFactory : public Factory {
	
	public:
		
		TextureFactory();
		virtual Node *create(const Tag &tag) const;
};


#endif
