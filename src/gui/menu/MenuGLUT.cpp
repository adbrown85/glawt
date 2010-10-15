/*
 * MenuGLUT.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MenuGLUT.hpp"
#ifdef HAVE_GLUT
MenuGLUT *MenuGLUT::instance=NULL;


MenuGLUT::MenuGLUT(Delegate *delegate) : Control(delegate) {
	
	MenuGLUT::instance = this;
	type = "MenuGLUT";
}


void MenuGLUT::addMenuEntries(list<int> &entries) {
	
	list<int>::iterator it;
	
	for (it=entries.begin(); it!=entries.end(); ++it) {
		glutAddMenuEntry(Command::getName(*it).c_str(), *it);
	}
}


void MenuGLUT::createFileMenu() {
	
	list<int> items;
	
	// Add items
	items.push_back(Command::EXIT);
	
	// Make menu
	fileMenuID = glutCreateMenu(&MenuGLUT::onClick);
	addMenuEntries(items);
}


void MenuGLUT::createEditMenu() {
	
	list<int> items;
	
	// Add items
	items.push_back(Command::SELECT_ALL);
	items.push_back(Command::DESELECT);
	items.push_back(Command::HIDE);
	items.push_back(Command::SHOW_ALL);
	
	// Make menu
	editMenuID = glutCreateMenu(&MenuGLUT::onClick);
	addMenuEntries(items);
}


void MenuGLUT::createViewMenu() {
	
	list<int> items;
	
	// Add items
	items.push_back(Command::ZOOM_IN);
	items.push_back(Command::ZOOM_OUT);
	items.push_back(Command::RESET);
	items.push_back(Command::INFORMATION);
	
	// Make menu
	viewMenuID = glutCreateMenu(&MenuGLUT::onClick);
	addMenuEntries(items);
}


/** Installs the Menu into the display. */
void MenuGLUT::install() {
	
	vector<int> opts;
	vector<int>::iterator o;
	
	// Create submenus
	createFileMenu();
	createEditMenu();
	createViewMenu();
	
	// Make menu
	mainMenuID = glutCreateMenu(MenuGLUT::onClick);
	glutAddSubMenu("File", fileMenuID);
	glutAddSubMenu("Edit", editMenuID);
	glutAddSubMenu("View", viewMenuID);
	
	// Attach
	glutSetMenu(mainMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/** Passes option to interpreter as commands. */
void MenuGLUT::onClick(GLint option) {
	
	switch (option) {
	case Command::ZOOM_IN:
	case Command::ZOOM_OUT:
		instance->delegate->run(option, 1.0);
		break;
	default:
		instance->delegate->run(option);
		break;
	}
	instance->canvas->refresh();
}



#endif // HAVE_GLUT
