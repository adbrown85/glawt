/*
 * MouseHelper.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef MOUSEHELPER_HPP
#define MOUSEHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Control.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseData.hpp"
#include "Scene.hpp"
using std::vector;
using std::multimap;



class MouseHelper : public Control {
	
	
	public:
		
		MouseHelper(Delegate *delegate);
		int getModifier();
		void initialize(MouseData *data);
		virtual void initialize(multimap<int,Binding> bindings) = 0;
		void initialize(vector<Manipulator*> manipulators);
		vector<Manipulator*> install(Scene *scene);
	
	
	protected:
		
		MouseData *data;
};


#endif
