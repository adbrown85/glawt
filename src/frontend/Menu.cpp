/*
 * Menu.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Menu.hpp"
Menu *Menu::menu=NULL;


Menu::Menu(Delegate *delegate,
           Scene *scene) :
           Control(delegate, scene) {
	
	Menu::menu = this;
	type = "Menu";
}


/**
 * Installs the Menu into the display.
 */
void Menu::install() {
	
	// Make menus
	installItemMenu();
	installMainMenu();
}


/**
 * Make the menu for when an item is selected.
 */
void Menu::installItemMenu() {
	
	vector<int> opts;
	vector<int>::iterator o;
	
	// Add items to list
	opts.push_back(Command::DESELECT);
	opts.push_back(Command::SELECT_ALL);
	opts.push_back(Command::HIDE);
	
	// Make menu
	itemMenuID = glutCreateMenu(Menu::onClick);
	for (o=opts.begin(); o!=opts.end(); o++)
		glutAddMenuEntry(Command::getName(*o).c_str(), *o);
	
	// Attach
	glutSetMenu(itemMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/**
 * Make the main menu.
 */
void Menu::installMainMenu() {
	
	vector<int> opts;
	vector<int>::iterator o;
	
	// Add items to list
	opts.push_back(Command::SELECT_ALL);
	opts.push_back(Command::DESELECT);
	opts.push_back(Command::HIDE);
	opts.push_back(Command::SHOW_ALL);
	opts.push_back(Command::RESET);
	
	// Make menu
	mainMenuID = glutCreateMenu(Menu::onClick);
	for (o=opts.begin(); o!=opts.end(); o++)
		glutAddMenuEntry(Command::getName(*o).c_str(), *o);
	
	// Attach
	glutSetMenu(mainMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/**
 * Passes option to interpreter as commands.
 */
void Menu::onClick(GLint option) {
	
	menu->delegate->run(option);
	glutPostRedisplay();
}

