/*
 * Picker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PICKER_HPP
#define PICKER_HPP
#include "common.h"
#include "Manipulator.hpp"         // Pass to Painter, check if picked
#include "Traverser.hpp"           // Traversing the subscene
#include "Scout.hpp"               // Finding nodes in the subscene
#include "Renderbuffer.hpp"
#include "Choose.hpp"
#include "UniformInt.hpp"
#define PICKER_SUBSCENE "ui/pick.xml"
using namespace std;


/** @brief Determines which item is under the mouse cursor.
 * @ingroup gui
 */
class Picker : public Traverser {
public:
	Picker(Scene *scene, Canvas *canvas);
	virtual ~Picker();
	void addManipulators(list<Manipulator*> manipulators);
	pair<GLuint,GLuint> pick(int x, int y);
protected:
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
	void renderHotspots(Node *node);
	void openSubscene();
	void prepareSubscene();
	void destroySubscene();
private:
	list<Manipulator*> manipulators;
	Scene *subscene;
	Traverser *traverser;
	Choose *choose;
	UniformInt *itemIDUniform, *sourceIDUniform;
	Renderbuffer *buffer;
};


/*
protected:
	pair<GLuint,GLuint> chooseItem();
	void finish();
	void initialize(int x, int y);
	void storeIDsOfItems();
*/

#endif
