/*
 * Scout.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef Scout_HPP
#define Scout_HPP
#include "common.h"
#include "Node.hpp"
using namespace std;


/** @brief Utility for finding nodes in a scene.
 * @ingroup scene
 */
class Scout {
public:
	static Node* search(Node *root, const string &type);
};


#endif
