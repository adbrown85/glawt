/*
 * Control.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CONTROL_HPP
#define CONTROL_HPP
#include "common.h"
#include <map>                          // Storing bindings
#include <list>                         // Storing manipulators
#include <utility>                      // Pair
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
using namespace std;


/* Functor for comparing combos. */
class ComboComparator {
public:
	bool compareTriggers(const Combo &A, const Combo &B);
	bool compareModifiers(const Combo &A, const Combo &B);
	bool compareActions(const Combo &A, const Combo &B);
	bool operator()(const Combo &A, const Combo &B);
};


/**
 * @ingroup frontend
 * @brief Interface installed into a %Display that controls the scene.
 */
class Control {
public:
	Control(Delegate *delegate);
	virtual ~Control();
	virtual void add(Binding binding);
	virtual void add(Manipulator *manipulator);
	Binding* getBinding(const Combo &combo);
	virtual list<Manipulator*> getManipulators() const;
	virtual void install() = 0;
	virtual void print();
	virtual void setManipulators(list<Manipulator*> manipulators);
protected:
	Delegate *delegate;
	map<Combo,Binding,ComboComparator> bindings;
	Scene *scene;
	Canvas *canvas;
	string type;
	list<Manipulator*> manips;
};

/* Get and set the control's manipulators. */
inline list<Manipulator*> Control::getManipulators() const {return manips;}
inline void Control::setManipulators(list<Manipulator*> m) {manips = m;}

/* Compares two combos by comparing their triggers, modifiers, and actions. */
inline bool ComboComparator::operator()(const Combo &A, const Combo &B) {
	return compareTriggers(A, B);
}

/* Compares the triggers of two combos. */
inline bool ComboComparator::compareTriggers(const Combo &A, const Combo &B) {
	if (A.trigger < B.trigger) {
		return true;
	} else if (A.trigger > B.trigger) {
		return false;
	} else {
		return compareModifiers(A, B);
	}
}

/* Compares the modifiers of two combos. */
inline bool ComboComparator::compareModifiers(const Combo &A, const Combo &B) {
	if (A.modifier < B.modifier) {
		return true;
	} else if (A.modifier > B.modifier) {
		return false;
	} else {
		return compareActions(A, B);
	}
}

/* Compares the actions of two combos. */
inline bool ComboComparator::compareActions(const Combo &A, const Combo &B) {
	if (A.action < B.action) {
		return true;
	} else if (A.action > B.action) {
		return false;
	} else {
		return false;
	}
}


#endif
