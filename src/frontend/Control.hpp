/*
 * Control.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "Binding.hpp"
#include "Interpreter.hpp"
#include "Manipulator.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Interface installed into a %Display that controls the scene.
 */
class Control {
public:
	Control(Interpreter *interpreter);
	virtual ~Control();
	virtual void add(const Binding &binding);
	virtual void add(Manipulator *manipulator);
	virtual vector<Manipulator*> getManipulators() const;
	virtual void install() = 0;
	virtual void print();
	virtual void setManipulators(vector<Manipulator*> manipulators);
protected:
	Interpreter *interpreter;
	multimap<int,Binding> bindings;
	Scene *scene;
	string type;
	vector<Manipulator*> manipulators;
};


#endif
