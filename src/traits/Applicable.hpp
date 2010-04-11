/*
 * Applicable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef APPLICABLE_HPP
#define APPLICABLE_HPP
#include <cstdlib>
#include <iostream>


/**
 * @interface Applicable
 * @ingroup traits
 * @brief
 *     Interface for something that can be applied, and then removed.
 */
class Applicable {
	
	public :
		
		virtual void apply() = 0;
		virtual void remove() = 0;
};


#endif
