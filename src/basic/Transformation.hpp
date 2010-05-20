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
#include <list>                         // Storing listeners
#include "Applicable.hpp"
#include "NodeEvent.hpp"


/**
 * @interface Transformation
 * @ingroup basic
 * @brief Operation that changes the size, position, or orientation of objects.
 */
class Transformation : public Applicable {
public:
	Transformation(const Tag &tag) : Applicable(tag) {}
	virtual void addListener(NodeListener *listener);
	virtual void fireEvent();
	virtual void apply() = 0;
	virtual void remove() = 0;
private:
	NodeNotifier notifier;
};


#endif
