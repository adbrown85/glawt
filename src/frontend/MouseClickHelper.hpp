/*
 * MouseClickHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSECLICKHELPER_HPP
#define MOUSECLICKHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Identifiable.hpp"
#include "MouseData.hpp"
#include "MouseHelper.hpp"
#include "Picker.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @brief
 *     Handles mouse clicking actions for %Mouse.
 * @ingroup frontend
 */
class MouseClickHelper : public MouseHelper {
	
	
	public :
		
		MouseClickHelper(Delegate *delegate);
		void initialize(multimap<int,Binding> bindings);
		void onClick(int button,
		             int state,
		             int x,
		             int y);
	
	
	private:
		
		void pickItem();
		void tryBindings();
		void tryBinding(Binding *binding);
};


#endif
