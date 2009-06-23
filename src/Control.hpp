/*
 * Control.hpp
 *     Interface for a display control.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __CONTROL_HEADER__
#define __CONTROL_HEADER__
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "Scene.hpp"
using std::multimap;
using std::string;
using std::pair;
using std::vector;



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
