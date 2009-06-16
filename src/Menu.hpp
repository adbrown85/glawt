/*
 * Menu.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __MENU_HEADER__
#define __MENU_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include "Command.hpp"
#include "Control.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Menu : public Control {
	
	
	public :
		
		Menu() {Menu::menu = this;}
		
		static void handler(GLint option);
		void install();
		void menuItem();
		void menuMain();
		void print();
	
	
	private:
		
		static Menu *menu;
		int menuMainID, menuItemID;
};


#endif
