/*
 * Transformation.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP
#include <cstdlib>
#include <iostream>
#include "Applicable.hpp"
#include "Node.hpp"


/**
 * @interface Transformation
 * @ingroup basic
 * @brief
 *     Operation that changes the size, position, or orientation of objects.
 */
class Transformation : public Node,
                       public Applicable {
	
	public :
		
		virtual void apply() = 0;
		virtual void remove() = 0;
};


#endif
