/*
 * SimpleTransformable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SIMPLETRANSFORMABLE_HPP
#define SIMPLETRANSFORMABLE_HPP
#include "common.h"
#include <cfloat>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Transform.hpp"
using namespace std;


/** @brief Simple implementation of %Transformable.
 * @ingroup basic
 */
class SimpleTransformable : public Node,
                            public Transformable,
                            public NodeListener {
public:
	SimpleTransformable(const Tag &tag);
	virtual void associate();
	virtual Extent getExtent();
	virtual Vector getPosition();
	virtual Matrix getTransformation();
	virtual Matrix getTransformationInverse();
	virtual void onNodeEvent(NodeEvent &event);
protected:
	void updatePositionExtent();
private:
	bool valid;
	list<Transform*> transforms;
	Extent extent;
	Vector position;
	Matrix transformation;
};

/** Invalidates the position when a transform changes. */
inline void SimpleTransformable::onNodeEvent(NodeEvent &event) {valid = false;}


#endif
