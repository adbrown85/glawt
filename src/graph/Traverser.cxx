/*
 * Traverser.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Traverser.hpp"
#include "Factory.hpp"
#include "Parser.hpp"
#include "Tag.hpp"
#include "Window.hpp"


class FakeDrawable : public Drawable {
public: 
	FakeDrawable(const Tag &tag) : Drawable(tag) {name = tag.getName();}
	virtual void draw() const {cout << "  " << name << endl;}
	string name;
};
class FakeSelectable : public Selectable {
public: 
	FakeSelectable(const Tag &tag) : Selectable(tag) {name = tag.getName();}
	virtual void draw() const {cout << "  " << name << endl;}
	string name;
};
class FakeApplicable : public Applicable {
public:
	FakeApplicable(const Tag &tag) {name = tag.getName();}
	virtual void apply() {cout << "  " << name << endl;}
	virtual void remove() {cout << "  " << name << endl;}
	string name;
};


class FakeTraverser : public Traverser {
public:
	FakeTraverser(Scene *scene) : Traverser(scene) {};
	virtual void onApplicable(Applicable *applicable);
	virtual void onDrawable(Drawable *drawable);
	virtual void onSelectable(Selectable *selectable);
};
void FakeTraverser::onApplicable(Applicable *node) {
	cout << "  FakeTraverser::onApplicable" << endl;
	cout << "  " << node->getClassName() << endl;
	Traverser::onApplicable(node);
}
void FakeTraverser::onDrawable(Drawable *node) {
	cout << "  FakeTraverser::onDrawable" << endl;
	cout << "  " << node->getClassName() << endl;
	Traverser::onDrawable(node);
}
void FakeTraverser::onSelectable(Selectable *node) {
	cout << "  FakeTraverser::onSelectable" << endl;
	cout << "  " << node->getClassName() << endl;
	Traverser::onSelectable(node);
}


Node* create(const Tag &tag) {
	
	string name=tag.getName();
	
	if (name=="cube") {
		return new FakeSelectable(tag);
	} else if (name=="fullscreen") {
		return new FakeDrawable(tag);
	} else if (name=="program" || name=="translate") {
		return new FakeApplicable(tag);
	} else {
		return new Node();
	}
}


class TraverserTest {
public:
	void before();
	void testStart();
	void after();
private:
	Scene *scene;
	Traverser *traverser;
};


void TraverserTest::before() {
	
	// Open scene
	cout << "Creating..." << endl;
	Factory::install("program", &create);
	Factory::install("shader", &create);
	Factory::install("translate", &create);
	Factory::install("cube", &create);
	scene = new Scene();
	scene->open("Traverser.xml");
	traverser = new FakeTraverser(scene);
}


void TraverserTest::testStart() {
	
	// Start
	cout << "\nStarting..." << endl;
	traverser->start();
}


void TraverserTest::after() {
	
	// Clean up
	cout << "\nCleaning up..." << endl;
	delete traverser;
	delete scene;
}



int main(int argc,
         char *argv[]) {
	
	TraverserTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Traverser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		test.before();
		test.testStart();
		test.after();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Traverser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

