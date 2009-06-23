/*
 * Mouse.cpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Mouse.hpp"
Mouse *Mouse::obj=NULL;



/**
 * Manipulates the scene when the mouse is dragged.
 * 
 * @param x
 *     Current horizontal coordinate of the mouse while it's being dragged.
 * @param y
 *     Current vertical coordinate of the mouse while it's being dragged.
 */
void Mouse::handleDrag(int x, int y) {
	
	Binding *binding;
	char directions[] = {'x', 'y'};
	Vector movement;
	map<char,Binding*>::iterator bi;
	
	// Update
	currentCursorPosition.set(x, y);
	movement.set((x-lastCursorPosition.x), -(y-lastCursorPosition.y));
	
	// Dragging manipulator
	if (currentManipulator != NULL)
		currentManipulator->use(scene, movement);
	
	// Run normal drag commands for each direction
	else {
		for (int i=0; i<2; i++) {
			bi = currentDragBindings.find(directions[i]);
			if (bi != currentDragBindings.end()) {
				binding = bi->second;
				if (binding != NULL)
					delegate->run(binding->getCommand(),
					              binding->getArgument()*movement.get(i));
			}
		}
	}
	
	// Update
	lastCursorPosition.set(x, y);
	glutPostRedisplay();
}



/**
 * Handles mouse clicks.
 * 
 * @param button
 *     Button that was clicked.
 * @param state
 *     State of the button.
 * @param x
 *     Current horizontal coordinate of the mouse when it was clicked.
 * @param y
 *     Current vertical coordinate of the mouse when it was clicked.
 */
void Mouse::handleClick(int button, int state, int x, int y) {
	
	bool itemIsManipulator=false;
	Binding *binding;
	char direction;
	int modifier;
	Item *item;
	multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Store current cursor position
	currentCursorPosition.set(x, y);
	
	// Find the item under the cursor
	currentManipulator = NULL;
	itemIsManipulator = false;
	if (state == GLUT_DOWN) {
		currentItemID = Picker::pick(scene, manipulators, x, y);
		item = Item::find(currentItemID);
		if (item != NULL) {
			if (typeid(*item) == typeid(Translator))
				itemIsManipulator = true;
		}
	}
	
	// Lookup binding for this binding and state
	modifier = glutGetModifiers();
	if (modifier == 1 || modifier == 5)
		modifier -= 1;
	range = bindings.equal_range(button);
	for (bi=range.first; bi!=range.second; ++bi) {
		binding = &bi->second;
		if (binding->getModifier() == modifier) {
			if (binding->hasDrag()) {
				direction = static_cast<char>(binding->getState());
				if (state == GLUT_DOWN)
					currentDragBindings[direction] = binding;
				else
					currentDragBindings[direction] = NULL;
			}
			else if (state == binding->getState()) {
				if (itemIsManipulator) {
					if (binding->getCommand() == Command::MANIPULATE)
						currentManipulator = dynamic_cast<Manipulator*>(item);
				}
				else {
					if (binding->hasArgument())
						delegate->run(binding->getCommand(),
						              binding->getArgument());
					else
						delegate->run(binding->getCommand());
					glutPostRedisplay();
				}
			}
		}
	}
	
	// Store cursor position for next time
	lastCursorPosition.set(x, y);
}



/**
 * Installs the control into the current context.
 * 
 * @param scene
 *     Makes the Control use this scene;
 */
vector<Manipulator*> Mouse::install(Scene *scene) {
	
	// Initialize attributes
	Mouse::obj = this;
	this->scene = scene;
	this->type = "Mouse";
	
	// Install
	installBindings();
	installCallbacks();
	installManipulators();
	
	// Finish
	return manipulators;
}



/**
 * GLUT callback for when the mouse is dragged.
 */
void Mouse::motion(int x, int y) {
	
	obj->handleDrag(x, y);
}



/**
 * GLUT callback for mouse clicks.
 */
void Mouse::mouse(int button, int state, int x, int y) {
	
	obj->handleClick(button, state, x, y);
}



/**
 * Simple test program.
 */
/*
#include "Interpreter.hpp"
int main() {
	
	using namespace std;
	Scene scene;
	Interpreter interpreter(&scene);
	Mouse mouse(&interpreter);
	vector<Manipulator*> manipulators;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Mouse" << endl;
	cout << "****************************************" << endl;
	
	// Test
	cout << endl;
	manipulators = mouse.install(&scene);
	for (int i=0; i<manipulators.size(); ++i)
		cout << manipulators[i]->getAxis() << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Mouse" << endl;
	cout << "****************************************" << endl;
	return 0;
}
*/
