/*
 * Traverser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRAVERSER_HPP
#define TRAVERSER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Exception.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Applicable.hpp"          // Apply modifications to scene
#include "Drawable.hpp"            // Drawing items in scene
using namespace std;


/**
 * @ingroup graph
 * @brief Utility to walk through nodes that consolidates rules.
 */
class Traverser {
public:
	Traverser(Scene *scene);
	virtual void start();
protected:
	virtual void onApplicable(Applicable *node);
	virtual void onDrawable(Drawable *node);
	void traverseChildren(Node *node);
	void traverseNode(Node *node);
private:
	Scene *scene;
};


#endif
