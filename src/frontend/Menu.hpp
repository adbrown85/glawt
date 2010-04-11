/*
 * Menu.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef __MENU_HEADER__
#define __MENU_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using std::vector;



/**
 * @brief
 *     Right-click menu for the %Display.
 * @ingroup frontend
 */
class Menu : public Control {
	
	
	public :
		
		Menu(Delegate *delegate) : Control(delegate) {
			Menu::menu = this;
		}
		
		static void handler(GLint option);
		vector<Manipulator*> install(Scene *scene);
		void menuItem();
		void menuMain();
		void print();
	
	
	private:
		
		static Menu *menu;
		int menuMainID, menuItemID;
};


#endif
