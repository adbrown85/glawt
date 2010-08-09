/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include "common.h"
#include "Link.hpp"
#include "Shape.hpp"
using namespace std;


/** @brief Simple reuse of a group.
 * 
 * @warning Should only be used when the group itself includes the only program 
 * needed by the nodes in the group, or if all instances will be under the 
 * same program.  Otherwise, use Clone or Replica.
 * 
 * @see Clone
 * @see Replica
 * 
 * @ingroup basic
 */
class Instance : public Node, public Applicable {
public:
	Instance(const Tag &tag);
	virtual void apply();
	virtual bool areChildrenSelectable() const;
	virtual void associate();
	virtual void finalize();
	virtual void remove();
	virtual string toString() const;
public:  // Accessors and mutators
	virtual string getOf() const;
	virtual void setOf(const string &of);
protected:
	void findExclusions();
	Link* getLink();
private:
	string of, only;
	list<Shape*> exclusions;
	bool selectable;
	Link *link;
};

inline bool Instance::areChildrenSelectable() const {return selectable;}
inline Link* Instance::getLink() {return link;}
inline string Instance::getOf() const {return of;}
inline void Instance::setOf(const string &of) {this->of = of; link->setTo(of);}


#endif
