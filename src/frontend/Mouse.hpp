/*
 * Mouse.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseClickHelper.hpp"
#include "MouseData.hpp"
#include "MouseHelper.hpp"
#include "MouseDragHelper.hpp"
#include "Scene.hpp"
#include "Translator.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     %Mouse control for the %Display.
 * 
 * @todo
 *     Need to deallocate manipulators.
 */
class Mouse : public Control {
	
	public:
		
		Mouse(Delegate *delegate,
		      Scene *scene);
		virtual void install();
		static void onClick(int button,
		                    int action,
		                    int x,
		                    int y);
		static void onDrag(int x,
		                   int y);
	
	protected:
		
		void initBindings();
		void initData();
		void initManipulators();
	
	private:
		
		MouseClickHelper clickHelper;
		MouseData data;
		MouseDragHelper dragHelper;
		static Mouse *obj;
};


#endif
