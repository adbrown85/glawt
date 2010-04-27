/*
 * ShapeFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHAPEFACTORY_HPP
#define SHAPEFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Cube.hpp"
#include "Fullscreen.hpp"
#include "Square.hpp"
using namespace std;


class ShapeFactory : public Factory {
	
	public:
		
		ShapeFactory();
		virtual Node *create(const Tag &tag) const;
};


#endif
