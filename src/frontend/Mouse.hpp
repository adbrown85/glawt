/*
 * Mouse.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __MOUSE_HEADER__
#define __MOUSE_HEADER__
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Identifiable.hpp"
#include "Manipulator.hpp"
#include "Picker.hpp"
#include "Scene.hpp"
#include "Translator.hpp"
#include "Vector.hpp"
using std::map;
using std::multimap;
using std::pair;
using std::vector;



/**
 * @brief
 *     %Mouse control for the %Display.
 * @ingroup frontend
 * 
 * @todo
 *     Need to deallocate manipulators.
 */
class Mouse : public Control {
	
	
	public :
		
		Mouse(Delegate *delegate) : Control(delegate) {}
		void dragHandler(int x,
		                 int y);
		void clickHandler(int button,
		                  int action,
		                  int x,
		                  int y);
		vector<Manipulator*> install(Scene *scene);
		
		static void dragCallback(int x,
		                         int y);
		static void clickCallback(int button,
		                          int action,
		                          int x,
		                          int y);
	
	
	private :
		
		unsigned int currentItemID, dragCount;
		Manipulator *currentManipulator;
		map<char,Binding*> dragBindings;
		Vector dragAxis, dragDirection, lastCursorPosition;
		
		static Mouse *obj;
		
		void dragDecideAxis(const Vector &movement);
		bool dragUseConstrained();
		void installBindings();
		void installCallbacks();
		void installManipulators();
		void pickItem(int button,
		              int x,
		              int y);
		void tryBinding(Binding *binding,
		                int state);
};


#endif
