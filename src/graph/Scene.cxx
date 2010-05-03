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
	virtual void associate() {cout << "  Associate " << getClassName() << endl;}
	virtual void finalize() {cout << "  Finalize " << getClassName() << endl;}
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
class FakeSquare : public FakeNode {
public:
	FakeSquare() {}
};
class FakeGroup: public FakeNode {
public:
	FakeGroup() {}
	virtual bool isSealed() const {return true;}
};
class FakeInstance: public FakeNode {
public:
	FakeInstance() {
		addChild(new FakeSquare());
		addChild(new FakeSquare());
		addChild(new FakeSquare());
	}
	virtual bool areChildrenPrintable() const {return false;}
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
	} else if (name == "group") {
		return new FakeGroup();
	} else if (name == "instance") {
		return new FakeInstance();
	} else {
		throw "Could not create node.";
	}
}


class SceneTest {
public:
	void setUp();
	void tearDown();
	void testOpen();
	void testPrepare();
	void testPrint();
private:
	Scene *scene;
};


void SceneTest::setUp() {
	scene = new Scene();
}


void SceneTest::tearDown() {
	delete scene;
}


void SceneTest::testOpen() {
	cout << "Opening..." << endl;
	Factory::install("program", &create);
	Factory::install("shader", &create);
	Factory::install("translate", &create);
	Factory::install("cube", &create);
	Factory::install("group", &create);
	Factory::install("instance", &create);
	scene->open("Scene.xml");
}


void SceneTest::testPrepare() {
	cout << "\nPreparing..." << endl;
	scene->prepare();
}


void SceneTest::testPrint() {
	cout << "\nPrinting..." << endl;
	scene->print();
}


/**
 * Unit test for Scene.
 */
int main() {
	
	SceneTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		test.setUp();
		test.testOpen();
		test.testPrepare();
		test.testPrint();
		test.tearDown();
	} catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

