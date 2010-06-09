/*
 * Control.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CONTROL_HPP
#define CONTROL_HPP
#include "common.h"
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
using namespace std;


/** @brief Interface installed into a %Display that controls the scene.
 * @ingroup gui
 */
class Control {
public:
	Control(Delegate *delegate);
	virtual ~Control();
	virtual void add(Binding binding);
	virtual void add(Manipulator *manipulator);
	Binding* getBinding(const Combo &combo);
	virtual map<Combo,Binding> getBindings();
	virtual list<Manipulator*> getManipulators() const;
	virtual void install() = 0;
	virtual void load() = 0;
	virtual void print();
	virtual void setManipulators(list<Manipulator*> manipulators);
protected:
	Delegate *delegate;
	map<Combo,Binding> bindings;
	Scene *scene;
	Canvas *canvas;
	string type;
	list<Manipulator*> manips;
};

/* Get and set the control's manipulators. */
inline list<Manipulator*> Control::getManipulators() const {return manips;}
inline void Control::setManipulators(list<Manipulator*> m) {manips = m;}

/* Get the control's bindings */
inline map<Combo,Binding> Control::getBindings() {return bindings;}


#endif
