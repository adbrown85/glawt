/*
 * MouseHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSEHELPER_HPP
#define MOUSEHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include "Control.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseData.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Generic handler for a mouse action.
 */
class MouseHelper : public Control {
	
	public:
		
		MouseHelper(Delegate *delegate);
		virtual int getModifier();
		virtual void initialize(MouseData *data);
		virtual void initialize(multimap<int,Binding> bindings) = 0;
		virtual void initialize(vector<Manipulator*> manipulators);
		virtual vector<Manipulator*> install(Scene *scene);
		virtual void updateCurrentData(int x, int y);
		virtual void updateLastData();
	
	protected:
		
		MouseData *data;
};


#endif
