/*
 * Menu.cpp
 *     Pop-up menu for 3D display.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Menu.hpp"
int Menu::menuMainID, Menu::menuItemID;
Scene *Menu::scene=NULL;
std::map<int,std::string> Menu::map;
std::map<int,std::string>::iterator Menu::mi;



void Menu::handler(GLint option) {
	
	switch (option) {
		case MENU_DELETE :
			std::cerr << map[option] << std::endl; break;
		case MENU_DESELECT :
			std::cerr << map[option] << std::endl; break;
		case MENU_DESELECT_ALL :
			std::cerr << map[option] << std::endl; break;
		case MENU_DUPLICATE :
			std::cerr << map[option] << std::endl; break;
		case MENU_HIDE :
			std::cerr << map[option] << std::endl; break;
		case MENU_RESET :
			std::cerr << map[option] << std::endl; break;
		case MENU_REVERT :
			std::cerr << map[option] << std::endl; break;
		case MENU_SAVE :
			std::cerr << map[option] << std::endl; break;
		case MENU_SELECT_ALL :
			std::cerr << map[option] << std::endl; break;
		case MENU_SHOW_ALL :
			std::cerr << map[option] << std::endl; break;
		default :
			break;
	}
}



void Menu::initialize() {
	
	// Initialize map
	map[MENU_DELETE] = "Delete";
	map[MENU_DESELECT] = "Deselect";
	map[MENU_DESELECT_ALL] = "Deselect All";
	map[MENU_DUPLICATE] = "Duplicate";
	map[MENU_HIDE] = "Hide";
	map[MENU_RESET] = "Reset";
	map[MENU_REVERT] = "Revert";
	map[MENU_SAVE] = "Save";
	map[MENU_SELECT_ALL] = "Select All";
	map[MENU_SHOW_ALL] = "Show All";
}



void Menu::install(Scene *scene) {
	
	std::cerr << "Menu::install()" << std::endl;
	
	// Initialize options
	initialize();
	menuMain();
	menuItem();
	
	glutSetMenu(menuMainID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



void Menu::menuItem() {
	
	static std::vector<int> list;
	static std::vector<int>::iterator it;
	
	// Add items to list
	list.push_back(MENU_DESELECT_ALL);
	list.push_back(MENU_SELECT_ALL);
	list.push_back(MENU_DUPLICATE);
	list.push_back(MENU_HIDE);
	list.push_back(MENU_DELETE);
	
	// Make menu
	menuItemID = glutCreateMenu(handler);
	for (it=list.begin(); it!=list.end(); it++)
		glutAddMenuEntry(map[*it].c_str(), *it);
}



void Menu::menuMain() {
	
	static std::vector<int> list;
	static std::vector<int>::iterator it;
	
	// Add items to list
	list.push_back(MENU_SELECT_ALL);
	list.push_back(MENU_SAVE);
	list.push_back(MENU_REVERT);
	
	// Make menu
	menuMainID = glutCreateMenu(handler);
	for (it=list.begin(); it!=list.end(); it++)
		glutAddMenuEntry(map[*it].c_str(), *it);
}



/**
 * Prints the descriptions in the menu.
 */
void Menu::print() {
	
	// Print
	std::cerr << "All menu commands: " << std::endl;
	for (mi=map.begin(); mi!=map.end(); mi++)
		std::cerr << mi->first << " " << mi->second << std::endl;
}
