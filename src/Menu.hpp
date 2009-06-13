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
#include <map>
#include <string>
#include "Scene.hpp"
enum {
	MENU_DELETE,
	MENU_DESELECT,
	MENU_DESELECT_ALL,
	MENU_DUPLICATE,
	MENU_HIDE,
	MENU_RESET,
	MENU_REVERT,
	MENU_SAVE,
	MENU_SELECT_ALL,
	MENU_SHOW_ALL
};



class Menu {
	
	
	public :
		
		static void handler(GLint option);
		static void initialize();
		static void install(Scene *scene);
		static void menuItem();
		static void menuMain();
		static void print();
	
	
	private:
		
		static Scene *scene;
		static std::map<int,std::string> map;
		static std::map<int,std::string>::iterator mi;
		
		static int menuMainID, menuItemID;
};


#endif
