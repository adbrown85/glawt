/*
 * Transformation.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__
#include <cstdlib>
#include <iostream>
#include "Applicable.hpp"
#include "Node.hpp"



class Transformation : public Applicable,
                       public Node {
	
	
	public :
		
		void apply() = 0;
		void remove() = 0;
};


#endif
