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
#include "Tag.hpp"
using namespace std;


/** @brief Reusable collection of nodes.
 * @ingroup advanced
 */
class Group : public Node {
public:
	Group(const Tag &tag);
	virtual bool areChildrenTraversable() const;
	virtual bool areChildrenPreparable() const;
	static Group* find(Node *node, const string &name);
	string getName() const;
	virtual string toString() const;
private:
	string name;
};


inline bool Group::areChildrenTraversable() const {return false;}
inline bool Group::areChildrenPreparable() const {return false;}
inline string Group::getName() const {return name;}


#endif
