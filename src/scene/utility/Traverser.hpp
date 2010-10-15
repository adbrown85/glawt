/*
 * Traverser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRAVERSER_HPP
#define TRAVERSER_HPP
#include "common.h"
#include "Exception.hpp"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Scene.hpp"
using namespace std;


/** @brief Utility to walk through nodes.
 * @ingroup scene
 */
class Traverser {
public:
	Traverser(Scene *scene);
	virtual ~Traverser() {}
	virtual void start();
protected:
	void findDependents();
	Canvas* getCanvas() const;
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
	void traverseChildren(Node *node);
	void traverseNode(Node *node);
	void setCanvas(Canvas *canvas);
private:
	list<Dependent*> dependents;
	Scene *scene;
	Canvas *canvas;
};

/** Sets the canvas that will be used for dependent nodes. */
inline void Traverser::setCanvas(Canvas *c) {canvas = c;}

/** @return %Canvas used for dependent nodes. */
inline Canvas* Traverser::getCanvas() const {return canvas;}


#endif
