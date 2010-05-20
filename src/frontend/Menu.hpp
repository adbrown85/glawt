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
#include "Control.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Right-click menu for the %Display.
 */
class Menu : public Control {
public:
	Menu(Interpreter *interpreter);
	virtual void install();
	static void onClick(GLint option);
protected:
	void installItemMenu();
	void installMainMenu();
private:
	static Menu *instance;
	int mainMenuID, itemMenuID;
};


#endif
