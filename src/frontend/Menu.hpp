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
		
		Menu(Delegate *delegate,
		     Scene *scene);
		virtual void install();
		void installItemMenu();
		void installMainMenu();
		static void onClick(GLint option);
	
	private:
		
		static Menu *menu;
		int mainMenuID, itemMenuID;
};


#endif
