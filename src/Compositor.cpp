/*
 * Compositor.cpp
 *     Responsible for hiding items and showing information.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Compositor.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Compositor::Compositor() {
	
	std::map<int,void(Compositor::*)()>::iterator h;
	
	// Set type
	type = "Compositor";
	
	// Add handlers
	hans[Command::HIDE] = &Compositor::cmdHide;
	hans[Command::INFORMATION] = &Compositor::cmdInfo;
	hans[Command::SHOW_ALL] = &Compositor::cmdShowAll;
	
	// Copy commands
	for (h=hans.begin(); h!=hans.end(); h++)
		cmds.push_back(h->first);
}



void Compositor::cmdHide() {
	
	int count;
	
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		if (scene->items[i]->isSelected()) {
			scene->items[i]->setShown(false);
			scene->items[i]->setSelected(false);
		}
	}
}



void Compositor::cmdInfo() {
	
	cout << "Compositor::cmdInfo()" << endl;
}



void Compositor::cmdShowAll() {
	
	int count;
	
	count = scene->items.size();
	for (int i=0; i<count; i++)
		scene->items[i]->setShown(true);
}



/**
 * Interprets a command.
 */
void Compositor::run(int command) {
	
	void (Compositor::*method)();
	
	// Filter command to correct method
	method = hans[command];
	(this->*method)();
}
