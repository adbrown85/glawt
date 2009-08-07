/*
 * MouseDragHelper.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef MOUSEDRAGHELPER_HPP
#define MOUSEDRAGHELPER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <vector>
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseData.hpp"
#include "MouseHelper.hpp"
#include "Vector.hpp"
using std::multimap;
using std::vector;



/**
 * @brief
 *     Handles mouse dragging actions for %Mouse.
 * @ingroup frontend
 */
class MouseDragHelper : public MouseHelper {
	
	
	public :
		
		MouseDragHelper(Delegate *delegate);
		void initialize(multimap<int,Binding> bindings);
		void onDrag(int x,
		            int y);
	
	
	private:
		
		Vector axis, direction, movement;
		static char directions[2];
		
		void decideAxis();
		void tryBinding(Binding *binding);
		void tryBindings();
		bool useConstrained();
};


#endif
