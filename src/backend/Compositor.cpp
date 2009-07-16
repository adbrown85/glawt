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
	
	// Set type
	type = "Compositor";
	
	// Add handlers
	handlersZero[Command::HIDE] = &Compositor::hide;
	handlersZero[Command::INFORMATION] = &Compositor::info;
	handlersZero[Command::SHOW_ALL] = &Compositor::showAll;
}



void Compositor::hide(Scene *scene, int cmd) {
	
	std::cout << "Compositor::hide(Scene*,int)" << std::endl;
	
/*
	int count;
	
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		if (scene->items[i]->isSelected()) {
			scene->items[i]->setShown(false);
			scene->items[i]->setSelected(false);
		}
	}
*/
}



void Compositor::info(Scene *scene, int cmd) {
	
	std::cout << "Compositor::info(Scene*,int)" << std::endl;
}



void Compositor::showAll(Scene *scene, int cmd) {
	
	std::cout << "Compositor::showAll(Scene*,int)" << std::endl;
	
/*
	int count;
	
	count = scene->items.size();
	for (int i=0; i<count; i++)
		scene->items[i]->setShown(true);
*/
}
