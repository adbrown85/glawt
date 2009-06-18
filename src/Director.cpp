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
	std::map<int,void(Director::*)(int,float,float)>::iterator h2;
	
	// Set type
	type = "Director";
	
	// Add zero-argument handlers
	hans0[Command::DESELECT] = &Director::cmdSelect;
	hans0[Command::NEXT] = &Director::cmdIterate;
	hans0[Command::PREVIOUS] = &Director::cmdIterate;
	hans0[Command::SELECT_ALL] = &Director::cmdSelect;
	
	// Add two-argument handlers
	hans2[Command::GRAB] = &Director::cmdGrab;
	
	// Copy commands
	for (h0=hans0.begin(); h0!=hans0.end(); h0++)
		cmds.push_back(h0->first);
	for (h2=hans2.begin(); h2!=hans2.end(); h2++)
		cmds.push_back(h2->first);
}



/**
 * Picks an item in the scene based on coordinates.
 */
void Director::cmdGrab(int cmd, float x, float y) {
	
	const int pickBuffSize=32;
	GLuint id, pickBuffer[pickBuffSize], pos, *ptr;
	GLint nPicks, vpArray[4];
	int count;
	Item *item;
	Translator trn;
	
	// Initialize pick buffer and names
	glSelectBuffer(pickBuffSize, pickBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	
	// Save current viewing matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	// Obtain the parameters for the current viewport
	glGetIntegerv(GL_VIEWPORT, vpArray);
	gluPickMatrix(GLdouble(x),
	              GLdouble(vpArray[3]-y),
	              5.0,
	              5.0,
	              vpArray);
	gluPerspective(30,
	               (float)scene->getWidth() / scene->getHeight(), 
	               0.1,
	               1000.0);
	
	// Draw
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(scene->position.x, scene->position.y, scene->position.z);
	glRotatef(scene->rotation.x, 1.0, 0.0, 0.0);
	glRotatef(scene->rotation.y, 0.0, 1.0, 0.0);
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		item = scene->items[i];
		if (item->isShown()) {
			glPushName(item->getID());
			item->draw();
			if (item->isSelected()) {
				glPushName(count+item->getID());
				trn.copy(*item);
				trn.draw();
			}
		}
	}
	
	// Restore original viewing matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
	
	// Determine number of picked objects, return to normal rendering mode
	nPicks = glRenderMode(GL_RENDER);
	
	// Find ID of object picked
	ptr = pickBuffer;
	for (int i=0; i<nPicks; i++) {
		pos = *ptr;
		ptr += 3;
		for (int j=0; j<pos; j++) {
			id = *ptr;
			ptr++;
		}
	}
	
	// Check for manipulator
	count = scene->items.size();
	for (int i=0; i<count; i++) {
		item = scene->items[i];
		if (count+item->getID() == id) {
			std::cout << "Manipulator for item: " << item->getID() << std::endl;
			state->manAct = true;
			std::cout << "Manipulator active" << std::endl;
			break;
		}
	}
	
	// Select the object
	if (!state->manAct) {
		count = scene->items.size();
		for (int i=0; i<count; i++) {
			item = scene->items[i];
			if (item->getID() == id) {
				item->toggleSelected();
				break;
			}
		}
	}
}



/**
 * Iterates through the items in the scene.
 */
void Director::cmdIterate(int cmd) {
	
	cout << "Director::cmdIterate(int)" << endl;
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
void Director::run(int command, float arg1, float arg2) {
	
	void (Director::*method)(int,float,float);
	
	// Filter command to correct method
	method = hans2[command];
	(this->*method)(command, arg1, arg2);
}
