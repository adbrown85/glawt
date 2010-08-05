/*
 * Link.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LINK_HPP
#define LINK_HPP
#include "common.h"
#include "Group.hpp"
using namespace std;


/** @brief Simple connection to a %Group.
 * @ingroup basic
 */
class Link : public Node {
public:
	Link(const Tag &tag);
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
	virtual void establish();
	virtual void relink();
	virtual string toString() const;
private:
	Group *group;
	string to;
};

inline bool Link::areChildrenDestroyable() const {return false;}
inline bool Link::areChildrenPrintable() const {return false;}


#endif
