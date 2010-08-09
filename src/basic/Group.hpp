/*
 * Group.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GROUP_HPP
#define GROUP_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;


/** @brief Collection of nodes.
 * @ingroup basic
 */
class Group : public Node, public Nameable {
public:
	Group(const Tag &tag);
	virtual bool areChildrenTraversable() const;
	virtual bool areChildrenPreparable() const;
	static Group* find(Node *node);
	static Group* find(Node *node, const string &name);
	virtual string toString() const;
};

inline bool Group::areChildrenTraversable() const {return false;}
inline bool Group::areChildrenPreparable() const {return false;}


#endif
