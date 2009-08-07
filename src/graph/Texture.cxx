/*
 * Texture.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture.hpp"



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
	
	Texture *textures[4];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create textures
	cout << "Creating textures..." << endl;
	for (int i=0; i<4; ++i)
		textures[i] = new FakeTexture("input/crate.jpg", "crate");
	for (int i=0; i<3; ++i)
		textures[i]->addChild(textures[i+1]);
	
	// Prepare nodes
	cout << "Preparing nodes..." << endl;
	for (int i=0; i<4; ++i)
		textures[i]->associate();
	textures[0]->printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
