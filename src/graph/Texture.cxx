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
		FakeTexture(const Tag &tag) : Texture(tag) {}
		void apply() {}
		void remove() {}
};



/**
 * Unit test for Texture.
 */
int main() {
	
	Scene scene;
	Tag tag;
	Texture *texture;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	
	// Test tag
	cout << "\nTesting tag..." << endl;
	tag.attributes["name"] = "foo";
	tag.attributes["file"] = "glsl/bar.frag";
	texture = new FakeTexture(tag);
	texture->print();
	
	// Create textures
	cout << "\nCreating textures..." << endl;
	for (int i=0; i<4; ++i)
		scene.addToLast(new FakeTexture("crate", "input/crate.jpg"));
	
	// Prepare nodes
	cout << "\nPreparing nodes..." << endl;
	scene.prepare();
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
}

