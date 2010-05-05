/*
 * Picker.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Picker.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


class PickerTest {
public:
	void setUp();
	void testPick();
	static void mouse(int,int,int,int);
private:
	static Picker *picker;
};
Picker *PickerTest::picker=NULL;


void PickerTest::mouse(int button, int state, int x, int y) {
	
	pair<int,int> result;
	
	result = picker->pick(x,y);
	cout << "  " << result.first << " " << result.second << endl;
}


void PickerTest::setUp() {
	
	// Open the scene
	AdvancedFactory::install();
	Tester::open("Picker.xml");
	
	// Install picker
	Window::setMouse(&PickerTest::mouse);
	if (picker == NULL)
		picker = new Picker(Tester::getScene());
}


void PickerTest::testPick() {
	
	cout << "\nTesting pick..." << endl;
	Tester::start();
}


int main(int argc,
         char *argv[]) {
	
	PickerTest test;
	
	Tester::init(argc, argv);
	test.setUp();
	test.testPick();
	
	// Finish
	return 0;
}

