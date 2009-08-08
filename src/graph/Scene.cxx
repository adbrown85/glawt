/*
 * Scene.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <ctime>
#include <iostream>
#include "Scene.hpp"
#include "Shape.hpp"
#include "Translation.hpp"
#define NUM_OF_ITEMS 3
using namespace std;



/**
 * Fake shape node.
 */
class FakeShape : public Shape {
	public:
		void draw() const {};
};



/**
 * Unit test for Scene.
 */
int main() {
	
	float rotation;
	int randomNum;
	FakeShape shapes[NUM_OF_ITEMS];
	Scene scene;
	Translation trans[NUM_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	
	// Build scene
	cout << "\nBuilding scene..." << endl;
	for (int i=0; i<NUM_OF_ITEMS; ++i) {
		scene.add(&trans[i]);
		trans[i].addChild(&shapes[i]);
	}
	
	// Randomize translations
	cout << "\nRandomizing translations..." << endl;
	srand(time(NULL));
	for (int i=0; i<NUM_OF_ITEMS; ++i) {
		randomNum = rand() % 10;
		trans[i].set(0, 0, randomNum);
	}
	scene.print();
	
	// Sort by depth
	cout << "\nEnter rotation:  ";
	cin >> rotation;
	while (cin) {
		scene.setRotation(rotation, 0, 1, 0);
		cout << "Sorting by depth..." << endl;
		scene.sortByDepth();
		scene.print();
		cout << "\nEnter rotation:  ";
		cin >> rotation;
	}
	cout << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
}
