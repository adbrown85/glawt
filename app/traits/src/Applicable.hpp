/*
 * Applicable.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __APPLICABLE_HPP__
#define __APPLICABLE_HPP__
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
