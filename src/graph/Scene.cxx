/*
 * Scene.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "Scene.hpp"
#define NUM_OF_ITEMS 3
using namespace std;

class FakeNode : public Node {
public:
	virtual void associate() {cout << "Associate " << getClassName() << endl;}
	virtual void finalize() {cout << "Finalize " << getClassName() << endl;}
};

class FakeProgram : public FakeNode {
public:
	FakeProgram() {}
};
class FakeShader : public FakeNode {
public:
	FakeShader() {}
};
class FakeTranslate : public FakeNode {
public:
	FakeTranslate() {}
};
class FakeCube : public FakeNode {
public:
	FakeCube() {}
};


Node* create(const Tag &tag) {
	
	string name;
	
	name = tag.getName();
	if (name == "program") {
		return new FakeProgram();
	} else if (name == "shader") {
		return new FakeShader();
	} else if (name == "translate") {
		return new FakeTranslate();
	} else if (name == "cube") {
		return new FakeCube();
	} else {
		throw "Could not create node.";
	}
}


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
	cout << "Opening..." << endl;
	Factory::install("program", &create);
	Factory::install("shader", &create);
	Factory::install("translate", &create);
	Factory::install("cube", &create);
	scene.open("Scene.xml");
	
	// Test prepare
	cout << "\nPreparing..." << endl;
	scene.prepare();
	
	// Test print
	cout << "\nPrinting..." << endl;
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

