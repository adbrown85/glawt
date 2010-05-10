/*
 * BooleanXor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanXor.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


class BooleanXorTest {
public:
	BooleanXorTest() {instance = this; shape = NULL;}
	static void keyboard(unsigned char key, int x, int y);
	void move(const Vector &movement);
	void setScene(Scene *scene) {this->scene = scene;}
protected:
	void select(int id);
private:
	static BooleanXorTest *instance;
	Scene *scene;
	Shape *shape;
};
BooleanXorTest *BooleanXorTest::instance;



void BooleanXorTest::keyboard(unsigned char key, int x, int y) {
	
	switch (toupper(key)) {
	case '1':
	case '2':
		instance->select(((int)key-48) - 1); break;
	case 'A':
		instance->move(Vector(-0.1,0,0,0)); break;
	case 'D':
		instance->move(Vector(+0.1,0,0,0)); break;
	case 'W':
		instance->move(Vector(0,+0.1,0,0)); break;
	case 'S':
		instance->move(Vector(0,-0.1,0,0)); break;
	case '<':
	case ',':
		instance->move(Vector(0,0,-0.1,0)); break;
	case '>':
	case '.':
		instance->move(Vector(0,0,+0.1,0)); break;
	case 'P':
		instance->scene->print(); break;
	case '-':
	case '_':
		Window::translate(Vector(0,0,-2)); break;
	case '+':
	case '=':
		Window::translate(Vector(0,0,+2)); break;
	case 27:
		exit(0);
	}
}


void BooleanXorTest::move(const Vector &movement) {
	
	Translate *translate;
	
	// Nothing selected
	if (shape == NULL)
		return;
	
	// Alter translate
	translate = Translate::find(shape);
	if (translate != NULL) {
		translate->add(movement);
	}
	Window::refresh();
}


void BooleanXorTest::select(int id) {
	
	int i;
	Node::iterator it;
	Node *node, *other;
	
	// Get the shape
	shape = dynamic_cast<Shape*>(Identifiable::findByID(id));
	
	// Add new color uniform and refresh
	node = Factory::create("uniform type='vec4' name='Color' value='1 1 0 1'");
	shape->addChild(node);
	node->associate();
	node->finalize();
	
	// Remove from other
	id = !id;
	other = dynamic_cast<Node*>(Identifiable::findByID(id));
	i = 0;
	for (it=other->begin(); it!=other->end(); ++it) {
		++i;
		if (i == 3) {
			delete *it;
			other->erase(it);
			break;
		}
	}
	
	// Refresh
	Window::refresh();
}


int main(int argc,
         char *argv[]) {
	
	BooleanXorTest test;
	
	// Initialize
	Tester::init(argc, argv);
	AdvancedFactory::install();
	Tester::open("BooleanXor.xml");
	
	// Start
	test.setScene(Tester::getScene());
	Window::setKeyboard(&BooleanXorTest::keyboard);
	Tester::start();
	
	// Finish
	return 0;
}

