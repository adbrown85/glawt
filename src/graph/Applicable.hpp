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
#include "Node.hpp"


/**
 * @ingroup graph
 * @brief %Node that can be applied, and then removed.
 */
class Applicable : public Node {
public:
	virtual void apply() = 0;
	virtual void remove() = 0;
};


#endif
