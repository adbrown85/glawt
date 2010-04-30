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
Traverser *traverser;


class FakeDrawable : public Node, public Drawable {
public:
	FakeDrawable(const string &name) : Node(name) {}
	virtual void draw() const {}
};
class FakeApplicable : public Node, public Applicable {
public:
	FakeApplicable(const string &name) : Node(name) {}
	virtual void apply() {}
	virtual void remove() {}
};


class FakeTraverser : public Traverser {
public:
	FakeTraverser(Scene *scene) : Traverser(scene) {};
	virtual void onApplicable(Node *node);
	virtual void onDrawable(Node *node);
	virtual void onSelectable(Node *node);
};
void FakeTraverser::onApplicable(Node *node) {
	
	cout << "FakeTraverser::onApplicable" << endl;
	cout << node->getClassName() << endl;
	Traverser::onApplicable(node);
}
void FakeTraverser::onDrawable(Node *node) {
	
	cout << "FakeTraverser::onDrawable" << endl;
	cout << node->getClassName() << endl;
	Traverser::onDrawable(node);
}
void FakeTraverser::onSelectable(Node *node) {
	
	cout << "FakeTraverser::onSelectable" << endl;
	cout << node->getClassName() << endl;
	Traverser::onSelectable(node);
}


Node* create(const Tag &tag) {
	
	string name=tag.getName();
	
	if (name == "cube") {
		return new FakeDrawable(name);
	} else if (name=="program" || name=="shader" || name=="translate") {
		return new FakeApplicable(name);
	} else {
		return new Node(name);
	}
}


int main(int argc,
         char *argv[]) {
	
	Scene *scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Traverser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		Factory::install("program", &create);
		Factory::install("shader", &create);
		Factory::install("translate", &create);
		Factory::install("cube", &create);
		scene = new Scene();
		scene->open("Traverser.xml");
		traverser = new FakeTraverser(scene);
		traverser->start();
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

