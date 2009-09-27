/*
 * Target.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"



int main(int argc,
         char *argv[]) {
	
	Framebuffer framebuffer;
	Target target;
	Texture2D texture;
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Target" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	scene.add(&texture);
	texture.addChild(&framebuffer);
	framebuffer.addChild(&target);
	scene.prepare();
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Target" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

