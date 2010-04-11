/*
 * Menu.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MENU_HPP
#define MENU_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Right-click menu for the %Display.
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
