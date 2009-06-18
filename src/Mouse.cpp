/*
 * Mouse.cpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Mouse.hpp"
Mouse *Mouse::obj=NULL;
set<int> Mouse::spcs;



/**
 * Installs the control into the current context.
 */
void Mouse::install() {
	
	// Register functions
	Mouse::obj = this;
	className = "Mouse";
	bindings();
	specials();
	print();
	glutMouseFunc(Mouse::mouse);
	glutMotionFunc(Mouse::motion);
}



/**
 * Rotates or translates the scene by dragging one of the mouse buttons.
 */
void Mouse::motion(int x,
                   int y) {
	
	int count, xDif, yDif;
	Item *itm;
	Vector pos;
	
	
	xDif = obj->xLast - x;
	yDif = obj->yLast - y;
	
	if (obj->state->manAct == true) {
		count = obj->scene->items.size();
		for (int i=0; i<count; i++) {
			itm = obj->scene->items[i];
			if (itm->isSelected()) {
				pos = itm->getPosition();
				itm->setPosition(pos.x, pos.y+yDif*0.01, pos.z);
			}
		}
	}
	
	else {
		// Drag in X
		if (obj->dragX) {
			obj->del->run(obj->dragXCmd, obj->dragXArg * xDif);
		}
		
		// Drag in Y
		if (obj->dragY) {
			obj->del->run(obj->dragYCmd, obj->dragYArg * yDif);
		}
	}
	
	// Refresh
	obj->xLast = x;
	obj->yLast = y;
	glutPostRedisplay();
}



/**
 * Handles mouse clicks.
 */
void Mouse::mouse(int button,
                  int state,
                  int x,
                  int y) {
	
	Binding *bin;
	int mod;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> ran;
	multimap<int,Binding>::iterator bi;
	
	// Lookup
	mod = glutGetModifiers();
	if (mod == 1 || mod == 5)
		mod -= 1;
	ran = obj->bins.equal_range(button);
	for (bi=ran.first; bi!=ran.second; ++bi) {
		bin = &bi->second;
		if (bin->getModifier() == mod) {
			if (bin->hasDrag()) {
				if (bin->getState() == Binding::DRAG_X) {
					if (state == GLUT_DOWN) {
						obj->dragXCmd = bin->getCommand();
						obj->dragXArg = bin->getArgument();
						obj->xLast = x;
						obj->dragX = true;
					}
					else {
						obj->dragX = false;
					}
				}
				else if (bin->getState() == Binding::DRAG_Y) {
					if (state == GLUT_DOWN) {
						obj->dragYCmd = bin->getCommand();
						obj->dragYArg = bin->getArgument();
						obj->yLast = y;
						obj->dragY = true;
					}
					else {
						obj->dragY = false;
					}
				}
			}
			else if (state == bin->getState()) {
				if (needsCoordinates(bin->getCommand()))
					obj->del->run(bin->getCommand(), x, y);
				else if (bin->hasArgument())
					obj->del->run(bin->getCommand(), bin->getArgument());
				else
					obj->del->run(bin->getCommand());
				glutPostRedisplay();
			}
		}
	}
	
	// Clear manipulator
	if (state == GLUT_UP)
		obj->state->setManipulator(false);
}



/**
 * Checks if a command needs coordinates.
 */
bool Mouse::needsCoordinates(int cmd) {
	
	set<int>::iterator si;
	
	// Check if in vector
	si = spcs.find(cmd);
	return si != spcs.end();
}
