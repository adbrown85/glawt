/*
 * RenderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef RENDERFACTORY_HPP
#define RENDERFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Cull.hpp"
#include "Framebuffer.hpp"
#include "Target.hpp"
using namespace std;


class RenderFactory : public Factory {
	
	public:
		
		RenderFactory();
		virtual Node *create(const Tag &tag) const;
};


#endif
