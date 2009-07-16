/*
 * Transformation.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP
#include <cstdlib>
#include <iostream>
#include "Applicable.hpp"
#include "Node.hpp"



class Transformation : public Applicable,
                       public Node {
	
	
	public :
		
		virtual void apply() = 0;
		virtual void remove() = 0;
};


#endif
