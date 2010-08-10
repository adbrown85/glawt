/*
 * Transform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Matrix.hpp"
#include "State.hpp"


/** @brief Operation that changes size, position, or orientation of objects.
 * @interface Transform
 * @ingroup basic
 */
class Transform : public Node,
                  public Applicable, public NodeNotifier {
public:
	Transform(const Tag &tag) : Node(tag) {}
	static void findAll(Node *node, list<Transform*> &L);
	virtual void apply() = 0;
	virtual void applyTo(Matrix &matrix) = 0;
	virtual void remove() = 0;
	static void search(Node *node, list<Transform*> &L);
};


#endif
