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
	bool useExclusiveDrag=false;
	char directions[] = {'x', 'y'};
	float dotProduct, dragAmount;
	map<char,Binding*>::iterator bi;
	Vector movement;
	
	// Update
	movement.set((x-lastCursorPosition.x), -(y-lastCursorPosition.y));
	
	// Drag manipulator
	if (currentManipulator != NULL)
		currentManipulator->use(scene, movement);
	else {
		
		// Check for exclusive drag
		for (int i=0; i<2; i++) {
			bi = dragBindings.find(directions[i]);
			if (bi != dragBindings.end()) {
				binding = bi->second;
				if (binding != NULL) {
					if (binding->getOption() == Binding::EXCLUSIVE) {
						useExclusiveDrag = true;
						break;
					}
				}
			}
		}
		
		// If exclusive, wait for a direction to set axis
		if (useExclusiveDrag) {
			if (dragCount == 0) {
				dragAxis.set(0.0, 0.0);
				dragDirection.set(0.0, 0.0);
			}
			dragDirection = dragDirection + movement;
			if (dragCount < 10 && dragDirection.length() >= 3.0) {
				if (dragAxis.x < 0.5 && dragAxis.y < 0.5) {
					if (fabs(dragDirection.y) > fabs(dragDirection.x))
						dragAxis.set(0.0, 1.0);
					else
						dragAxis.set(1.0, 0.0);
				}
			}
		}
		else
			dragAxis.set(1.0, 1.0);
		
		// Perform dragging
		for (int i=0; i<2; i++) {
			bi = dragBindings.find(directions[i]);
			if (bi != dragBindings.end()) {
				binding = bi->second;
				if (binding != NULL) {
					if (fabs(movement.get(i)) > 0.5) {
						dragAmount = movement.get(i) * dragAxis.get(i);
						delegate->run(binding->getCommand(),
						              binding->getArgument() *
						              dragAmount);
					}
				}
			}
		}
	}
	
	// Update
	lastCursorPosition.set(x, y);
	++dragCount;
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
	
	// Find the item under the cursor
	currentManipulator = NULL;
	itemIsManipulator = false;
	currentItemID = Picker::pick(scene, manipulators, x, y);
	item = Item::find(currentItemID);
	if (item != NULL) {
		if (typeid(*item) == typeid(Translator))
			itemIsManipulator = true;
	}
	
	// Reset
	if (state == GLUT_DOWN) {
		dragBindings.clear();
		dragCount = 0;
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
					dragBindings[direction] = binding;
				else
					dragBindings[direction] = NULL;
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
	print();
	
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
