/*
 * Scene.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Scene.hpp"



/**
 * Creates and initializes a new scene.
 */
Scene::Scene() {
	
	// Initialize
	this->width = SCENE_DEFAULT_WIDTH;
	this->height = SCENE_DEFAULT_HEIGHT;
	reset();
}



/**
 * Creates and initializes a new scene.
 * 
 * @param width
 *     Width of the window for the scene.
 * @param height
 *     Height of the window for the scene.
 */
Scene::Scene(int width,
             int height) {
	
	// Initialize
	this->width = width;
	this->height = height;
	reset();
}



/**
 * Adds an item to the scene.
 * 
 * @param item
 *     Pointer to the Item object that should be added.
 */
void Scene::add(Item *item) {
	
	// Add pointer to list
	items.push_back(item);
}



/**
 * Adds a shader to the scene.
 * 
 * @param shader
 *     Pointer to the Shader object that should be added.
 */
void Scene::add(Shader *shader) {
	
	// Add pointer to list
	shaders.push_back(shader);
}



/**
 * Deselects all items in the scene.
 */
void Scene::deselectAll() {
	
	int count;
	
	// Set all items as selected
	count = items.size();
	for (int i=0; i<count; i++)
		items[i]->setSelected(false);
}



/**
 * Checks if any item in the scene is selected.
 * 
 * @return True if an item is selected.
 */
bool Scene::hasSelected() {
	
	int count;
	
	// Check all items
	count=items.size();
	for (int i=0; i<count; i++)
		if (items[i]->isSelected())
			return true;
	return false;
}



/**
 * Prints the list of items stored.
 */
void Scene::print() {
	
	using namespace std;
	int count;
	
	// Print
	count = items.size();
	cout << "Items: " << endl;
	for (int i=0; i<count; i++)
		if (items[i] != NULL)
			cout << "  " << *items[i] << endl;
}



/**
 * Resets the scene to the default state.
 */
void Scene::reset() {
	
	// Reset transformations
	position.set(0.0, 0.0, SCENE_DEFAULT_ZOOM);
	rotation.set(0.0, 0.0, 0.0);
}



/**
 * Selects all items in the scene that are not hidden.
 */
void Scene::selectAll() {
	
	int count;
	
	// Set all items as selected
	count = items.size();
	for (int i=0; i<count; i++)
		if (items[i]->isShown())
			items[i]->setSelected(true);
}




/**
 * Simple test program.
 */
/*
#include "Box.hpp"
int main(int argc, char **argv) {
	
	using namespace std;
	Box boxA(3.0), boxB(2.0);
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	boxA.setPosition( 2.0, 0.0, 0.0);
	boxB.setPosition(-2.0, 0.0, 0.0);
	scene.add(&boxA);
	boxA.setSelected(true);
	scene.add(&boxB);
	scene.print();
	if (scene.hasSelected())
		cout << "Scene has an item selected." << endl;
	scene.selectAll();
	scene.print();
	if (scene.hasSelected())
		cout << "Scene has an item selected." << endl;
	scene.deselectAll();
	scene.print();
	if (scene.hasSelected())
		cout << "Scene has an item selected." << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
