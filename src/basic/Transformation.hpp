/*
 * Transformation.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP
#include "common.h"
#include <list>                         // Storing listeners
#include <queue>                        // Searching
#include "Node.hpp"
#include "NodeEvent.hpp"
#include "Matrix.hpp"


/**
 * @interface Transformation
 * @ingroup basic
 * @brief Operation that changes the size, position, or orientation of objects.
 */
class Transformation : public Applicable {
public:
	Transformation(const Tag &tag) : Applicable(tag) {}
	virtual void addListener(NodeListener *listener);
	static void findAll(Node *node, list<Transformation*> &L);
	virtual void fireEvent();
	virtual void apply() = 0;
	virtual void applyTo(Matrix &matrix) = 0;
	virtual void remove() = 0;
	static list<Transformation*> search(Node *node);
private:
	NodeNotifier notifier;
};


#endif
