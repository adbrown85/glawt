/*
 * Shadow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADOW_HPP
#define SHADOW_HPP
#include "common.h"
#include "Group.hpp"
#include "Light.hpp"
using namespace std;


/** @brief Shadow map generated from a light and a group.
 * @ingroup advanced
 */
class Shadow : public Node,
               public NodeListener {
public:
	Shadow(const Tag &tag);
	virtual void associate();
	virtual void onNodeEvent(NodeEvent &event);
	virtual string toString() const;
protected:
	void findGroup();
	void findLight();
	void findTransforms();
private:
	string of, from;
	Group *group;
	Light *light;
};


#endif
