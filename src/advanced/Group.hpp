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
	static Group* find(Node *node, const string &name);
	string getName() const;
	bool isSealed() const;
private:
	string name;
};


inline bool Group::isSealed() const {return true;}
inline string Group::getName() const {return name;}


#endif
