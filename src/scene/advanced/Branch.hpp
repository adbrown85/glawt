/*
 * Branch.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BRANCH_HPP
#define BRANCH_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;


/** @brief One possible result of a conditional.
 * @ingroup advanced
 */
class Branch : public Node, public Nameable {
public:
	Branch(const Tag &tag);
	virtual bool areChildrenTraversable() const;
	virtual void setFollow(bool follow);
	virtual string toString() const;
private:
	bool follow;
};

/** @return True if the branch should be followed. */
inline bool Branch::areChildrenTraversable() const {return follow;}

/** Determine whether the branch should be followed. */
inline void Branch::setFollow(bool follow) {this->follow = follow;}


#endif
