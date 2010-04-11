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
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Interface installed into a %Display that controls the scene.
 */
class Control {
	
	public :
		
		Control(Delegate *delegate);
		~Control();
		
		void add(const Binding &binding);
		void add(Manipulator *manipulator);
		virtual vector<Manipulator*> install(Scene *scene) = 0;
		void print();
	
	protected :
		
		Delegate *delegate;
		multimap<int,Binding> bindings;
		Scene *scene;
		string type;
		vector<Manipulator*> manipulators;
};


#endif
