/*
 * Painter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PAINTER_HPP
#define PAINTER_HPP
#include "common.h"
#include <vector>
#include "Manipulator.hpp"         // Drawing manipulators for selection
#include "Node.hpp"                // Traversing the scene graph
#include "Program.hpp"             // Disable GLSL for outlines
#include "Texture.hpp"             // Pausing and restarting texturing
#include "Transform.hpp"           // Drawing manipulators for selection
#include "Scene.hpp"               // Rotating camera and accessing root node
#include "Vector.hpp"
#include "SubsceneUser.hpp"
#define PAINTER_SUBSCENE "ui/outline.xml"
using namespace std;


/** @brief Paints all the items to the screen or pick buffer.
 * @ingroup gui
 * 
 * @warning Does not flush to the buffer.
 */
class Painter : public Traverser, public SubsceneUser {
public:
	Painter(Canvas *canvas, Scene *scene);
	void addManipulator(Manipulator *manipulator);
	virtual void start();
protected:
	virtual void onDrawable(Node *node, Drawable *drawable);
private:
	vector<Manipulator*> manipulators;
};

/** Stores a manipulator to paint for selected items. */
inline void Painter::addManipulator(Manipulator *m) {manipulators.push_back(m);}


#endif
