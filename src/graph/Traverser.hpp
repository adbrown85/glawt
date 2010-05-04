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
#include "Selectable.hpp"          // Drawing manipulators for selection
using namespace std;


class Traverser {
public:
	Traverser(Scene *scene);
	virtual void start();
protected:
	virtual void onApplicable(Applicable *node);
	virtual void onDrawable(Drawable *node);
	virtual void onSelectable(Selectable *node);
	void traverseChildren(Node *node);
	void traverseNode(Node *node);
private:
	Scene *scene;
};


#endif
