/*
 * Placeholder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP
#include "common.h"
#include "Node.hpp"
#include "Group.hpp"
using namespace std;


/** @brief %Node that can be replaced in groups.
 * @ingroup advanced
 */
class Placeholder : public Node {
public:
	Placeholder(const Tag &tag);
	virtual void associate();
	virtual string getName() const;
	virtual string toString() const;
	virtual void setChild(Node *node);
private:
	string name;
};

/** @return Name given to the placeholder */
inline string Placeholder::getName() const {return name;}


#endif
