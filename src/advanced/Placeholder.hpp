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
class Placeholder : public Node, public Nameable {
public:
	Placeholder(const Tag &tag);
	virtual bool areChildrenDestroyable() const;
	virtual void check();
	virtual void clear();
	virtual void mimic(Node *node);
	virtual string toString() const;
};

/** Makes sure any leftover children aren't destoyed twice. */
inline bool Placeholder::areChildrenDestroyable() const {return false;}

/** Clears the placeholder's children. */
inline void Placeholder::clear() {children.clear();}

#endif