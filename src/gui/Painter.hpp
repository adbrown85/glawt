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
#include "Matrix.hpp"              // Rotating camera
#include "Node.hpp"                // Traversing the scene graph
#include "Program.hpp"             // Disable GLSL for outlines
#include "Texture.hpp"             // Pausing and restarting texturing
#include "Transform.hpp"           // Drawing manipulators for selection
#include "Traverser.hpp"
#include "Scene.hpp"               // Rotating camera and accessing root node
#include "Vector.hpp"
using namespace std;


/** @brief Paints all the items to the screen or pick buffer.
 * @ingroup gui
 * 
 * @warning Does not flush to the buffer.
 */
class Painter : public Traverser {
public:
	Painter(Canvas *canvas, Scene *scene);
	virtual ~Painter();
	void addManipulator(Manipulator *manipulator);
	virtual void start();
	void setMode(GLenum mode);
protected:
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
private:
	static bool tried;
	GLenum mode;
	static Scene *outline;
	vector<Manipulator*> manipulators;
};

/** Stores a manipulator to paint for selected items. */
inline void Painter::addManipulator(Manipulator *m) {manipulators.push_back(m);}

/** Sets the rendering mode. */
inline void Painter::setMode(GLenum mode) {this->mode = mode;}


#endif
