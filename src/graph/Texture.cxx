/*
 * Texture.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"
#include "Scene.hpp"



/**
 * Fake Texture subclass with stubs needed for testing.
 */
class FakeTexture : public Texture {
	public:
		FakeTexture(string filename,
		            string name) : Texture(filename,name) {}
		void apply() {}
		void remove() {}
};



/**
 * Unit test for Texture.
 */
int main() {
	
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create textures
	cout << "Creating textures..." << endl;
	for (int i=0; i<4; ++i)
		scene.addToLast(new FakeTexture("crate", "input/crate.jpg"));
	
	// Prepare nodes
	cout << "Preparing nodes..." << endl;
	scene.prepare();
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

