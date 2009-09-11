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



/**
 * Hides the items currently selected.
 * 
 * @param scene
 *     Pointer to a collection of nodes.
 * @param cmd
 *     Specific command that was issued.
 */
void Compositor::hide(Scene *scene,
                      int cmd) {
	
	Selection::iterator si;
	
	// Hide and clear the selection
	for (si=scene->selection.begin(); si!=scene->selection.end(); ++si)
		(*si)->hide();
	scene->selection.clear();
}



/**
 * Displays info about the scene on the screen.
 * 
 * @param scene
 *     Pointer to a collection of nodes.
 * @param cmd
 *     Specific command that was issued.
 */
void Compositor::info(Scene *scene,
                      int cmd) {
	
	cout << "Compositor::info(Scene*,int)" << endl;
}



/**
 * Shows all the %Drawable nodes in the scene.
 * 
 * @param scene
 *     Pointer to a collection of nodes.
 * @param cmd
 *     Specific command that was issued.
 */
void Compositor::showAll(Scene *scene,
                         int cmd) {
	
	showAll(&(scene->rootNode));
}



/**
 * Recursively shows a node and its children.
 * 
 * @param node
 *     Pointer to a node.
 */
void Compositor::showAll(Node *node) {
	
	Drawable *drawable;
	vector<Node*> children;
	
	// Show node
	drawable = dynamic_cast<Drawable*>(node);
	if (drawable != NULL)
		drawable->show();
	
	// Show children
	children = node->getChildren();
	for (int i=0; i<children.size(); ++i)
		showAll(children[i]);
}
