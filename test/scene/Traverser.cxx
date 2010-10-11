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


class FakeDrawable : public Node, public Drawable {
public: 
	FakeDrawable(const Tag &tag) : Node(tag) {name = tag.getName();}
	virtual void draw() const {cout << "  " << name << endl;}
	virtual bool isSelectable() const {return true;}
	virtual bool isSelected() const {return false;}
	virtual bool isVisible() const {return true;}
	virtual void setSelected(bool selected) {}
	virtual void setVisible(bool visible) {}
	virtual void toggleSelected() {}
	virtual void toggleVisible() {}
	virtual string toString() const {return Node::toString() + " " + name;}
	string name;
};
class FakeApplicable : public Node, public Applicable {
public:
	FakeApplicable(const Tag &tag) : Node(tag) {name = tag.getName();}
	virtual void apply() {cout << "  " << name << endl;}
	virtual void remove() {cout << "  " << name << endl;}
	virtual string toString() const {return Node::toString() + " " + name;}
	string name;
};
class FakeSealed : public Node {
public:
	FakeSealed(const Tag &tag) : Node(tag) {name = tag.getName();}
	virtual bool areChildrenTraversable() const {return false;}
	virtual string toString() const {return Node::toString() + " " + name;}
	string name;
};


class FakeTraverser : public Traverser {
public:
	FakeTraverser(Scene *scene) : Traverser(scene) {};
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
};
void FakeTraverser::onApplicable(Node *node, Applicable *applicable) {
	cout << "  FakeTraverser::onApplicable" << endl;
	cout << "  " << node->getClassName() << endl;
	Traverser::onApplicable(node, applicable);
}
void FakeTraverser::onDrawable(Node *node, Drawable *drawable) {
	cout << "  FakeTraverser::onDrawable" << endl;
	cout << "  " << node->getClassName() << endl;
	Traverser::onDrawable(node, drawable);
}


Node* create(const Tag &tag) {
	
	string name=tag.getName();
	
	if (name=="cube" || name=="square") {
		return new FakeDrawable(tag);
	} else if (name=="group") {
		return new FakeSealed(tag);
	} else if (name=="program" || name=="translate" || name=="uniform") {
		return new FakeApplicable(tag);
	} else {
		return new Node(tag);
	}
}


class TraverserTest {
public:
	void setUp();
	void tearDown();
	void testStart();
private:
	Scene *scene;
	Traverser *traverser;
};


void TraverserTest::setUp() {
	
	// Open scene
	cout << "Creating..." << endl;
	Factory::install("program", &create);
	Factory::install("shader", &create);
	Factory::install("translate", &create);
	Factory::install("cube", &create);
	Factory::install("square", &create);
	Factory::install("uniform", &create);
	Factory::install("group", &create);
	scene = new Scene();
	scene->open("Traverser.xml");
	scene->print();
	traverser = new FakeTraverser(scene);
}


void TraverserTest::tearDown() {
	
	// Clean up
	cout << "\nCleaning up..." << endl;
	delete traverser;
	delete scene;
}


void TraverserTest::testStart() {
	
	// Start
	cout << "\nStarting..." << endl;
	traverser->start();
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
		test.setUp();
		test.testStart();
		test.tearDown();
	} catch (Exception &e) {
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

