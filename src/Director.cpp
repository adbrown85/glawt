/*
 * Director.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Director.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Director::Director() {
	
	std::map<int,void(Director::*)(int)>::iterator h0;
	std::map<int,void(Director::*)(int,float)>::iterator h1;
	
	// Set type
	type = "Director";
	
	// Add zero-argument handlers
	hans0[Command::DESELECT] = &Director::cmdSelect;
	hans0[Command::NEXT] = &Director::cmdIterate;
	hans0[Command::PREVIOUS] = &Director::cmdIterate;
	hans0[Command::SELECT_ALL] = &Director::cmdSelect;
	
	// Add one-argument handlers
	hans1[Command::GRAB] = &Director::cmdGrab;
	
	// Copy commands
	for (h0=hans0.begin(); h0!=hans0.end(); h0++)
		cmds.push_back(h0->first);
	for (h1=hans1.begin(); h1!=hans1.end(); h1++)
		cmds.push_back(h1->first);
}



/**
 * Picks an item in the scene based on coordinates.
 */
void Director::cmdGrab(int cmd, float id) {
	
	Item *item;
	
	// Find item and set selected
	item = scene->getItem(static_cast<int>(id));
	if (item != NULL)
		item->toggleSelected();
}



/**
 * Iterates through the items in the scene.
 */
void Director::cmdIterate(int cmd) {
	
	std::cout << "Director::cmdIterate(int)" << std::endl;
}



/**
 * Selects all or none.
 */
void Director::cmdSelect(int cmd) {
	
	switch (cmd) {
		case Command::SELECT_ALL :
			scene->selectAll();
			break;
		case Command::DESELECT :
			scene->deselectAll();
			break;
		default :
			break;
	}
	glutPostRedisplay();
}



/**
 * Interprets a command.
 */
void Director::run(int command) {
	
	void (Director::*method)(int);
	
	// Filter command to correct method
	method = hans0[command];
	(this->*method)(command);
}



/**
 * Interprets a command.
 */
void Director::run(int command, float argument) {
	
	void (Director::*method)(int,float);
	
	// Filter command to correct method
	method = hans1[command];
	(this->*method)(command, argument);
}
