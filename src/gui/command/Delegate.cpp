/*
 * Delegate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Delegate.hpp"


/** Stores the inputs and sets up all the workers. */
Delegate::Delegate(Scene *scene, Canvas *canvas) {
	
	// Fields
	this->scene = scene;
	this->canvas = canvas;
	
	// Workers
	cameraman = new Cameraman(scene, canvas);
	compositor = new Compositor(scene, canvas);
	director = new Director(scene, canvas);
	grip = new Grip(scene, canvas);
	producer = new Producer(scene, canvas);
}


/** Deletes all the workers. */
Delegate::~Delegate() {
	
	delete cameraman;
	delete compositor;
	delete director;
	delete grip;
	delete producer;
}


/** Adds a callback that will be called when a command is issued. */
void Delegate::addListener(CommandListener *listener, int command) {
	
	listeners[command] = listener;
}


/** Calls the listener for a command. */
void Delegate::fireEvent(int command) {
	
	map<int,CommandListener*>::iterator it;
	
	it = listeners.find(command);
	if (it != listeners.end()) {
		(it->second)->onCommandEvent(command);
	}
}


/** Runs a command by handing it off to a worker. */
void Delegate::run(int command) {
	
	// Check for listener
	fireEvent(command);
	
	// Hand off to worker
	switch (command) {
	case Command::FIT_SELECTED:
	case Command::FIT_ALL:
		cameraman->fit(command);
		break;
	case Command::RESET:
		cameraman->reset(command);
		break;
	case Command::REFRESH:
		cameraman->refresh(command);
		break;
	case Command::HIDE:
		compositor->hide(command);
		break;
	case Command::SHOW_ALL:
		compositor->showAll(command);
		break;
	case Command::DESELECT:
	case Command::SELECT_ALL:
		director->select(command);
		break;
	case Command::NEXT:
	case Command::PREVIOUS:
		director->iterate(command);
		break;
	case Command::EXIT:
		producer->quit(command);
		break;
	case Command::LIST:
		producer->list(command);
		break;
	}
}


/** Runs a command by handing it off to a worker. */
void Delegate::run(int command, float argument) {
	
	// Check for listener
	fireEvent(command);
	
	// Hand off to worker
	switch (command) {
	case Command::CIRCLE_X:
	case Command::CIRCLE_Y:
	case Command::CIRCLE_LEFT:
	case Command::CIRCLE_RIGHT:
	case Command::CIRCLE_DOWN:
	case Command::CIRCLE_UP:
		cameraman->rotate(command, argument);
		break;
	case Command::BOOM:
	case Command::BOOM_DOWN:
	case Command::BOOM_UP:
	case Command::ZOOM_IN:
	case Command::ZOOM_OUT:
	case Command::TRACK:
	case Command::TRACK_LEFT:
	case Command::TRACK_RIGHT:
		cameraman->translate(command, argument);
		break;
	case Command::GRAB:
		director->grab(command, argument);
		break;
	case Command::ROTATE_X:
	case Command::ROTATE_Y:
	case Command::ROTATE_Z:
		grip->rotate(command, argument);
		break;
	case Command::SCALE_X:
	case Command::SCALE_Y:
	case Command::SCALE_Z:
		grip->scale(command, argument);
		break;
	case Command::TRANSLATE_X:
	case Command::TRANSLATE_Y:
	case Command::TRANSLATE_Z:
		grip->translate(command, argument);
		break;
	}
}


/** Runs a command by handing it off to a worker. */
void Delegate::run(int command, string argument) {
	
	// Check for listener
	fireEvent(command);
	
	// Hand off to worker
	switch (command) {
	case Command::OPEN:
		producer->open(command, argument);
		break;
	}
}

