/*
 * Framebuffer.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
#include "Scene.hpp"



/**
 * Unit test for %Framebuffer.
 */
int main(int argc,
         char *argv[]) {
	
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Framebuffer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	scene.add(new Framebuffer());
	scene.associate();
	scene.finalize();
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Framebuffer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

