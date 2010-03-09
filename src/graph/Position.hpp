/*
 * Position.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef POSITION_HPP
#define POSITION_HPP
#include <cstdlib>
#include <iostream>
#include "Light.hpp"
#include "Node.hpp"
#include "Tag.hpp"



/**
 * @ingroup graph
 * @brief
 *     %Position for a light.
 */
class Position : public Node {
	
	
	public :
		
		Position(const Tag &tag);
		virtual string toString() const;
	
	
	private:
		
		float x, y, z;
		
		virtual void associate();
};


#endif
