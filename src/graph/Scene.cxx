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
		FakeShape(float size=1.0) : Shape(size) {}
		void draw() const {};
};



/**
 * Unit test for Scene.
 */
int main() {
	
	float rotation;
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Build scene
	cout << "Building scene..." << endl;
	srand(time(NULL));
	for (int i=0; i<NUM_OF_ITEMS; ++i) {
		scene.addToRoot(new Translation(0, 0, rand()%10));
		scene.addToLast(new FakeShape(1.0));
		scene.backup();
		scene.addToLast(new FakeShape(2.0));
	}
	scene.print();
	
	// Sort by depth
	cout << endl;
	cout << "Enter rotation:  ";
	cin >> rotation;
	while (cin) {
		scene.setRotation(rotation, 0, 1, 0);
		cout << "Sorting by depth..." << endl;
		scene.sortByDepth();
		scene.print();
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

