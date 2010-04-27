/*
 * TransformFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORMFACTORY_HPP
#define TRANSFORMFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Scale.hpp"
#include "Translation.hpp"
using namespace std;


class TransformFactory : public Factory {
	
	public:
		
		TransformFactory();
		virtual Node *create(const Tag &tag) const;
};


#endif
