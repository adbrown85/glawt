/*
 * Group.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GROUP_HPP
#define GROUP_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Reusable collection of nodes.
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
