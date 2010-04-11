/*
 * Menu.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Menu.hpp"
Menu *Menu::menu=NULL;


/**
 * Eventually will take the option and send it to the Interpreter.
 * 
 * @note Handler is the same between all Menu classes.
 */
void Menu::handler(GLint option) {
	
	menu->delegate->run(option);
	glutPostRedisplay();
}


/**
 * Installs the Menu into the display.
 */
vector<Manipulator*> Menu::install(Scene *scene) {
	
	// Initialize attributes
	this->scene = scene;
	type = "Menu";
	
	// Make menus
	menuMain();
	menuItem();
	
	// Attach
	glutSetMenu(menuMainID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	// Finish
	return manipulators;
}


/**
 * Make the menu for when an item is selected.
 */
void Menu::menuItem() {
	
	vector<int> opts;
	vector<int>::iterator o;
	
	// Add items to list
	opts.push_back(Command::DESELECT);
	opts.push_back(Command::SELECT_ALL);
	opts.push_back(Command::HIDE);
	
	// Make menu
	menuItemID = glutCreateMenu(Menu::handler);
	for (o=opts.begin(); o!=opts.end(); o++)
		glutAddMenuEntry(Command::getName(*o).c_str(), *o);
}


/**
 * Make the main menu.
 */
void Menu::menuMain() {
	
	vector<int> opts;
	vector<int>::iterator o;
	
	// Add items to list
	opts.push_back(Command::SELECT_ALL);
	opts.push_back(Command::DESELECT);
	opts.push_back(Command::HIDE);
	opts.push_back(Command::SHOW_ALL);
	opts.push_back(Command::RESET);
	
	// Make menu
	menuMainID = glutCreateMenu(handler);
	for (o=opts.begin(); o!=opts.end(); o++)
		glutAddMenuEntry(Command::getName(*o).c_str(), *o);
}

