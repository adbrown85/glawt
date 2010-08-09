/*
 * Transformation.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeEvent.hpp"
#include "Matrix.hpp"


/** @brief Operation that changes size, position, or orientation of objects.
 * @interface Transformation
 * @ingroup basic
 */
class Transformation : public Node,
                       public Applicable, public NodeNotifier {
public:
	Transformation(const Tag &tag) : Node(tag) {}
	static void findAll(Node *node, list<Transformation*> &L);
	virtual void apply() = 0;
	virtual void applyTo(Matrix &matrix) = 0;
	virtual void remove() = 0;
	static list<Transformation*> search(Node *node);
};


#endif
