/*
 * Scene.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "Scene.hpp"
#include "Shape.hpp"
#define NUM_OF_ITEMS 3
using namespace std;


/**
 * Fake shape node.
 */
class FakeShape : public Shape {
	public:
		FakeShape(float size=1.0) : Shape(size) {}
		virtual void draw() const {};
};


class FakeFactory : public Factory {
	public:
		Node* create(const Tag &tag) {
			Node* node = new Node();
			node->setClassName(tag.name);
			return node;
		}
		set<string> getClasses() {
			set<string> classes;
			classes.insert("program");
			classes.insert("shader");
			classes.insert("translate");
			classes.insert("cube");
			return classes;
		}
};


/**
 * Unit test for Scene.
 */
int main() {
	
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test open
	cout << "Testing open..." << endl;
	scene.install(new FakeFactory());
	scene.open("Scene.xml");
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
/*
	float rotation;
	
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
*/
	
}

