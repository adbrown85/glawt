/*
 * Scene.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include <iostream>
#include "Scene.hpp"
#include "Shape.hpp"
//#include "Translation.hpp"
#define NUM_OF_ITEMS 3
using namespace std;


/**
 * Fake shape node.
 */
class FakeShape : public Shape {
	public:
		FakeShape(float size=1.0) : Shape(size) {}
		void draw() const {};
};


/**
 * Unit test for Scene.
 */
int main() {
	
	float rotation;
	Scene sceneA, sceneB;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test open
	cout << "Testing open..." << endl;
	sceneB.open("Scene.xml");
	sceneB.print();
	
	// Build scene
	cout << "\nBuilding scene..." << endl;
	srand(time(NULL));
	for (int i=0; i<NUM_OF_ITEMS; ++i) {
		//sceneA.addToRoot(new Translation(0, 0, rand()%10));
		sceneA.addToLast(new FakeShape(1.0));
		sceneA.backup();
		sceneA.addToLast(new FakeShape(2.0));
	}
	sceneA.print();
	
	// Sort by depth
	cout << "\nEnter rotation:  ";
	cin >> rotation;
	while (cin) {
		sceneA.setRotation(rotation, 0, 1, 0);
		cout << "Sorting by depth..." << endl;
		sceneA.sortByDepth();
		sceneA.print();
		cout << endl;
		cout << "Enter rotation:  ";
		cin >> rotation;
	}
	cout << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

